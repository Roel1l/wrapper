// MotionControlTestWrappedCPP.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include <Windows.h>
#include <string>

#include "mctl.h"
#include "mctlWrapper.h"

using namespace std;

typedef DWORD(*MCTLW_INIT)(char*);
typedef DWORD(*MCTLW_MOVEABS)(LPAXISPOS);
typedef DWORD(*MCTLW_EXIT)(void);
typedef DWORD(*MCTLW_RESET)(void);
typedef DWORD(*MCTLW_REFERENCE)(DWORD);


int main()
{
	cout << "MotionControlTestWrappedCPP starting" << endl;
	HINSTANCE hInstLibrary = LoadLibraryA("mctlWrapper.dll");
	if (hInstLibrary)
	{
		cout << "canapi loaded successfully" << endl;
		MCTLW_INIT _initialize = (MCTLW_INIT)GetProcAddress(hInstLibrary, "mctlw_Initialize");
		MCTLW_MOVEABS _moveAbs = (MCTLW_MOVEABS)GetProcAddress(hInstLibrary, "mctlw_MoveAbs");
		MCTLW_EXIT _xit = (MCTLW_EXIT)GetProcAddress(hInstLibrary, "mctlw_Exit");
		MCTLW_RESET _reset = (MCTLW_RESET)GetProcAddress(hInstLibrary, "mctlw_Reset");
		MCTLW_REFERENCE _reference = (MCTLW_REFERENCE)GetProcAddress(hInstLibrary, "mctlw_Reference");

		unsigned int uiResult = 0;
		uiResult = _initialize("c:\\CNCworkbench\\Control\\CAN\\CAN_PCI_3_Axis.ini");
		if ((uiResult & 0xC000FFFF) == 0)
		{
			uiResult = _reset();
			if ((uiResult & 0xC000FFFF) == 0)
			{
				uiResult = _reference(1);
				if ((uiResult & 0xC000FFFF) == 0)
				{
					AXISPOS ax;
					ax.X = 100000; //  µm
					ax.Y = 120000; //  µm
				   //Correct init bug...
					ax.Z = 0;
					ax.A = 0;
					ax.B = 0;
					ax.C = 0;
					ax.U = 0;
					ax.V = 0;
					ax.W = 0;
					printf("Bewegung wird gestartet.\n");
					uiResult = _moveAbs(&ax);
					if ((uiResult & 0xC000FFFF) == 0)
					{
						string dump;
						cout << "whack a key once movement stops" << endl;
						getline(cin, dump);
						uiResult = _xit();
					}
					else
					{
						printf("Fehler bei axctl_MoveAbs: %x", uiResult);
					}
				}
				else
				{
					printf("Fehler bei axctl_Reference: %x", uiResult);
				}
			}
			else
			{
				printf("Fehler bei axctl_Reset: %x", uiResult);
			}
		}
		else
		{
			printf("Fehler bei mctl_Initialize: %x", uiResult);
		}

		FreeLibrary(hInstLibrary);
	}
	else
	{
		cout << "failed to load mctlWrapper" << endl;
	}
	return 0;
}

