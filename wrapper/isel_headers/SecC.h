/***************************************************************************

	 File:	SecC.H  

  Purpose:	Include file for the use of the Security Circuit Interface DLL
			SecC.DLL
			For access to the Security Circuit functions include this file
			into your source file and add SecC.LIB to your project.


  created:	26.07.2000 KP, isel Automation
  Version:	1.00

   modif.:	
			05.02.2001 KP
			Umstellung der Linker Direktiven auf geaenderte Aufrufkonvention
			__declspec(dllexport/dllimport) _stdcall wegen Inkompatibilitaet
			mit Visual Basic/Delphi, die anscheinend nur StdCall unterstuetzen.

			11.07.2001 KP	
			Added function prototypes for dynamic loaded DLL's

			23.11.2005 
			Flags SEC_TYPE_SKME, SEC_TYPE_SKMB, SEC_TYPE_PNOZ_MULTI
			Flag SEC_STAT_COMMUNICATION_FAIL



***************************************************************************/


#ifndef _ISELAUTOMATION_SEC_H_11072001_INCLUDED_
#define _ISELAUTOMATION_SEC_H_11072001_INCLUDED_



//////////////////////////////////////////////////////////////////////
// Flags and constants


#define SEC_TYPE_GENERIC				0x00000000
#define SEC_TYPE_SVM1					0x00000001		// Security module SVM-1 (used with UPMV4 controls)
#define SEC_TYPE_IMS6					0x00000002		// Security status interface IMS6
#define SEC_TYPE_IMC4					0x00000003		// Security status interface IMC4
#define SEC_TYPE_IML4					0x00000004		// Security status interface IMC4
#define SEC_TYPE_SKME					0x00000005		// Sicherheitskreismodul SKM-S1.xE (erweitert mit RS232-Anschluss)
#define SEC_TYPE_SKMB					0x00000006		// Sicherheitskreismodul SKM-S1.xB (Basis ohne RS232-Anschluss)
#define SEC_TYPE_PNOZ_MULTI				0x00000007		// PILZ Sicherheitsrelais PNOZ-Multi

#define SEC_RESERVED					0x10000000		
#define SEC_TYPE_ADMINISTRATOR			0x10000000		// Administrator for security circuit DLL management
#define SEC_TYPE_OTHER					0x80000000		// Other security circuit type (not listed)
#define SEC_TYPE_OEM					0x80000001		// OEM Security circuit


#define SEC_CFG_CONTROLLER				0x00000001		// A microcontroller is present
#define SEC_CFG_CONSOLE					0x00000002		// A console (for user input) is available
#define SEC_CFG_DISPLAY					0x00000004		// A display (for message output) is available


														// Common status
#define SEC_STAT_EMERGENCYSWITCH		0x00000001		// Emergency switch activated
#define SEC_STAT_SETUPMODE				0x00000002		// Setup mode is activated
#define SEC_STAT_ATHOMEPOS				0x00000004		// All axes are at home pos
#define SEC_STAT_SPINDLETURNS			0x00000008		// Spindle is still turning, not halted
#define SEC_STAT_COVEROPEN				0x00000010		// At least 1 cover is opened
#define SEC_STAT_LIMITSWITCH			0x00000020		// At least 1 limit switch is activated
#define SEC_STAT_OEM_1					0x00000100		// A user control input (#1) is active
#define SEC_STAT_OEM_2					0x00000200		// A user control input (#2) is active
#define SEC_STAT_POWER_FAIL				0x00010000		// Security module power fail
#define SEC_STAT_COMMUNICATION_FAIL		0x00020000		// Security module communication fail
#define SEC_STAT_HARDWARE_FAIL			0x00040000		// Hardware check failed
#define SEC_STAT_CONTROL_FAIL			0x00080000		// Control self test failed
#define SEC_STAT_LOCKED					0x00100000		// Module status is "locked"
#define SEC_STAT_COVERLOCKED			0x00200000		// Cover status is "locked"
#define SEC_STAT_FLASH					0x01000000		// Flashlight is on

														// Cover status
#define SEC_STAT_COVER1					0x00000001		// Cover 1 is opened
#define SEC_STAT_COVER2					0x00000002		// Cover 2 is opened
#define SEC_STAT_COVER3					0x00000004		// Cover 3 is opened
#define SEC_STAT_COVER4					0x00000008		// Cover 4 is opened


														// Disable and lock status
#define SEC_STAT_LOCK_AXES				0x00000001		// Axes are disabled
#define SEC_STAT_LOCK_SPINDLE			0x00000002		// Spindle drives are disabled
#define SEC_STAT_LOCK_TOOLCHANGE		0x00000004		// Toolchange system is disabled
#define SEC_STAT_LOCK_IO				0x00000008		// IO system is disabled
#define SEC_STAT_LOCK_COVER				0x00000010		// Cover lock is activated
#define SEC_STAT_LOCK_OEM_1				0x00001000		// Additional HW provided by user is disabled
#define SEC_STAT_LOCK_OEM_2				0x00002000		// Additional HW provided by user is disabled

														// Extended status flags
#define SEC_STAT_ISBUSY					0x00000001		// Module is busy with an operation
#define SEC_STAT_DISABLED				0x00000002		// Security module is disabled
#define SEC_STAT_ISINITIALIZED			0x00000004		// Security module is initialized




//////////////////////////////////////////////////////////////////////
// Data types

