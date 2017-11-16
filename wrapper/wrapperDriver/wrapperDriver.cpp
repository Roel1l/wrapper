// wrapperDriver.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include "windows.h"

#include <stdio.h>

#include "mctl.h"
#include "mctlWrapper.h"

using namespace std;

typedef DWORD(*MCTLW_GETVERSION)(LPMCTLVERSION);
typedef DWORD(*MCTLW_XXXVELOCITY)(LPMCTLVELOCITY);
typedef DWORD(*MCTLW_INIT)(char*);
typedef DWORD(*MCTLW_MOVEABS)(LPAXISPOS);
typedef DWORD(*MCTLW_GETSTATUS)(LPMCTLSTATUS);
typedef DWORD(*MCTLW_CPGETBUFFERSTATUS)(LPCPBSTATUS);

int main()
{
	cout << "hya!" << endl;
	cout << "longs are " << sizeof(long) << " bytes" << endl;
	HINSTANCE hInstLibrary = LoadLibraryA("mctlWrapper.dll");
	if (hInstLibrary)
	{
		cout << "got library" << endl;

		MCTLW_INIT _initialize = (MCTLW_INIT)GetProcAddress(hInstLibrary, "mctlw_Initialize");
		if (_initialize)
		{
			_initialize("c:\\CNCworkbench\\Control\\CAN\\CAN_PCI_3_Axis.ini");
		}

		cout << "getversion...." << endl;
		MCTLW_GETVERSION _getVersion = (MCTLW_GETVERSION)GetProcAddress(hInstLibrary, "mctlw_GetVersion");
		if (_getVersion)
		{
			cout << "got function" << endl;
			MCTLVERSION data;
			snprintf(data.szComment, 255, "comments here");
			snprintf(data.szCompanyName, 255, "company here");
			snprintf(data.szDescription, 255, "description here");
			data.dwType = 20;
			DWORD result = _getVersion(&data);
			cout << result << endl;
			cout << data.dwType << endl;
			cout << data.iVerMajor << endl;
			cout << data.iVerMinor << endl;
			cout << data.iVerRelease << endl;
			cout << data.iVerBuilt << endl;
			cout << data.szDescription << endl<<"---------------------"<<endl;
			cout << data.szComment << endl << "---------------------" << endl;
			cout << data.szCompanyName << endl;
		}
		MCTLW_XXXVELOCITY _getVelocity = (MCTLW_XXXVELOCITY)GetProcAddress(hInstLibrary, "mctlw_GetVelocity");
		MCTLW_XXXVELOCITY _setVelocity = (MCTLW_XXXVELOCITY)GetProcAddress(hInstLibrary, "mctlw_SetVelocity");
		if (_getVelocity && _setVelocity)
		{
			cout << "velocity functions found" << endl;
			MCTLVELOCITY data;
			cout<<"calling getVelocity: "<<_getVelocity(&data)<<endl;
			cout << "reset values" << endl;
			cout << data.lNormVel[0] << endl;
			cout << data.lNormVel[1] << endl;
			cout << data.lFastVel[0] << endl;
			cout << data.lFastVel[1] << endl;
			cout << data.lTeachVel[0] << endl;
			cout << data.lTeachVel[1] << endl;
			cout << data.lActVel[0] << endl;
			cout << data.lActVel[1] << endl;

			data.lNormVel[0]=10;
			data.lNormVel[1]=11;
			data.lFastVel[0]=12;
			data.lFastVel[1]=13;
			data.lTeachVel[0]=14;
			data.lTeachVel[1]=15;
			data.lActVel[0]=16;
			data.lActVel[1]=17;
			cout << "calling setVelocity: " << _setVelocity(&data) << endl;

			data.lNormVel[0] = -10;
			data.lNormVel[1] = -11;
			data.lFastVel[0] = -12;
			data.lFastVel[1] = -13;
			data.lTeachVel[0] = -14;
			data.lTeachVel[1] = -15;
			data.lActVel[0] = -16;
			data.lActVel[1] = -17;
			cout << "calling getVelocity: " << _getVelocity(&data) << endl;
			cout << "set values" << endl;
			cout << data.lNormVel[0] << endl;
			cout << data.lNormVel[1] << endl;
			cout << data.lFastVel[0] << endl;
			cout << data.lFastVel[1] << endl;
			cout << data.lTeachVel[0] << endl;
			cout << data.lTeachVel[1] << endl;
			cout << data.lActVel[0] << endl;
			cout << data.lActVel[1] << endl;
		}
		MCTLW_MOVEABS _moveAbs = (MCTLW_MOVEABS)GetProcAddress(hInstLibrary, "mctlw_MoveAbs");
		if (_moveAbs)
		{
			AXISPOS data;
			data.X = 100;
			data.Y = 200;
			data.Z = 300;
			cout << "moveabs returns " << _moveAbs(&data) << endl;
		}
		MCTLW_GETSTATUS _getStatus = (MCTLW_GETSTATUS)GetProcAddress(hInstLibrary, "mctlw_GetStatus");
		if (_getStatus)
		{
			MCTLSTATUS data;
			cout << "getStatus returns " << _getStatus(&data) << endl;
			cout<<data.dwCommon << endl;
			cout<<data.dwExtended << endl;
			cout<<data.dwHWLSNeg << endl;
			cout<<data.dwHWLSPos << endl;
			cout<<data.dwSWLSNeg << endl;
			cout<<data.dwSWLSPos << endl;
		}
		MCTLW_CPGETBUFFERSTATUS _getBufferStatus = (MCTLW_CPGETBUFFERSTATUS)GetProcAddress(hInstLibrary, "mctlw_cp_GetBufferStatus");
		if (_getBufferStatus)
		{
			CPBSTATUS data;
			cout << "getBufferStatus returns " << _getBufferStatus(&data) << endl;
		}
	}
	int x;
	std::cin >> x;

    return 0;
}

