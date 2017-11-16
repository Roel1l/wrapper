// MotionControlTestMctlCPP.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include <Windows.h>
#include <string>

#include "mctl.h"

using namespace std;

int main()
{
	cout << "MotionControlTestMctlCPP starting" << endl;
	HINSTANCE hMctlLibrary;
	hMctlLibrary = LoadLibraryA("CanApi.dll");

	if (hMctlLibrary)
	{
		cout << "canapi loaded successfully" << endl;

		MCTL_INITIALIZE _initialize;
		MCTL_EXIT _xit;
		MCTL_RESET _reset;
		MCTL_REFERENCE _reference;
		MCTL_MOVEABS _moveAbs;

		_initialize = (MCTL_INITIALIZE)GetProcAddress(hMctlLibrary, "mctl_Initialize");
		_xit = (MCTL_EXIT)GetProcAddress(hMctlLibrary, "mctl_Exit");
		_reset = (MCTL_RESET)GetProcAddress(hMctlLibrary, "mctl_Reset");
		_reference = (MCTL_REFERENCE)GetProcAddress(hMctlLibrary, "mctl_Reference");
		_moveAbs = (MCTL_MOVEABS)GetProcAddress(hMctlLibrary, "mctl_MoveAbs");

		if (_initialize && _xit && _reset && _reference && _moveAbs)
		{
			cout << "functions retrieved" << endl;
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
						uiResult = _moveAbs(&ax, sizeof(ax));
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
		}
		FreeLibrary(hMctlLibrary);
	}
	else
	{
		cout << "failed to load canapi" << endl;
	}
	return 0;
}

