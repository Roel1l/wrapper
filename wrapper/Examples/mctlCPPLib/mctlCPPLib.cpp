
#include <iostream>
#include "stdafx.h"
#include <Windows.h>
#include <string>

#include "ncerror.h"
#include "mctl.h"
#include "mctl1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// Initialisieren der isel-CAN-CNC-Steuerung
	// mctl1.ini enthält ein Beispiel mit zwei Achsen (X,Y)
//	DWORD wresult = mctl_Initialize("c:\\CNCworkbench\\control\\can\\Examples\\mctl1\\mctl1.ini");
	DWORD wresult = mctl_Initialize("c:\\CNCworkbench\\Control\\CAN\\CAN_PCI_3_Axis.ini");
	cerr << "mctl_Initialize(\"c:\\CNCworkbench\\control\\can\\Examples\\mctl1\\mctl1.ini\") ";
	if ((0xFFFF & wresult) == ERR_NOERROR)
	{
		cerr << ": OK\n";
		// Reset der Achsen und Fahren in den Betriebszustand
		DWORD wresult = mctl_Reset();
		cerr << "mctl_Reset() ";
		if ((0xFFFF & wresult) == ERR_NOERROR)
		{
			cerr << ": OK\n";
			// Referencefahrt der Achsen
			DWORD wresult = mctl_Reference(AXIS_ALL);
			cerr << "mctl_Reference(AXIS_ALL) ";
			if ((0xFFFF & wresult) == ERR_NOERROR)
			{
				cerr << ": OK\n";
				AXISPOS ax;
				ax.X = 100000; //  µm
				ax.Y = 120000; //  µm
				printf("Bewegung wird gestartet.\n");
				DWORD wresult = mctl_MoveAbs(&ax, sizeof(ax));
				cerr << "mctl_MoveAbs(&ax, sizeof(ax)) ";
				if ((0xFFFF & wresult) == ERR_NOERROR)
				{
					cerr << ": OK\n";
					MCTLSTATUS Status;
					// Warten bis Bewegung beendet ist.
					Status.fInMotion = TRUE;
					while (Status.fInMotion)
					{
						Sleep(30); // 30 ms warten dann Status abfragen
						mctl_GetStatus(&Status, sizeof(Status));
					}
					printf("Bewegung beendet.\n");
				}
				else { cerr << "error code " << wresult << endl; }
			}
			else { cerr << "error code " << wresult << endl; }
		}
		else { cerr << "error code " << wresult << endl; }

		// isel CAN-CNC-Steuerung freigeben
		wresult = mctl_Exit();
		cerr << "mctl_Exit() ";
		if ((0xFFFF & wresult) == ERR_NOERROR)
		{
			cerr << ": OK\n";
		}
		else { cerr << "error code " << wresult << endl; }
	}
	else{cerr << "error code " << wresult << endl;}

	return nRetCode;
}


