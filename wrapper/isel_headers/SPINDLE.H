//*****************************************************************
//
// File:	SPINDLE.H  
//
// Purpose:	Definitionen der Funktionen aus der DLL fuer die 
//          Spindelsteuerung SPINDLE.DLL
//			Fuer den Zugriff auf die Funktionen ist diese
//			Include-Datei einzubinden und das LIB-File SPINDLE.LIB
//			in das Projekt aufzunehmen.
//
//
// created:	23.12.98 KP, isel Automation
// Version: 1.00
//
//			23.12.1998
//			geaendert wegen Vereinheitlichung von Softwarestrukturen
//			in unterschiedlichen Modulen
//			Vereinheitlichung von Namensstrukturen
//
//			17.04.99
//			Bei der Uebergabe selbstdefinierter Structs sollte immer
//			ein DWORD_Parameter mit dem Wert sizeof(Struct) uebergeben
//			werden. Auf diese Weise können in der Zukunft Zugriffe
//			ueber die Grenzen des Structs hinaus vermieden werden (falls
//			der Struct mit der Version der DLL wachsen sollte und eine
//			alte DLL mit einem Client_Programm mit Deklarationen der neuen 
//			Structgroesse benutzt wird).
//			
//			09.06.99 
//			Bemerkung:
//			Bei der Uebergabe selbstdefinierter Structs muss immer
//			ein DWORD_Parameter mit dem Wert sizeof(Struct) uebergeben
//			werden. Auf diese Weise können in der Zukunft Zugriffe
//			ueber die Grenzen des Structs hinaus vermieden werden (falls
//			der Struct mit der Version der DLL wachsen sollte und eine
//			alte DLL mit einem Client_Programm mit Deklarationen der neuen 
//			Structgroesse benutzt wird).
//
//			06.07.2000
//			Umstellung der Linker Direktiven auf __declspec(dllexport/dllimport)
//
//			24.01.2001
//			Erweiterung um das Flag "Modul ist initialisiert"
//			
//			05.02.2001
//			Umstellung der Linker Direktiven auf geaenderte Aufrufkonvention
//			__declspec(dllexport/dllimport) _stdcall wegen Inkompatibilitaet
//			mit Visual Basic/Delphi, die anscheinend nur StdCall unterstuetzen.
//
//			01.03.2001
//			Erweiterung um Flag "Solldrehzahl erreicht"
//
//
//
//
//
//*****************************************************************


#ifndef SPINDLE_H_INCLUDED
#define SPINDLE_H_INCLUDED



//////////////////////////////////////////////////////////////////////
// Flags and constants


#define SPN_TYPE_MULTIIO_PWM				0		
#define SPN_TYPE_C142_7BIT_DIR				1
#define SPN_TYPE_MULTIIO_ANALOG_LFRI		2
#define SPN_TYPE_MULTIIO_ANALOG				3
#define SPN_TYPE_SET1BIT					4
#define SPN_TYPE_SET1BIT_SC					5
#define SPN_TYPE_MANUAL						6
#define SPN_TYPE_C142_ANALOGADAPT			7
#define SPN_TYPE_C142_ISA300				8
#define SPN_TYPE_FC12_6BITSD				9
#define SPN_TYPE_8BIT						10
#define SPN_TYPE_7BIT_START					11
#define SPN_TYPE_7BIT_DIR					12
#define SPN_TYPE_6BIT_START_DIR				13
#define SPN_TYPE_ANALOGADAPTER				14
#define SPN_TYPE_ISA300						15
#define SPN_TYPE_1BIT_READABLE				16
#define SPN_TYPE_IMC4_SPINDLEPORT			17
#define SPN_TYPE_IMS6_SPINDLE				18
#define SPN_TYPE_ADMINISTRATOR				0x10000000		// Administrator for multiple spindle control
#define SPN_TYPE_OTHER						0x80000000		// Other spindle type (not listed)
#define SPN_TYPE_OEM						0x80000001		// OEM Spindle Control


#define SPN_CFG_DIR_LEFT					0x00000001
#define SPN_CFG_DIR_RIGHT					0x00000002
#define SPN_CFG_VARIABLESPEED				0x00000010
#define SPN_CFG_OVERRIDE					0x00000020
#define SPN_CFG_MULTIPLE_MODULE_ACCESS		0x10000000


#define SPN_STAT_STANDSTILL					0x00000001
#define SPN_STAT_TEMPERATURE				0x00000002
#define SPN_STAT_OVERLOAD					0x00000004
#define SPN_STAT_POWER_FAIL					0x00010000
#define SPN_STAT_SC_FAIL					0x00020000
#define SPN_STAT_HARDWARE_FAIL				0x00040000
#define SPN_STAT_CONTROL_FAIL				0x00080000
#define SPN_STAT_SETSPEEDREACHED			0x00100000		// KP 02.02.01 Set Speed value is reached
#define SPN_STAT_COMMUNICATION_FAIL			0x10000000		// KP 24.01.01 Communication (e.g. via Bus, RS232,...) failed

#define SPN_STAT_ISBUSY						0x00000001
#define SPN_STAT_DISABLED					0x00000002
#define SPN_STAT_ISINITIALIZED				0x00000004		// KP 24.01.01 Spindle module is initialized



#define SPN_OFF								0x00
#define SPN_ON								0x01

#define SPN_DIR_LEFT						0x01
#define SPN_DIR_RIGHT						0x02

#define SPN_MIN_OVERRIDE					75
#define SPN_MAX_OVERRIDE					125




//////////////////////////////////////////////////////////////////////
// Data types


