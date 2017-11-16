// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Windows.h>

#include "mctl.h"

#include "mctlWrapper.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	BOOL retval = TRUE;
	static HINSTANCE hInstLibrary;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hInstLibrary = LoadLibraryA("CanApi.dll");

		if (hInstLibrary)
		{
			_setUnits = (MCTL_SETUNITS)GetProcAddress(hInstLibrary, "mctl_SetUnits");
			_initialize = (MCTL_INITIALIZE)GetProcAddress(hInstLibrary, "mctl_Initialize");
			_xit = (MCTL_EXIT)GetProcAddress(hInstLibrary, "mctl_Exit");
			_setup = (MCTL_SETUP)GetProcAddress(hInstLibrary, "mctl_Setup");
			_diagnosis = (MCTL_DIAGNOSIS)GetProcAddress(hInstLibrary, "mctl_Diagnosis");
			_getVersion = (MCTL_GETVERSION)GetProcAddress(hInstLibrary, "mctl_GetVersion");
			_getConfiguration = (MCTL_GETCONFIGURATION)GetProcAddress(hInstLibrary, "mctl_GetConfiguration");
			_getAxisConfiguration = (MCTL_GETAXISCONFIGURATION)GetProcAddress(hInstLibrary, "mctl_GetAxisConfiguration");
			_getStatus = (MCTL_GETSTATUS)GetProcAddress(hInstLibrary, "mctl_GetStatus");
			_getStatusOnEvent = (MCTL_GETSTATUSONEVENT)GetProcAddress(hInstLibrary, "mctl_GetStatusOnEvent");
			_getAxisStatus = (MCTL_GETAXISSTATUS)GetProcAddress(hInstLibrary, "mctl_GetAxisStatus");
			_reset = (MCTL_RESET)GetProcAddress(hInstLibrary, "mctl_Reset");
			_reference = (MCTL_REFERENCE)GetProcAddress(hInstLibrary, "mctl_Reference");
			_referenceBreak = (MCTL_REFERENCEBREAK)GetProcAddress(hInstLibrary, "mctl_ReferenceBreak");
			_setTestMode = (MCTL_SETTESTMODE)GetProcAddress(hInstLibrary, "mctl_SetTestMode");
			_setTeachMode = (MCTL_SETTEACHMODE)GetProcAddress(hInstLibrary, "mctl_SetTeachMode");
			_setPowerState = (MCTL_SETPOWERSTATE)GetProcAddress(hInstLibrary, "mctl_SetPowerState");
			_setVelocity = (MCTL_SETVELOCITY)GetProcAddress(hInstLibrary, "mctl_SetVelocity");
			_getVelocity = (MCTL_GETVELOCITY)GetProcAddress(hInstLibrary, "mctl_GetVelocity");
			_setOverride = (MCTL_SETOVERRIDE)GetProcAddress(hInstLibrary, "mctl_SetOverride");
			_getOverride = (MCTL_GETOVERRIDE)GetProcAddress(hInstLibrary, "mctl_GetOverride");
			_setActPosWnp = (MCTL_SETACTPOSWNP)GetProcAddress(hInstLibrary, "mctl_SetActPosWNP");
			_setWnpAbs = (MCTL_SETWNPABS)GetProcAddress(hInstLibrary, "mctl_SetWNPAbs");
			_setWnpRel = (MCTL_SETWNPREL)GetProcAddress(hInstLibrary, "mctl_SetWNPRel");
			_getWnp = (MCTL_GETWNP)GetProcAddress(hInstLibrary, "mctl_GetWNP");
			_getWnpStatus = (MCTL_GETWNPSTATUS)GetProcAddress(hInstLibrary, "mctl_GetWNPStatus");
			_clearWnp = (MCTL_CLEARWNP)GetProcAddress(hInstLibrary, "mctl_ClearWNP");
			_setSwls = (MCTL_SETSWLS)GetProcAddress(hInstLibrary, "mctl_SetSWLS");
			_getSwlsStatus = (MCTL_GETSWLSSTATUS)GetProcAddress(hInstLibrary, "mctl_GetSWLSStatus");
			_enableSwls = (MCTL_ENABLESWLS)GetProcAddress(hInstLibrary, "mctl_EnableSWLS");
			_clearSwls = (MCTL_CLEARSWLS)GetProcAddress(hInstLibrary, "mctl_ClearSWLS");
			_moveAbs = (MCTL_MOVEABS)GetProcAddress(hInstLibrary, "mctl_MoveAbs");
			_moveRel = (MCTL_MOVEREL)GetProcAddress(hInstLibrary, "mctl_MoveRel");
			_moveRelUntilPortEvent = (MCTL_MOVERELUNTILPORTEVENT)GetProcAddress(hInstLibrary, "mctl_MoveRelUntilPortEvent");
			_fastAbs = (MCTL_FASTABS)GetProcAddress(hInstLibrary, "mctl_FastAbs");
			_fastRel = (MCTL_FASTREL)GetProcAddress(hInstLibrary, "mctl_FastRel");
			_circleAbs = (MCTL_CIRCLEABS)GetProcAddress(hInstLibrary, "mctl_CircleAbs");
			_circleRel = (MCTL_CIRCLEREL)GetProcAddress(hInstLibrary, "mctl_CircleRel");
			_helixAbs = (MCTL_HELIXABS)GetProcAddress(hInstLibrary, "mctl_HelixAbs");
			_helixRel = (MCTL_HELIXREL)GetProcAddress(hInstLibrary, "mctl_HelixRel");
			_splineAbs = (MCTL_SPLINEABS)GetProcAddress(hInstLibrary, "mctl_SplineAbs");
			_splineRel = (MCTL_SPLINEREL)GetProcAddress(hInstLibrary, "mctl_SplineRel");
			_bezierAbs = (MCTL_BEZIERABS)GetProcAddress(hInstLibrary, "mctl_BezierAbs");
			_bezierRel = (MCTL_BEZIERREL)GetProcAddress(hInstLibrary, "mctl_BezierRel");
			_getPosition = (MCTL_GETPOSITION)GetProcAddress(hInstLibrary, "mctl_GetPosition");
			_getDestinationPos = (MCTL_GETDESTINATIONPOS)GetProcAddress(hInstLibrary, "mctl_GetDestinationPos");
			_setMotionState = (MCTL_SETMOTIONSTATE)GetProcAddress(hInstLibrary, "mctl_SetMotionState");
			_leaveHwls = (MCTL_LEAVEHWLS)GetProcAddress(hInstLibrary, "mctl_LeaveHWLS");
			_hwlsBridge = (MCTL_HWLSBRIDGE)GetProcAddress(hInstLibrary, "mctl_HWLSBridge");
			_setDrillParam = (MCTL_SETDRILLPARAM)GetProcAddress(hInstLibrary, "mctl_SetDrillParam");
			_getDrillParam = (MCTL_GETDRILLPARAM)GetProcAddress(hInstLibrary, "mctl_GetDrillParam");
			_drill = (MCTL_DRILL)GetProcAddress(hInstLibrary, "mctl_Drill");
			_operate = (MCTL_OPERATE)GetProcAddress(hInstLibrary, "mctl_Operate");
			_inputBit = (MCTL_INPUTBIT)GetProcAddress(hInstLibrary, "mctl_InputBit");
			_inputByte = (MCTL_INPUTBYTE)GetProcAddress(hInstLibrary, "mctl_InputByte");
			_inputWord = (MCTL_INPUTWORD)GetProcAddress(hInstLibrary, "mctl_InputWord");
			_inputDWord = (MCTL_INPUTDWORD)GetProcAddress(hInstLibrary, "mctl_InputDWord");
			_outputBit = (MCTL_OUTPUTBIT)GetProcAddress(hInstLibrary, "mctl_OutputBit");
			_outputByte = (MCTL_OUTPUTBYTE)GetProcAddress(hInstLibrary, "mctl_OutputByte");
			_outputWord = (MCTL_OUTPUTWORD)GetProcAddress(hInstLibrary, "mctl_OutputWord");
			_outputDWord = (MCTL_OUTPUTDWORD)GetProcAddress(hInstLibrary, "mctl_OutputDWord");
			_readOutputBit = (MCTL_READOUTPUTBIT)GetProcAddress(hInstLibrary, "mctl_ReadOutputBit");
			_readOutputByte = (MCTL_READOUTPUTBYTE)GetProcAddress(hInstLibrary, "mctl_ReadOutputByte");
			_readOutputWord = (MCTL_READOUTPUTWORD)GetProcAddress(hInstLibrary, "mctl_ReadOutputWord");
			_readOutputDWord = (MCTL_READOUTPUTDWORD)GetProcAddress(hInstLibrary, "mctl_ReadOutputDWord");
			_cp_setBufferSize = (MCTL_CP_SETBUFFERSIZE)GetProcAddress(hInstLibrary, "mctl_cp_SetBufferSize");
			_cp_enablePath = (MCTL_CP_ENABLEPATH)GetProcAddress(hInstLibrary, "mctl_cp_EnablePath");
			_cp_disablePath = (MCTL_CP_DISABLEPATH)GetProcAddress(hInstLibrary, "mctl_cp_DisablePath");
			_cp_startPath = (MCTL_CP_STARTPATH)GetProcAddress(hInstLibrary, "mctl_cp_StartPath");
			_cp_endPath = (MCTL_CP_ENDPATH)GetProcAddress(hInstLibrary, "mctl_cp_EndPath");
			_cp_getBufferStatus = (MCTL_CP_GETBUFFERSTATUS)GetProcAddress(hInstLibrary, "mctl_cp_GetBufferStatus");
			_cp_setVelocity = (MCTL_CP_SETVELOCITY)GetProcAddress(hInstLibrary, "mctl_cp_SetVelocity");
			_cp_outputBit = (MCTL_CP_OUTPUTBIT)GetProcAddress(hInstLibrary, "mctl_cp_OutputBit");
			_cp_outputByte = (MCTL_CP_OUTPUTBYTE)GetProcAddress(hInstLibrary, "mctl_cp_OutputByte");
			_cp_outputWord = (MCTL_CP_OUTPUTWORD)GetProcAddress(hInstLibrary, "mctl_cp_OutputWord");
			_cp_outputDWord = (MCTL_CP_OUTPUTDWORD)GetProcAddress(hInstLibrary, "mctl_cp_OutputDWord");
		}
		else
		{
			retval = FALSE;
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (hInstLibrary)
		{
			FreeLibrary(hInstLibrary);
		}
		break;
	}
	return retval;
}

