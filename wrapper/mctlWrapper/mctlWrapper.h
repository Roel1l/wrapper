// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MCTLWRAPPER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MCTLWRAPPER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MCTLWRAPPER_EXPORTS
#define MCTLWRAPPER_API __declspec(dllexport)
#else
#define MCTLWRAPPER_API __declspec(dllimport)
#endif

extern "C"
{
	extern MCTL_SETUNITS _setUnits;
	extern MCTL_INITIALIZE _initialize;
	extern MCTL_EXIT _xit;
	extern MCTL_SETUP _setup;
	extern MCTL_DIAGNOSIS _diagnosis;
	extern MCTL_GETVERSION _getVersion;
	extern MCTL_GETCONFIGURATION _getConfiguration;
	extern MCTL_GETAXISCONFIGURATION _getAxisConfiguration;
	extern MCTL_GETSTATUS _getStatus;
	extern MCTL_GETSTATUSONEVENT _getStatusOnEvent;
	extern MCTL_GETAXISSTATUS _getAxisStatus;
	extern MCTL_RESET _reset;
	extern MCTL_REFERENCE _reference;
	extern MCTL_REFERENCEBREAK _referenceBreak;
	extern MCTL_SETTESTMODE _setTestMode;
	extern MCTL_SETTEACHMODE _setTeachMode;
	extern MCTL_SETPOWERSTATE _setPowerState;
	extern MCTL_SETVELOCITY _setVelocity;
	extern MCTL_GETVELOCITY _getVelocity;
	extern MCTL_SETOVERRIDE _setOverride;
	extern MCTL_GETOVERRIDE _getOverride;
	extern MCTL_SETACTPOSWNP _setActPosWnp;
	extern MCTL_SETWNPABS _setWnpAbs;
	extern MCTL_SETWNPREL _setWnpRel;
	extern MCTL_GETWNP _getWnp;
	extern MCTL_GETWNPSTATUS _getWnpStatus;
	extern MCTL_CLEARWNP _clearWnp;
	extern MCTL_SETSWLS _setSwls;
	extern MCTL_GETSWLSSTATUS _getSwlsStatus;
	extern MCTL_ENABLESWLS _enableSwls;
	extern MCTL_CLEARSWLS _clearSwls;
	extern MCTL_MOVEABS _moveAbs;
	extern MCTL_MOVEREL _moveRel;
	extern MCTL_MOVERELUNTILPORTEVENT _moveRelUntilPortEvent;
	extern MCTL_FASTABS _fastAbs;
	extern MCTL_FASTREL _fastRel;
	extern MCTL_CIRCLEABS _circleAbs;
	extern MCTL_CIRCLEREL _circleRel;
	extern MCTL_HELIXABS _helixAbs;
	extern MCTL_HELIXREL _helixRel;
	extern MCTL_SPLINEABS _splineAbs;
	extern MCTL_SPLINEREL _splineRel;
	extern MCTL_BEZIERABS _bezierAbs;
	extern MCTL_BEZIERREL _bezierRel;
	extern MCTL_GETPOSITION _getPosition;
	extern MCTL_GETDESTINATIONPOS _getDestinationPos;
	extern MCTL_SETMOTIONSTATE _setMotionState;
	extern MCTL_LEAVEHWLS _leaveHwls;
	extern MCTL_HWLSBRIDGE _hwlsBridge;
	extern MCTL_SETDRILLPARAM _setDrillParam;
	extern MCTL_GETDRILLPARAM _getDrillParam;
	extern MCTL_DRILL _drill;
	extern MCTL_OPERATE _operate;
	extern MCTL_INPUTBIT _inputBit;
	extern MCTL_INPUTBYTE _inputByte;
	extern MCTL_INPUTWORD _inputWord;
	extern MCTL_INPUTDWORD _inputDWord;
	extern MCTL_OUTPUTBIT _outputBit;
	extern MCTL_OUTPUTBYTE _outputByte;
	extern MCTL_OUTPUTWORD _outputWord;
	extern MCTL_OUTPUTDWORD _outputDWord;
	extern MCTL_READOUTPUTBIT _readOutputBit;
	extern MCTL_READOUTPUTBYTE _readOutputByte;
	extern MCTL_READOUTPUTWORD _readOutputWord;
	extern MCTL_READOUTPUTDWORD _readOutputDWord;
	extern MCTL_CP_SETBUFFERSIZE _cp_setBufferSize;
	extern MCTL_CP_ENABLEPATH _cp_enablePath;
	extern MCTL_CP_DISABLEPATH _cp_disablePath;
	extern MCTL_CP_STARTPATH _cp_startPath;
	extern MCTL_CP_ENDPATH _cp_endPath;
	extern MCTL_CP_GETBUFFERSTATUS _cp_getBufferStatus;
	extern MCTL_CP_SETVELOCITY _cp_setVelocity;
	extern MCTL_CP_OUTPUTBIT _cp_outputBit;
	extern MCTL_CP_OUTPUTBYTE _cp_outputByte;
	extern MCTL_CP_OUTPUTWORD _cp_outputWord;
	extern MCTL_CP_OUTPUTDWORD _cp_outputDWord;

}