typedef struct tagSPNVERSION			// Version information
{														
DWORD	dwType;							// Spindeltyp
int	 	iVerMajor;						// Version number major
int	 	iVerMinor;						// version number minor
int		iVerRelease;					// release number
int		iVerBuilt;						// built number
char    szDescription[255];				// Description of the module
char    szComment[255];					// Comment concerning purpose, functions etc.
char	szCompanyName[255];				// Name of the module supplier
}
SPNVERSION, *LPSPNVERSION;


typedef struct tagSPNCONFIG				// The ability struct
{
DWORD	dwAbility;						// Abilities of the spindle control
LONG	lMinSpeed;						// Minimum speed
LONG	lMaxSpeed;						// Maximum speed
LONG    lMinOverride;					// Minimum value of the speed override
LONG	lMaxOverride;					// Maximum value of the speed override
}
SPNCONFIG, *LPSPNCONFIG;


typedef struct tagSPNSTATUS				// Status informations
{
DWORD	dwCommon;						// Common status flags
DWORD	dwExtended;						// Extended status flags
long	lSpeed;							// Currently set target speed
long	lActSpeed;						// Current physical speed
long	lOverride;						// Currently set override value
DWORD	dwDirection;					// Currently set target direction
DWORD	dwActDirection;					// Current physical turn direction
DWORD	dwOnOff;						// Switch status (ON or OFF)

BOOL	fStandStill;					// Flag spindle is not in motion
BOOL	fTemperature;					// Flag Temperature error
BOOL	fOverload;						// Flag Overload
BOOL	fPowerFail;						// Flag Power fail
BOOL	fSCFail;						// Flag Spindle blocked by security circuit
BOOL	fHardwareFail;					// Flag Hardware error
BOOL	fControlFail;					// Flag Hardware error in spindle controller
BOOL	fIsBusy;						// Flag Spindle control is busy at the moment
BOOL	fDisabled;						// Flag Spindle module is disabled

BOOL	fSetSpeedReached;				// KP 01.03.2001 Desired speed value is reached
BOOL	fCommunicationFail;				// KP 01.03.2001 A communication error occured
BOOL	fIsInitialized;					// KP 01.03.2001 Spindle module is initialized
}
SPNSTATUS, *LPSPNSTATUS;




//////////////////////////////////////////////////////////////////////
// Function prototypes


#if defined(_SPN_DLL_INTERNAL_)
  #define SPN_DLLFUNC		__declspec(dllexport) _stdcall
#else
  #define SPN_DLLFUNC		__declspec(dllimport) _stdcall
#endif


#if defined(__BORLANDC__)
extern "C"
{
#endif


DWORD SPN_DLLFUNC spn_SetUnits(LPVOID, DWORD);
DWORD SPN_DLLFUNC spn_Initialize(char *);
DWORD SPN_DLLFUNC spn_Exit(void);
DWORD SPN_DLLFUNC spn_Setup(void);
DWORD SPN_DLLFUNC spn_Diagnosis(void);
DWORD SPN_DLLFUNC spn_GetVersion(LPSPNVERSION, DWORD);
DWORD SPN_DLLFUNC spn_GetConfiguration(LPSPNCONFIG, DWORD);
DWORD SPN_DLLFUNC spn_GetStatus(LPSPNSTATUS, DWORD);
DWORD SPN_DLLFUNC spn_Reset(void);
DWORD SPN_DLLFUNC spn_Switch(DWORD);
DWORD SPN_DLLFUNC spn_SetSpeed(LONG);
DWORD SPN_DLLFUNC spn_GetSpeed(LPLONG);
DWORD SPN_DLLFUNC spn_GetActSpeed(LPLONG);
DWORD SPN_DLLFUNC spn_SetDirection(DWORD);
DWORD SPN_DLLFUNC spn_GetDirection(LPDWORD);
DWORD SPN_DLLFUNC spn_SetOverride(long);
DWORD SPN_DLLFUNC spn_GetOverride(LPLONG);

										// Buffered workmode
DWORD SPN_DLLFUNC spn_Switch_B(DWORD);
DWORD SPN_DLLFUNC spn_SetSpeed_B(LONG);
DWORD SPN_DLLFUNC spn_SetDirection_B(DWORD);
DWORD SPN_DLLFUNC spn_SetOverride_B(long);

#if defined(__BORLANDC__)
}
#endif


										// Explicit binding:
										// Declaration of function prototypes
										// to access the spindle DLL functions

typedef DWORD (_stdcall * SPN_SETUNITS)(LPVOID, DWORD);
typedef DWORD (_stdcall * SPN_INITIALIZE)(char *);
typedef DWORD (_stdcall * SPN_EXIT)(void);
typedef DWORD (_stdcall * SPN_SETUP)(void);
typedef DWORD (_stdcall * SPN_DIAGNOSIS)(void);
typedef DWORD (_stdcall * SPN_RESET)(void);
typedef DWORD (_stdcall * SPN_GETVERSION)(LPVOID, DWORD);
typedef DWORD (_stdcall * SPN_GETCONFIGURATION)(LPVOID, DWORD);
typedef DWORD (_stdcall * SPN_GETSTATUS)(LPVOID, DWORD);
typedef DWORD (_stdcall * SPN_SWITCH)(DWORD);
typedef DWORD (_stdcall * SPN_SETSPEED)(LONG);
typedef DWORD (_stdcall * SPN_GETSPEED)(LPLONG);
typedef DWORD (_stdcall * SPN_GETACTSPEED)(LPLONG);
typedef DWORD (_stdcall * SPN_SETDIRECTION)(DWORD);
typedef DWORD (_stdcall * SPN_GETDIRECTION)(LPDWORD);
typedef DWORD (_stdcall * SPN_SETOVERRIDE)(LONG);
typedef DWORD (_stdcall * SPN_GETOVERRIDE)(LPLONG);


#endif									// #ifndef SPINDLE_H_INCLUDED