#ifndef _SECVERSION_DEFINED_
#define _SECVERSION_DEFINED_
typedef struct tagSECVERSION			// Version information
{														
DWORD	dwType;							// Type of Security circuit hardware
int	 	iVerMajor;						// Version number major
int	 	iVerMinor;						// Version number minor
int		iVerRelease;					// Release number
int		iVerBuilt;						// Built number
char    szDescription[255];				// Description of the module
char    szComment[255];					// Comment concerning purpose, functions etc.
char	szCompanyName[255];				// Name of the module supplier
}
SECVERSION, *LPSECVERSION;
#endif


#ifndef _SECCONFIG_DEFINED_
#define _SECCONFIG_DEFINED_
typedef struct tagSECCONFIG				// Security module configuration 
{
DWORD	dwAbility;						// Abilities of the security circuit
}
SECCONFIG, *LPSECCONFIG;
#endif


#ifndef _SECSTATUS_DEFINED_
#define _SECSTATUS_DEFINED_
typedef struct tagSECSTATUS				// Status informations
{
DWORD	dwCommon;						// Common status flags
DWORD	dwCover;						// Cover status
DWORD	dwHardwareLock;					// Disable status of supervised hardware
DWORD	dwExtended;						// Extended status flags

BOOL	fEmergencySwitch;				// Emergency switch is activated
BOOL	fSetupMode;						// Setup mode is activated
BOOL	fAtHomePos;						// Home pos Switch is activated
BOOL	fSpindleTurns;					// Spindle is turning
BOOL	fCoverOpen;						// At least one cover is still open
BOOL	fLimitSwitch;					// Limit switch is activated
BOOL	fOEM1;							// OEM input 1 is active
BOOL	fOEM2;							// OEM input 2 is active
BOOL	fPowerFail;						// Security module Power Fail 
BOOL	fHardwareFail;					// SecModule hardware check failed
BOOL	fControlFail;					// SecModule Control self test failed
BOOL	fLocked;						// SecModule status is "locked"
BOOL	fCoverLocked;					// Cover status is "locked"
BOOL	fFlashing;						// Alert Flashlight is on

BOOL	fIsBusy;						// Flag SecModule is busy
BOOL	fDisabled;						// Flag SecModule is disabled
BOOL	fIsInitialized;					// Flag SecModule is initialized
}
SECSTATUS, *LPSECSTATUS;
#endif




//////////////////////////////////////////////////////////////////////
// Function prototypes


#if defined(_SEC_DLL_INTERNAL_)
  #define SEC_DLLFUNC		__declspec(dllexport) _stdcall
#else
  #define SEC_DLLFUNC		__declspec(dllimport) _stdcall
#endif


#if defined(__BORLANDC__)
extern "C"
{
#endif


// Only for internal use
DWORD SEC_DLLFUNC sec_SetNCCtrl(LPVOID pNCCtrl);
DWORD SEC_DLLFUNC sec_SetMctlAdm(LPVOID pMctlAdm);
DWORD SEC_DLLFUNC sec_SetIoAdm(LPVOID pIoAdm);
DWORD SEC_DLLFUNC sec_SetSpnAdm(LPVOID pSpnAdm);
DWORD SEC_DLLFUNC sec_SetTchAdm(LPVOID pTchAdm);
// End internal use

DWORD SEC_DLLFUNC sec_Initialize(char *);
DWORD SEC_DLLFUNC sec_Exit(void);
DWORD SEC_DLLFUNC sec_Setup(void);
DWORD SEC_DLLFUNC sec_Diagnosis(void);
DWORD SEC_DLLFUNC sec_GetVersion(LPSECVERSION, DWORD);
DWORD SEC_DLLFUNC sec_GetConfiguration(LPSECCONFIG, DWORD);
DWORD SEC_DLLFUNC sec_Reset(void);
DWORD SEC_DLLFUNC sec_GetStatus(LPSECSTATUS, DWORD);
DWORD SEC_DLLFUNC sec_Operate(DWORD dwOperationCode, LPVOID lpParam);

#if defined(__BORLANDC__)
}
#endif

										// Explicit binding:
										// Declaration of function prototypes
										// to access the spindle DLL functions

// Only for internal use
										// KP 30.11.2006 Erweiterung der Standardfunktionen um Setzen der Verwalter in den Modulen
typedef DWORD (_stdcall * SEC_SETNCCTRL)(LPVOID);
typedef DWORD (_stdcall * SEC_SETMCTLADM)(LPVOID);
typedef DWORD (_stdcall * SEC_SETIOADM)(LPVOID);
typedef DWORD (_stdcall * SEC_SETSPNADM)(LPVOID);
typedef DWORD (_stdcall * SEC_SETTCHADM)(LPVOID);
// End internal use

typedef DWORD (_stdcall * SEC_SETUNITS)(LPVOID, DWORD);
typedef DWORD (_stdcall * SEC_INITIALIZE)(char *);
typedef DWORD (_stdcall * SEC_EXIT)(void);
typedef DWORD (_stdcall * SEC_SETUP)(void);
typedef DWORD (_stdcall * SEC_DIAGNOSIS)(void);
typedef DWORD (_stdcall * SEC_RESET)(void);
typedef DWORD (_stdcall * SEC_GETVERSION)(LPVOID, DWORD);
typedef DWORD (_stdcall * SEC_GETCONFIGURATION)(LPVOID, DWORD);
typedef DWORD (_stdcall * SEC_GETSTATUS)(LPVOID, DWORD);
typedef DWORD (_stdcall * SEC_OPERATE)(DWORD, LPVOID);


#endif  // #ifndef _ISELAUTOMATION_SEC_H_11072001_INCLUDED_


