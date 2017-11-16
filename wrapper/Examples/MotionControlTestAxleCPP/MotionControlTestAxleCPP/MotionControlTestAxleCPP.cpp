// MotionControlTestAxleCPP.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include <Windows.h>
#include <string>

#include "mctl.h"
#include "axctl.h"

using namespace std;

int main()
{
	cout << "MotionControlTestAxleCPP starting" << endl;
	HINSTANCE hMctlLibrary;
	hMctlLibrary = LoadLibraryA("CanApi.dll");

	if (hMctlLibrary)
	{
		cout << "canapi loaded successfully" << endl;
		HINSTANCE hAxctlLibrary;
		hAxctlLibrary = LoadLibraryA("axctl.dll");
		if (hAxctlLibrary)
		{
			cout << "axctl loaded successfully" << endl;

			MCTL_INITIALIZE _initializeMctl;
			MCTL_EXIT _mctl_Exit;
			AXCTL_INITIALIZE _initialize;
			AXCTL_RESET _reset;
			AXCTL_REFERENCE _reference;
			AXCTL_MOVEABS _moveAbs;
			AXCTL_EXIT _xit;

			_initializeMctl = (MCTL_INITIALIZE)GetProcAddress(hMctlLibrary, "mctl_Initialize");
			_mctl_Exit = (MCTL_EXIT)GetProcAddress(hMctlLibrary, "mctl_Exit");
			_initialize = (AXCTL_INITIALIZE)GetProcAddress(hAxctlLibrary, "axctl_Initialize");
			_reset = (AXCTL_RESET)GetProcAddress(hAxctlLibrary, "axctl_Reset");
			_reference = (AXCTL_REFERENCE)GetProcAddress(hAxctlLibrary, "axctl_Reference");
			_moveAbs = (AXCTL_MOVEABS)GetProcAddress(hAxctlLibrary, "axctl_MoveAbs");
			_xit = (AXCTL_EXIT)GetProcAddress(hAxctlLibrary, "axctl_Exit");

			if (_initializeMctl && _mctl_Exit && _initialize && _reset && _reference && _moveAbs && _xit)
			{
				cout << "functions retrieved" << endl;

				unsigned int uiResult = 0;
				//         uiResult = MCTL.mctl_Initialize("C:\\CNCWorkbench\\control\\can\\testaxctlserial.ini");
				//         uiResult = 0;
				//          if ((0xC000FFFF & uiResult) == 0)
				//         {
				// mctl_Initialize erfolgreich
				uiResult = _initialize("c:\\CNCworkbench\\Control\\CAN\\CAN_PCI_3_Axis.ini");
//				uiResult = _initialize("C:\\CNCWorkbench\\control\\can\\testaxctlserial.ini");
				if ((uiResult & 0xC000FFFF) == 0)
				{
					// axctl_Initialize erfolgreich
					// Reset der ersten Achse
					uiResult = _reset(1);
					if ((uiResult & 0xC000FFFF) == 0)
					{
						uiResult = _reference(1);
						if ((uiResult & 0xC000FFFF) == 0)
						{
							uiResult = _moveAbs(1, 10000);
							if ((uiResult & 0xC000FFFF) == 0)
							{
								string dump;
								cout << "whack a key once movement stops" << endl;
								getline(cin, dump);
								uiResult = _xit();
								uiResult = _mctl_Exit();
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
					printf("Fehler bei axctl_Initialize: %x", uiResult);
				}
				//         }
				//         else
				//         {
				//             strTest = string.Format("{0:X}", uiResult);
				//             DLLT.MessageBox(0, strTest, "Fehler bei mctl_Initialize", uiResult);
				//         }
			}

			FreeLibrary(hAxctlLibrary);
		}
		else
		{
			cout << "failed to load Axctl" << endl;
		}
		FreeLibrary(hMctlLibrary);
	}
	else
	{
		cout << "failed to load canapi" << endl;
	}
}
