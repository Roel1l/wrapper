// mctlWrapper.cpp : Defines the exported functions for the DLL application.
//

#include <iostream>

#include "stdafx.h"

#include "mctl.h"

#include "mctlWrapper.h"


extern "C"
{
//declare the function pointers, so the dllMain function can fill them, and they can be used below
	MCTL_SETUNITS _setUnits;
	MCTL_INITIALIZE _initialize;
	MCTL_EXIT _xit;
	MCTL_SETUP _setup;
	MCTL_DIAGNOSIS _diagnosis;
	MCTL_GETVERSION _getVersion;
	MCTL_GETCONFIGURATION _getConfiguration;
	MCTL_GETAXISCONFIGURATION _getAxisConfiguration;
	MCTL_GETSTATUS _getStatus;
	MCTL_GETSTATUSONEVENT _getStatusOnEvent;
	MCTL_GETAXISSTATUS _getAxisStatus;
	MCTL_RESET _reset;
	MCTL_REFERENCE _reference;
	MCTL_REFERENCEBREAK _referenceBreak;
	MCTL_SETTESTMODE _setTestMode;
	MCTL_SETTEACHMODE _setTeachMode;
	MCTL_SETPOWERSTATE _setPowerState;
	MCTL_SETVELOCITY _setVelocity;
	MCTL_GETVELOCITY _getVelocity;
	MCTL_SETOVERRIDE _setOverride;
	MCTL_GETOVERRIDE _getOverride;
	MCTL_SETACTPOSWNP _setActPosWnp;
	MCTL_SETWNPABS _setWnpAbs;
	MCTL_SETWNPREL _setWnpRel;
	MCTL_GETWNP _getWnp;
	MCTL_GETWNPSTATUS _getWnpStatus;
	MCTL_CLEARWNP _clearWnp;
	MCTL_SETSWLS _setSwls;
	MCTL_GETSWLSSTATUS _getSwlsStatus;
	MCTL_ENABLESWLS _enableSwls;
	MCTL_CLEARSWLS _clearSwls;
	MCTL_MOVEABS _moveAbs;
	MCTL_MOVEREL _moveRel;
	MCTL_MOVERELUNTILPORTEVENT _moveRelUntilPortEvent;
	MCTL_FASTABS _fastAbs;
	MCTL_FASTREL _fastRel;
	MCTL_CIRCLEABS _circleAbs;
	MCTL_CIRCLEREL _circleRel;
	MCTL_HELIXABS _helixAbs;
	MCTL_HELIXREL _helixRel;
	MCTL_SPLINEABS _splineAbs;
	MCTL_SPLINEREL _splineRel;
	MCTL_BEZIERABS _bezierAbs;
	MCTL_BEZIERREL _bezierRel;
	MCTL_GETPOSITION _getPosition;
	MCTL_GETDESTINATIONPOS _getDestinationPos;
	MCTL_SETMOTIONSTATE _setMotionState;
	MCTL_LEAVEHWLS _leaveHwls;
	MCTL_HWLSBRIDGE _hwlsBridge;
	MCTL_SETDRILLPARAM _setDrillParam;
	MCTL_GETDRILLPARAM _getDrillParam;
	MCTL_DRILL _drill;
	MCTL_OPERATE _operate;
	MCTL_INPUTBIT _inputBit;
	MCTL_INPUTBYTE _inputByte;
	MCTL_INPUTWORD _inputWord;
	MCTL_INPUTDWORD _inputDWord;
	MCTL_OUTPUTBIT _outputBit;
	MCTL_OUTPUTBYTE _outputByte;
	MCTL_OUTPUTWORD _outputWord;
	MCTL_OUTPUTDWORD _outputDWord;
	MCTL_READOUTPUTBIT _readOutputBit;
	MCTL_READOUTPUTBYTE _readOutputByte;
	MCTL_READOUTPUTWORD _readOutputWord;
	MCTL_READOUTPUTDWORD _readOutputDWord;
	MCTL_CP_SETBUFFERSIZE _cp_setBufferSize;
	MCTL_CP_ENABLEPATH _cp_enablePath;
	MCTL_CP_DISABLEPATH _cp_disablePath;
	MCTL_CP_STARTPATH _cp_startPath;
	MCTL_CP_ENDPATH _cp_endPath;
	MCTL_CP_GETBUFFERSTATUS _cp_getBufferStatus;
	MCTL_CP_SETVELOCITY _cp_setVelocity;
	MCTL_CP_OUTPUTBIT _cp_outputBit;
	MCTL_CP_OUTPUTBYTE _cp_outputByte;
	MCTL_CP_OUTPUTWORD _cp_outputWord;
	MCTL_CP_OUTPUTDWORD _cp_outputDWord;

//Implement the actual wrapper functions. Straight wrappers are prefixed mctlw_,
//wrappers which accept individual parameters for input fields in structs are prefixed mctlws_

	//  DWORD MCTL_DLLFUNC mctl_SetUnits(LPVOID pUnit, DWORD dwSize);

	/*no information on how to handle this function
	  TODO: figure out whast to do
	*/

	//  DWORD MCTL_DLLFUNC mctl_Initialize(char *szInitFile);
	DWORD MCTLWRAPPER_API mctlw_Initialize(char *szInitFile)
	{
		DWORD retval = -1;
		if (_initialize)
		{
			retval = _initialize(szInitFile);
		}
		return retval;
	}
	
	//  DWORD MCTL_DLLFUNC mctl_Exit(void);
	DWORD MCTLWRAPPER_API mctlw_Exit(void)
	{
		DWORD retval = -1;
		if (_initialize)
		{
			retval = _xit();  //no typo, _exit is in use by the runtime environment, _xit used instead
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_Setup(void);
	DWORD MCTLWRAPPER_API mctlw_Setup(void)
	{
		DWORD retval = -1;
		if (_initialize)
		{
			retval = _setup();
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_Diagnosis(void);
	DWORD MCTLWRAPPER_API mctlw_Diagnosis(void)
	{
		DWORD retval = -1;
		if (_initialize)
		{
			retval = _diagnosis();
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetVersion(LPMCTLVERSION lpMctlVer, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetVersion(LPMCTLVERSION lpMctlVer)
	{
		DWORD retval = -1;
		if (_initialize)
		{
			retval = _getVersion(lpMctlVer, sizeof(MCTLVERSION));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_GetVersion(DWORD type, LPMCTLVERSION lpMctlVer)
	{
		DWORD retval = -1;
		if (_initialize)
		{
			if (lpMctlVer)
			{
				lpMctlVer->dwType = type;
				retval = _getVersion(lpMctlVer, sizeof(MCTLVERSION));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetConfiguration(LPMCTLCONFIG lpMctlCfg, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetConfiguration(LPMCTLCONFIG lpMctlCfg)
	{
		DWORD retval = -1;
		if (_getConfiguration)
		{
			retval = _getConfiguration(lpMctlCfg, sizeof(MCTLCONFIG));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetAxisConfiguration(UINT nAxis, LPAXISCONFIG lpAxisCfg, DWORD dwSize);	
	//Function does not exist in CanApi.dll. No wrapper created.

	//  DWORD MCTL_DLLFUNC mctl_GetStatus(LPMCTLSTATUS lpMctlStatus, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetStatus(LPMCTLSTATUS lpMctlStatus)
	{
		DWORD retval = -1;
		if (_getStatus)
		{
			retval = _getStatus(lpMctlStatus, sizeof(MCTLSTATUS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetStatusOnEvent(DWORD dwEvent, DWORD dwMilliSeconds, LPMCTLSTATUS lpMctlStatus, DWORD dwSize);
	//Function does not exist in CanApi.dll. No wrapper created.

	//  DWORD MCTL_DLLFUNC mctl_GetAxisStatus(UINT nAxis, LPAXISSTATUS lpAxisStatus, DWORD dwSize);	
	DWORD MCTLWRAPPER_API mctlw_GetAxisStatus(UINT nAxis, LPAXISSTATUS lpAxisStatus)
	{
		DWORD retval = -1;
		if (_getAxisStatus)
		{
			retval = _getAxisStatus(nAxis, lpAxisStatus, sizeof(AXISSTATUS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_Reset(void);
	DWORD MCTLWRAPPER_API mctlw_Reset(void)
	{
		DWORD retval = -1;
		if (_reset)
		{
			retval = _reset();
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_Reference(DWORD dwAxis);																// Reference run, axes AXIS_X, AXIS_Y,...
	DWORD MCTLWRAPPER_API mctlw_Reference(DWORD dwAxis)
	{
		DWORD retval = -1;
		if (_reference)
		{
			retval = _reference(dwAxis);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_ReferenceBreak(void);																	// KP New 02.10.2003 mctl_ReferenceBreak() / CAN Bus Control
	DWORD MCTLWRAPPER_API mctlw_ReferenceBreak(void)
	{
		DWORD retval = -1;
		if (_referenceBreak)
		{
			retval = _referenceBreak();
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetTestMode(DWORD dwOnOff);
	DWORD MCTLWRAPPER_API mctlw_SetTestMode(DWORD dwOnOff)
	{
		DWORD retval = -1;
		if (_setTestMode)
		{
			retval = _setTestMode(dwOnOff);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetTeachMode(DWORD dwOnOff);
	DWORD MCTLWRAPPER_API mctlw_SetTeachMode(DWORD dwOnOff)
	{
		DWORD retval = -1;
		if (_setTeachMode)
		{
			retval = _setTeachMode(dwOnOff);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetPowerState(DWORD dwOnOff);
	DWORD MCTLWRAPPER_API mctlw_SetPowerState(DWORD dwOnOff)
	{
		DWORD retval = -1;
		if (_setPowerState)
		{
			retval = _setPowerState(dwOnOff);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetVelocity(LPMCTLVELOCITY lpMctlVel, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_SetVelocity(LPMCTLVELOCITY lpMctlVel)
	{
		DWORD retval = -1;
		if (_setVelocity)
		{
			retval = _setVelocity(lpMctlVel, sizeof(MCTLVELOCITY));
		}
		return retval;
	}

	//TODO: is structure modified?
	DWORD MCTLWRAPPER_API mctlws_SetVelocity(long normRel, long normRot, long fastRel, long fastRot, long teachRel, long techRot, long actualRel, long actualRot, LPMCTLVELOCITY lpMctlVel)
	{
		DWORD retval = -1;
		if (_setVelocity)
		{
			if (lpMctlVel)
			{
				lpMctlVel->lNormVel[0] = normRel;
				lpMctlVel->lNormVel[1] = normRot;
				lpMctlVel->lFastVel[0] = fastRel;
				lpMctlVel->lFastVel[1] = fastRot;
				lpMctlVel->lTeachVel[0] = teachRel;
				lpMctlVel->lTeachVel[1] = techRot;
				lpMctlVel->lActVel[0] = actualRel;
				lpMctlVel->lActVel[1] = actualRot;
				retval = _setVelocity(lpMctlVel, sizeof(MCTLVELOCITY));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetVelocity(LPMCTLVELOCITY lpMctlVel, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetVelocity(LPMCTLVELOCITY lpMctlVel)
	{
		DWORD retval = -1;
		if (_getVelocity)
		{
			retval = _getVelocity(lpMctlVel, sizeof(MCTLVELOCITY));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetOverride(long lOverride);
	DWORD MCTLWRAPPER_API mctlw_SetOverride(long lOverride)
	{
		DWORD retval = -1;
		if (_setOverride)
		{
			retval = _setOverride(lOverride);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetOverride(LPLONG lpOverride);
	DWORD MCTLWRAPPER_API mctlw_getOverride(LPLONG lpOverride)
	{
		DWORD retval = -1;
		if (_getOverride)
		{
			retval = _getOverride(lpOverride);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetActPosWNP(void);
	DWORD MCTLWRAPPER_API mctlw_SetActPosWNP(void)
	{
		DWORD retval = -1;
		if (_setActPosWnp)
		{
			retval = _setActPosWnp();
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetWNPAbs(LPAXISPOS AbsWPZero, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_SetWNPAbs(LPAXISPOS AbsWPZero)
	{
		DWORD retval = -1;
		if (_setWnpAbs)
		{
			retval = _setWnpAbs(AbsWPZero, sizeof(AXISPOS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_SetWNPAbs(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, LPAXISPOS AbsWPZero)
	{
		DWORD retval = -1;
		if (_setWnpAbs)
		{
			if (AbsWPZero)
			{
				AbsWPZero->A = A;
				AbsWPZero->B = B;
				AbsWPZero->C = C;
				AbsWPZero->U = U;
				AbsWPZero->V = V;
				AbsWPZero->W = W;
				AbsWPZero->X = X;
				AbsWPZero->Y = Y;
				AbsWPZero->Z = Z;
				retval = _setWnpAbs(AbsWPZero, sizeof(AXISPOS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetWNPRel(LPAXISPOS RelWPZero, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_SetWNPRel(LPAXISPOS RelWPZero)
	{
		DWORD retval = -1;
		if (_setWnpRel)
		{
			retval = _setWnpRel(RelWPZero, sizeof(AXISPOS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_SetWNPRel(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, LPAXISPOS RelWPZero)
	{
		DWORD retval = -1;
		if (_setWnpRel)
		{
			if (RelWPZero)
			{
				RelWPZero->A = A;
				RelWPZero->B = B;
				RelWPZero->C = C;
				RelWPZero->U = U;
				RelWPZero->V = V;
				RelWPZero->W = W;
				RelWPZero->X = X;
				RelWPZero->Y = Y;
				RelWPZero->Z = Z;
				retval = _setWnpRel(RelWPZero, sizeof(AXISPOS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetWNP(LPAXISPOS WPZero, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetWNP(LPAXISPOS WPZero)
	{
		DWORD retval = -1;
		if (_getWnp)
		{
			retval = _getWnp(WPZero, sizeof(AXISPOS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetWNPStatus(LPWNPSTATUS WNPStatus, DWORD dwSize);				// KP New 22.01.2002
	DWORD MCTLWRAPPER_API mctlw_GetWNPStatus(LPWNPSTATUS WNPStatus)
	{
		DWORD retval = -1;
		if (_getWnpStatus)
		{
			retval = _getWnpStatus(WNPStatus, sizeof(WNPSTATUS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_ClearWNP(void);
	DWORD MCTLWRAPPER_API mctlw_ClearWNP(void)
	{
		DWORD retval = -1;
		if (_clearWnp)
		{
			retval = _clearWnp();
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetSWLS(LPSWLSSTATUS SWLSAbs, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_SetSWLS(LPSWLSSTATUS SWLSAbs)
	{
		DWORD retval = -1;
		if (_setSwls)
		{
			retval = _setSwls(SWLSAbs, sizeof(SWLSSTATUS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_SetSWLS(DWORD dwEnabled, DWORD dwSWLSNeg, DWORD dwSWLSPos,
			long NegX, long NegY, long NegZ, long NegA, long NegB, long NegC, long NegU, long NegV, long NegW,
			long PosX, long PosY, long PosZ, long PosA, long PosB, long PosC, long PosU, long PosV, long PosW,
			BOOL fActive, LPSWLSSTATUS SWLSAbs)
	{
		DWORD retval = -1;
		if (_setSwls)
		{
			if (SWLSAbs)
			{
				SWLSAbs->dwEnabled = dwEnabled;
				SWLSAbs->dwSWLSNeg = dwSWLSNeg;
				SWLSAbs->dwSWLSPos = dwSWLSPos;
				SWLSAbs->fActive = fActive;
				SWLSAbs->Neg.A = NegA;
				SWLSAbs->Neg.B = NegB;
				SWLSAbs->Neg.C = NegC;
				SWLSAbs->Neg.U = NegU;
				SWLSAbs->Neg.V = NegV;
				SWLSAbs->Neg.W = NegW;
				SWLSAbs->Neg.X = NegX;
				SWLSAbs->Neg.Y = NegY;
				SWLSAbs->Neg.Z = NegZ;
				SWLSAbs->Pos.A = PosA;
				SWLSAbs->Pos.B = PosB;
				SWLSAbs->Pos.C = PosC;
				SWLSAbs->Pos.U = PosU;
				SWLSAbs->Pos.V = PosV;
				SWLSAbs->Pos.W = PosW;
				SWLSAbs->Pos.X = PosX;
				SWLSAbs->Pos.Y = PosY;
				SWLSAbs->Pos.Z = PosZ;
				retval = _setSwls(SWLSAbs, sizeof(SWLSSTATUS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetSWLSStatus(LPSWLSSTATUS SWLSStatus, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetSWLSStatus(LPSWLSSTATUS SWLSStatus)
	{
		DWORD retval = -1;
		if (_getSwlsStatus)
		{
			retval = _getSwlsStatus(SWLSStatus, sizeof(SWLSSTATUS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_EnableSWLS(DWORD dwAxis, DWORD dwOptions);
	DWORD MCTLWRAPPER_API mctlw_EnableSWLS(DWORD dwAxis, DWORD dwOptions)
	{
		DWORD retval = -1;
		if (_enableSwls)
		{
			retval = _enableSwls(dwAxis, dwOptions);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_ClearSWLS(void);
	DWORD MCTLWRAPPER_API mctlw_ClearSWLS(void)
	{
		DWORD retval = -1;
		if (_clearSwls)
		{
			retval = _clearSwls();
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_MoveAbs(LPAXISPOS lpAbsPos, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_MoveAbs(LPAXISPOS lpAbsPos)
	{
		DWORD retval = -1;
		if (_moveAbs)
		{
			retval = _moveAbs(lpAbsPos, sizeof(AXISPOS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_MoveAbs(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, LPAXISPOS lpAbsPos)
	{
		DWORD retval = -1;
		if (_moveAbs)
		{
			if (lpAbsPos)
			{
				lpAbsPos->A = A;
				lpAbsPos->B = B;
				lpAbsPos->C = C;
				lpAbsPos->U = U;
				lpAbsPos->V = V;
				lpAbsPos->W = W;
				lpAbsPos->X = X;
				lpAbsPos->Y = Y;
				lpAbsPos->Z = Z;
				retval = _moveAbs(lpAbsPos, sizeof(AXISPOS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_MoveRel(LPAXISPOS lpRelPos, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_MoveRel(LPAXISPOS lpRelPos)
	{
		DWORD retval = -1;
		if (_moveRel)
		{
			retval = _moveRel(lpRelPos, sizeof(AXISPOS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_MoveRel(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, LPAXISPOS lpRelPos)
	{
		DWORD retval = -1;
		if (_moveRel)
		{
			if (lpRelPos)
			{
				lpRelPos->A = A;
				lpRelPos->B = B;
				lpRelPos->C = C;
				lpRelPos->U = U;
				lpRelPos->V = V;
				lpRelPos->W = W;
				lpRelPos->X = X;
				lpRelPos->Y = Y;
				lpRelPos->Z = Z;
				retval = _moveRel(lpRelPos, sizeof(AXISPOS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_MoveRelUntilPortEvent(LPAXISPOS lpRelPos, DWORD dwSize, DWORD dwMask, DWORD dwValue); 
	DWORD MCTLWRAPPER_API mctlw_MoveRelUntilPortEvent(LPAXISPOS lpRelPos, DWORD dwMask, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_moveRelUntilPortEvent)
		{
			retval = _moveRelUntilPortEvent(lpRelPos, sizeof(AXISPOS), dwMask, dwValue);
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_MoveRelUntilPortEvent(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, DWORD dwMask, DWORD dwValue, LPAXISPOS lpRelPos)
	{
		DWORD retval = -1;
		if (_moveRelUntilPortEvent)
		{
			if (lpRelPos)
			{
				lpRelPos->A = A;
				lpRelPos->B = B;
				lpRelPos->C = C;
				lpRelPos->U = U;
				lpRelPos->V = V;
				lpRelPos->W = W;
				lpRelPos->X = X;
				lpRelPos->Y = Y;
				lpRelPos->Z = Z;
				retval = _moveRelUntilPortEvent(lpRelPos, sizeof(AXISPOS), dwMask, dwValue);
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_FastAbs(LPAXISPOS lpAbsPos, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_FastAbs(LPAXISPOS lpAbsPos)
	{
		DWORD retval = -1;
		if (_fastAbs)
		{
			retval = _fastAbs(lpAbsPos, sizeof(AXISPOS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_FastAbs(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, LPAXISPOS lpAbsPos)
	{
		DWORD retval = -1;
		if (_fastAbs)
		{
			if (lpAbsPos)
			{
				lpAbsPos->A = A;
				lpAbsPos->B = B;
				lpAbsPos->C = C;
				lpAbsPos->U = U;
				lpAbsPos->V = V;
				lpAbsPos->W = W;
				lpAbsPos->X = X;
				lpAbsPos->Y = Y;
				lpAbsPos->Z = Z;
				retval = _fastAbs(lpAbsPos, sizeof(AXISPOS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_FastRel(LPAXISPOS lpRelPos, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_FastRel(LPAXISPOS lpRelPos)
	{
		DWORD retval = -1;
		if (_fastRel)
		{
			retval = _fastRel(lpRelPos, sizeof(AXISPOS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_FastRel(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, LPAXISPOS lpRelPos)
	{
		DWORD retval = -1;
		if (_fastRel)
		{
			if (lpRelPos)
			{
				lpRelPos->A = A;
				lpRelPos->B = B;
				lpRelPos->C = C;
				lpRelPos->U = U;
				lpRelPos->V = V;
				lpRelPos->W = W;
				lpRelPos->X = X;
				lpRelPos->Y = Y;
				lpRelPos->Z = Z;
				retval = _fastRel(lpRelPos, sizeof(AXISPOS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_CircleAbs(LPCIRCLEPARAM lpAbsCiParam, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_CircleAbs(LPCIRCLEPARAM lpAbsCiParam)
	{
		DWORD retval = -1;
		if (_circleAbs)
		{
			retval = _circleAbs(lpAbsCiParam, sizeof(CIRCLEPARAM));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_CircleAbs(DWORD dwPlane, DWORD dwDirection, long  lCenter1, long  lCenter2,
			long  lEndPosX, long  lEndPosY, long  lEndPosZ, long  lEndPosA, long  lEndPosB, long  lEndPosC,
			long  lEndPosU, long  lEndPosV, long  lEndPosW, LPCIRCLEPARAM lpAbsCiParam)
	{
		DWORD retval = -1;
		if (_circleAbs)
		{
			if (lpAbsCiParam)
			{
				lpAbsCiParam ->dwPlane = dwPlane;
				lpAbsCiParam ->dwDirection = dwDirection;
				lpAbsCiParam ->lCenter1 = lCenter1;
				lpAbsCiParam ->lCenter2 = lCenter2;
				lpAbsCiParam ->lEndPosA = lEndPosA;
				lpAbsCiParam ->lEndPosB = lEndPosB;
				lpAbsCiParam ->lEndPosC = lEndPosC;
				lpAbsCiParam ->lEndPosU = lEndPosU;
				lpAbsCiParam ->lEndPosV = lEndPosV;
				lpAbsCiParam ->lEndPosW = lEndPosW;
				lpAbsCiParam ->lEndPosX = lEndPosX;
				lpAbsCiParam ->lEndPosY = lEndPosY;
				lpAbsCiParam ->lEndPosZ = lEndPosZ;
				retval = _circleAbs(lpAbsCiParam, sizeof(CIRCLEPARAM));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_CircleRel(LPCIRCLEPARAM lpRelCiParam, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_CircleRel(LPCIRCLEPARAM lpRelCiParam)
	{
		DWORD retval = -1;
		if (_circleRel)
		{
			retval = _circleRel(lpRelCiParam, sizeof(CIRCLEPARAM));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_CircleRel(DWORD dwPlane, DWORD dwDirection, long  lCenter1, long  lCenter2,
		long  lEndPosX, long  lEndPosY, long  lEndPosZ, long  lEndPosA, long  lEndPosB, long  lEndPosC,
		long  lEndPosU, long  lEndPosV, long  lEndPosW, LPCIRCLEPARAM lpRelCiParam)
	{
		DWORD retval = -1;
		if (_circleRel)
		{
			if (lpRelCiParam)
			{
				lpRelCiParam->dwPlane = dwPlane;
				lpRelCiParam->dwDirection = dwDirection;
				lpRelCiParam->lCenter1 = lCenter1;
				lpRelCiParam->lCenter2 = lCenter2;
				lpRelCiParam->lEndPosA = lEndPosA;
				lpRelCiParam->lEndPosB = lEndPosB;
				lpRelCiParam->lEndPosC = lEndPosC;
				lpRelCiParam->lEndPosU = lEndPosU;
				lpRelCiParam->lEndPosV = lEndPosV;
				lpRelCiParam->lEndPosW = lEndPosW;
				lpRelCiParam->lEndPosX = lEndPosX;
				lpRelCiParam->lEndPosY = lEndPosY;
				lpRelCiParam->lEndPosZ = lEndPosZ;
				retval = _circleRel(lpRelCiParam, sizeof(CIRCLEPARAM));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_HelixAbs(LPHELIXPARAM lpAbsHlxParam, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_HelixAbs(LPHELIXPARAM lpAbsHlxParam)
	{
		DWORD retval = -1;
		if (_helixAbs)
		{
			retval = _helixAbs(lpAbsHlxParam, sizeof(HELIXPARAM));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_HelixAbs(DWORD dwPlane, DWORD dwDirection, long  lCenter1, long  lCenter2,
		long  lEndPosX, long  lEndPosY, long  lEndPosZ, long  lEndPosA, long  lEndPosB, long  lEndPosC,
		long  lEndPosU, long  lEndPosV, long  lEndPosW, LPHELIXPARAM lpAbsHlxParam)
	{
		DWORD retval = -1;
		if (_helixAbs)
		{
			if (lpAbsHlxParam)
			{
				lpAbsHlxParam->dwPlane = dwPlane;
				lpAbsHlxParam->dwDirection = dwDirection;
				lpAbsHlxParam->lCenter1 = lCenter1;
				lpAbsHlxParam->lCenter2 = lCenter2;
				lpAbsHlxParam->lEndPosA = lEndPosA;
				lpAbsHlxParam->lEndPosB = lEndPosB;
				lpAbsHlxParam->lEndPosC = lEndPosC;
				lpAbsHlxParam->lEndPosU = lEndPosU;
				lpAbsHlxParam->lEndPosV = lEndPosV;
				lpAbsHlxParam->lEndPosW = lEndPosW;
				lpAbsHlxParam->lEndPosX = lEndPosX;
				lpAbsHlxParam->lEndPosY = lEndPosY;
				lpAbsHlxParam->lEndPosZ = lEndPosZ;
				retval = _helixAbs(lpAbsHlxParam, sizeof(HELIXPARAM));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_HelixRel(LPHELIXPARAM lpRelHlxParam, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_HelixRel(LPHELIXPARAM lpRelHlxParam)
	{
		DWORD retval = -1;
		if (_helixRel)
		{
			retval = _helixRel(lpRelHlxParam, sizeof(HELIXPARAM));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_HelixRel(DWORD dwPlane, DWORD dwDirection, long  lCenter1, long  lCenter2,
		long  lEndPosX, long  lEndPosY, long  lEndPosZ, long  lEndPosA, long  lEndPosB, long  lEndPosC,
		long  lEndPosU, long  lEndPosV, long  lEndPosW, LPHELIXPARAM lpRelHlxParam)
	{
		DWORD retval = -1;
		if (_helixRel)
		{
			if (lpRelHlxParam)
			{
				lpRelHlxParam->dwPlane = dwPlane;
				lpRelHlxParam->dwDirection = dwDirection;
				lpRelHlxParam->lCenter1 = lCenter1;
				lpRelHlxParam->lCenter2 = lCenter2;
				lpRelHlxParam->lEndPosA = lEndPosA;
				lpRelHlxParam->lEndPosB = lEndPosB;
				lpRelHlxParam->lEndPosC = lEndPosC;
				lpRelHlxParam->lEndPosU = lEndPosU;
				lpRelHlxParam->lEndPosV = lEndPosV;
				lpRelHlxParam->lEndPosW = lEndPosW;
				lpRelHlxParam->lEndPosX = lEndPosX;
				lpRelHlxParam->lEndPosY = lEndPosY;
				lpRelHlxParam->lEndPosZ = lEndPosZ;
				retval = _helixRel(lpRelHlxParam, sizeof(HELIXPARAM));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SplineAbs(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
	//  DWORD MCTL_DLLFUNC mctl_SplineRel(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
	//  DWORD MCTL_DLLFUNC mctl_BezierAbs(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
	//  DWORD MCTL_DLLFUNC mctl_BezierRel(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
	
	/*  I strongly suspect these four functions take an array of AXISPOS as input, not a single position.
	    I have no idea how to handle this on the Mathematica side. No wrappers written.
		TODO: figure out what to do with these
	*/

	//  DWORD MCTL_DLLFUNC mctl_GetPosition(LPAXISPOS lpPos, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetPosition(LPAXISPOS lpPos)
	{
		DWORD retval = -1;
		if (_getPosition)
		{
			retval = _getPosition(lpPos, sizeof(AXISPOS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetDestinationPos(LPAXISPOS lpDestPos, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetDestinationPos(LPAXISPOS lpDestPos)
	{
		DWORD retval = -1;
		if (_getDestinationPos)
		{
			retval = _getDestinationPos(lpDestPos, sizeof(AXISPOS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetMotionState(DWORD dwState);
	DWORD MCTLWRAPPER_API mctlw_SetMotionState(DWORD dwState)
	{
		DWORD retval = -1;
		if (_setMotionState)
		{
			retval = _setMotionState(dwState);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_LeaveHWLS(DWORD dwAxis, LPVOID lpParam);

	/*no information on how to handle this function
	TODO: figure out whast to do
	*/

	//  DWORD MCTL_DLLFUNC mctl_HWLSBridge(DWORD dwOnOff);
	DWORD MCTLWRAPPER_API mctlw_HWLSBridge(DWORD dwOnOff)
	{
		DWORD retval = -1;
		if (_hwlsBridge)
		{
			retval = _hwlsBridge(dwOnOff);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_SetDrillParam(LPDRILLPARAM lpDrillParam, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_SetDrillParam(LPDRILLPARAM lpDrillParam)
	{
		DWORD retval = -1;
		if (_setDrillParam)
		{
			retval = _setDrillParam(lpDrillParam, sizeof(DRILLPARAM));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_SetDrillParam(DWORD dwDrillCycle, long lRefHeight, long lDepth, long lDelay,
			long lNormVel, long lFastVel, long lFirstIncrDepth, long lOtherIncrDepth, long lIncrDepthDecr,
			long lIncrRetreat, long lRetreat, long lSecurityHeight, DWORD dwPlane, DWORD dwDirection, LPDRILLPARAM lpDrillParam)
	{
		DWORD retval = -1;
		if (_setDrillParam)
		{
			if (lpDrillParam)
			{
				lpDrillParam ->dwDirection = dwDirection;
				lpDrillParam ->dwDrillCycle = dwDrillCycle;
				lpDrillParam ->dwPlane = dwPlane;
				lpDrillParam ->lDelay = lDelay;
				lpDrillParam ->lDepth = lDepth;
				lpDrillParam ->lFastVel = lFastVel;
				lpDrillParam ->lFirstIncrDepth = lFirstIncrDepth;
				lpDrillParam ->lIncrDepthDecr = lIncrDepthDecr;
				lpDrillParam ->lIncrRetreat = lIncrRetreat;
				lpDrillParam ->lNormVel = lNormVel;
				lpDrillParam ->lOtherIncrDepth = lOtherIncrDepth;
				lpDrillParam ->lRefHeight = lRefHeight;
				lpDrillParam ->lRetreat = lRetreat;
				lpDrillParam ->lSecurityHeight = lSecurityHeight;
				retval = _setDrillParam(lpDrillParam, sizeof(DRILLPARAM));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_GetDrillParam(LPDRILLPARAM lpDrillParam, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_GetDrillParam(LPDRILLPARAM lpDrillParam)
	{
		DWORD retval = -1;
		if (_getDrillParam)
		{
			retval = _getDrillParam(lpDrillParam, sizeof(DRILLPARAM));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_Drill(LPAXISPOS lpDrillPos, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_Drill(LPAXISPOS lpDrillPos)
	{
		DWORD retval = -1;
		if (_drill)
		{
			retval = _drill(lpDrillPos, sizeof(AXISPOS));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_Drill(long X, long Y, long Z, long A, long B, long C, long U, long V, long W, LPAXISPOS lpDrillPos)
	{
		DWORD retval = -1;
		if (_drill)
		{
			if (lpDrillPos)
			{
				lpDrillPos->A = A;
				lpDrillPos->B = B;
				lpDrillPos->C = C;
				lpDrillPos->U = U;
				lpDrillPos->V = V;
				lpDrillPos->W = W;
				lpDrillPos->X = X;
				lpDrillPos->Y = Y;
				lpDrillPos->Z = Z;
				retval = _drill(lpDrillPos, sizeof(AXISPOS));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_Operate(DWORD dwOperationCode, LPVOID lpParam);

	/*no information on how to handle this function
	TODO: figure out whast to do
	*/

	//  DWORD MCTL_DLLFUNC mctl_InputBit(DWORD dwPort, DWORD dwBit, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_InputBit(DWORD dwPort, DWORD dwBit, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_inputBit)
		{
			retval = _inputBit(dwPort, dwBit, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_InputByte(DWORD dwPort, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_InputByte(DWORD dwPort, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_inputByte)
		{
			retval = _inputByte(dwPort, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_InputWord(DWORD dwPort, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_InputWord(DWORD dwPort, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_inputWord)
		{
			retval = _inputWord(dwPort, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_InputDWord(DWORD dwPort, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_InputDWord(DWORD dwPort, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_inputDWord)
		{
			retval = _inputDWord(dwPort, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_OutputBit(DWORD dwPort, DWORD dwBit, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_OutputBit(DWORD dwPort, DWORD dwBit, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_outputBit)
		{
			retval = _outputBit(dwPort, dwBit, dwValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_OutputByte(DWORD dwPort, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_OutputByte(DWORD dwPort, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_outputByte)
		{
			retval = _outputByte(dwPort, dwValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_OutputWord(DWORD dwPort, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_OutputWord(DWORD dwPort, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_outputWord)
		{
			retval = _outputWord(dwPort, dwValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_OutputDWord(DWORD dwPort, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_OutputDWord(DWORD dwPort, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_outputDWord)
		{
			retval = _outputDWord(dwPort, dwValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_ReadOutputBit(DWORD dwPort, DWORD dwBit, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_ReadOutputBit(DWORD dwPort, DWORD dwBit, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_readOutputBit)
		{
			retval = _readOutputBit(dwPort, dwBit, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_ReadOutputByte(DWORD dwPort, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_ReadOutputByte(DWORD dwPort, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_readOutputByte)
		{
			retval = _readOutputByte(dwPort, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_ReadOutputWord(DWORD dwPort, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_ReadOutputWord(DWORD dwPort, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_readOutputWord)
		{
			retval = _readOutputWord(dwPort, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_ReadOutputDWord(DWORD dwPort, LPDWORD lpValue);
	DWORD MCTLWRAPPER_API mctlw_ReadOutputDWord(DWORD dwPort, LPDWORD lpValue)
	{
		DWORD retval = -1;
		if (_readOutputDWord)
		{
			retval = _readOutputDWord(dwPort, lpValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_SetBufferSize(DWORD dwBufferSize);
	DWORD MCTLWRAPPER_API mctlw_cp_SetBufferSize(DWORD dwBufferSize)
	{
		DWORD retval = -1;
		if (_cp_setBufferSize)
		{
			retval = _cp_setBufferSize(dwBufferSize);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_EnablePath(DWORD dwFlags);
	DWORD MCTLWRAPPER_API mctlw_cp_EnablePath(DWORD dwFlags)
	{
		DWORD retval = -1;
		if (_cp_enablePath)
		{
			retval = _cp_enablePath(dwFlags);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_DisablePath(DWORD dwFlags);
	DWORD MCTLWRAPPER_API mctlw_cp_DisablePath(DWORD dwFlags)
	{
		DWORD retval = -1;
		if (_cp_disablePath)
		{
			retval = _cp_disablePath(dwFlags);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_StartPath(DWORD dwFlags);
	DWORD MCTLWRAPPER_API mctlw_cp_StartPath(DWORD dwFlags)
	{
		DWORD retval = -1;
		if (_cp_startPath)
		{
			retval = _cp_startPath(dwFlags);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_EndPath(DWORD dwFlags);
	DWORD MCTLWRAPPER_API mctlw_cp_EndPath(DWORD dwFlags)
	{
		DWORD retval = -1;
		if (_cp_endPath)
		{
			retval = _cp_endPath(dwFlags);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_GetBufferStatus(LPCPBSTATUS lpContPathBufferStatus, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_cp_GetBufferStatus(LPCPBSTATUS lpContPathBufferStatus)
	{
		DWORD retval = -1;
		if (_cp_getBufferStatus)
		{
			retval = _cp_getBufferStatus(lpContPathBufferStatus, sizeof(CPBSTATUS));
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_SetVelocity(LPMCTLVELOCITY lpMctlVel, DWORD dwSize);
	DWORD MCTLWRAPPER_API mctlw_cp_SetVelocity(LPMCTLVELOCITY lpMctlVel)
	{
		DWORD retval = -1;
		if (_cp_setVelocity)
		{
			retval = _cp_setVelocity(lpMctlVel, sizeof(MCTLVELOCITY));
		}
		return retval;
	}

	DWORD MCTLWRAPPER_API mctlws_cp_SetVelocity(long normRel, long normRot, long fastRel, long fastRot, long teachRel, long techRot, long actualRel, long actualRot, LPMCTLVELOCITY lpMctlVel)
	{
		DWORD retval = -1;
		if (_cp_setVelocity)
		{
			if (lpMctlVel)
			{
				lpMctlVel->lNormVel[0] = normRel;
				lpMctlVel->lNormVel[1] = normRot;
				lpMctlVel->lFastVel[0] = fastRel;
				lpMctlVel->lFastVel[1] = fastRot;
				lpMctlVel->lTeachVel[0] = teachRel;
				lpMctlVel->lTeachVel[1] = techRot;
				lpMctlVel->lActVel[0] = actualRel;
				lpMctlVel->lActVel[1] = actualRot;
				retval = _cp_setVelocity(lpMctlVel, sizeof(MCTLVELOCITY));
			}
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_OutputBit(DWORD dwPort, DWORD dwBit, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_cp_OutputBit(DWORD dwPort, DWORD dwBit, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_cp_outputBit)
		{
			retval = _cp_outputBit(dwPort, dwBit, dwValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_OutputByte(DWORD dwPort, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_cp_OutputByte(DWORD dwPort, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_cp_outputByte)
		{
			retval = _cp_outputByte(dwPort, dwValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_OutputWord(DWORD dwPort, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_cp_OutputWord(DWORD dwPort, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_cp_outputWord)
		{
			retval = _cp_outputWord(dwPort, dwValue);
		}
		return retval;
	}

	//  DWORD MCTL_DLLFUNC mctl_cp_OutputDWord(DWORD dwPort, DWORD dwValue);
	DWORD MCTLWRAPPER_API mctlw_cp_OutputDWord(DWORD dwPort, DWORD dwValue)
	{
		DWORD retval = -1;
		if (_cp_outputDWord)
		{
			retval = _cp_outputDWord(dwPort, dwValue);
		}
		return retval;
	}

}

