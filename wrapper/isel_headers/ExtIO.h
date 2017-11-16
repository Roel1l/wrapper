//*********************************************************************************
//
// File:	ExtIO.H  
//
// Purpose:	Definitionen der Funktionen aus der DLL fuer den
//          allgemeinen Zugriff auf IO-Ports EXTIO.DLL
//			Fuer den Zugriff auf die Funktionen ist diese
//			Include-Datei einzubinden und das LIB-File EXTIO.LIB
//			in das Projekt aufzunehmen.
//
//
// created:	14.04.99 KP, isel Automation
// Version: 1.00
//
//			09.06.99 
//			Bemerkung:
//			Bei der Uebergabe selbstdefinierter Structs sollte immer
//			ein DWORD_Parameter mit dem Wert sizeof(Struct) uebergeben
//			werden. Auf diese Weise können in der Zukunft Zugriffe
//			ueber die Grenzen des Structs hinaus vermieden werden (falls
//			der Struct mit der Version der DLL wachsen sollte und eine
//			alte DLL mit einem Client_Programm mit Deklarationen der neuen 
//			Structgroesse benutzt wird).
//
//			06.07.2000
//			Umstellung der Linker Direktiven auf _declspec(dllexport/dllimport)
//
//			06.09.2000
//			Erweiterung um die Funktion io_InitOutput(), initialisieren
//			eines oder aller Ausgabeports mit den Defaultwerten
//			
//			24.01.2001
//			Flags fuer erweiterte Funktionalitaeten hinzugefuegt
//			
//			05.02.2001
//			Umstellung der Linker Direktiven auf geaenderte Aufrufkonvention
//			__declspec(dllexport/dllimport) _stdcall wegen Inkompatibilitaet
//			mit Visual Basic/Delphi, die anscheinend nur StdCall unterstuetzen.
//
//			13.07.2001
//			Flags fuer erweiterte Funktionalitaeten hinzugefuegt
//			
//		
//		
//
//*********************************************************************************


#ifndef _ISELAUTOMATION_EXTIO_H_INCLUDED
#define _ISELAUTOMATION_EXTIO_H_INCLUDED



//////////////////////////////////////////////////////////////////////
// Flags, constants

											// IO Type specification

#define IO_TYPE_PCCARD						0x00000001		
#define IO_TYPE_PCCARD_VXD					0x00000002
#define IO_TYPE_CAN							0x00000003
#define IO_TYPE_IMC4CTRL					0x00000004
#define IO_TYPE_IMS6CTRL					0x00000005
#define IO_TYPE_ADMINISTRATOR				0x10000000
#define IO_TYPE_OTHER						0x80000000
#define IO_TYPE_OEM							0x80000001		// OEM Io Module


											// Ability flags of the IO module

#define IO_CFG_ABLE_TO_READOUTPUT			0x00000001
#define IO_CFG_REALTIME_ACCESS				0x00000002
#define IO_CFG_ABLE_TO_HANDLE_WORD			0x00000004		// KP 13.07.2001 Later on: Word operations
#define IO_CFG_ABLE_TO_HANDLE_DOUBLEWORD	0x00000008		// KP 13.07.2001 Later on: Double word operations
#define IO_CFG_MULTIPLE_MODULE_ACCESS		0x10000000


											// Common status flags

#define IO_STAT_COMM_FAIL					0x00000001
#define IO_STAT_POWER_FAIL					0x00010000
#define IO_STAT_SC_FAIL						0x00020000
#define IO_STAT_HARDWARE_FAIL				0x00040000
#define IO_STAT_CONTROL_FAIL				0x00080000
#define IO_STAT_COMMUNICATION_FAIL			0x10000000		// KP Neu 24.01.01


											// Extended status flags

#define	IO_STAT_ISBUSY						0x00000001
#define IO_STAT_DISABLED					0x00000002		// KP Neu 24.01.01
#define IO_STAT_ISINITIALIZED				0x00000004		// KP Neu 24.01.01


											
#define IO_LOW								0x00
#define IO_HIGH								0x01
#define IO_LO								IO_LOW
#define	IO_HI								IO_HIGH
#define IO_OFF								IO_LOW
#define IO_ON								IO_HIGH

#ifndef	LOW	
#define LOW									IO_LOW
#endif

#ifndef	HIGH	
#define HIGH								IO_HIGH
#endif

#ifndef	LO	
#define LO									IO_LOW
#endif

#ifndef	HI	
#define HI									IO_HIGH
#endif

#ifndef IO_INIT_ALL
#define IO_INIT_ALL							0x0FFFFFFF
#endif



//////////////////////////////////////////////////////////////////////
// Data types


typedef struct tagIOVERSION					// Version information
{
DWORD	dwType;								// Type of IO module
int	 	iVerMajor;							// Major version number 
int	 	iVerMinor;							// Minor version number 
int		iVerRelease;						// Release version number 
int		iVerBuilt;							// Built version number 
char    szDescription[255];					// Description of the module
char    szComment[255];						// Comment concerning purpose, functions etc.
char	szCompanyName[255];					// Name of the module supplier
}											
IOVERSION, *LPIOVERSION;						   


typedef struct tagIOCONFIG					// Configuration of the IO module
{
DWORD	dwAbility;							// Module abilities
DWORD	dwNumInput;							// Number of available user inputs
DWORD	dwNumOutput;						// Number of available user outputs
}
IOCONFIG, *LPIOCONFIG;


typedef struct tagIOSTATUS
{
DWORD	dwCommon;							// Common status flags
DWORD	dwExtended;							// Extended status informations
BOOL	fCommFail;							// Communication error
BOOL	fPowerFail;							// Power Fail, missing supply voltage
BOOL	fSCFail;							// IO module locked by security circuit
BOOL	fHardwareFail;						// Hardware error
BOOL	fControlFail;						// Controller error
BOOL	fIsBusy;							// IO module is busy at the moment
BOOL	fDisabled;							// KP 13.07.2001 IO module is disabled
BOOL	fIsInitialized;						// KP 01.03.2001 IO module is initialized
BOOL	fCommunicationFail;					// KP 01.03.2001 Communication error (Bus-IO)
}
IOSTATUS, *LPIOSTATUS;




//////////////////////////////////////////////////////////////////////
// Function prototypes

#if defined(_IO_DLL_INTERNAL_)
  #define IO_DLLFUNC	__declspec(dllexport) _stdcall
#else
  #define IO_DLLFUNC	__declspec(dllimport) _stdcall
#endif


#if defined(__BORLANDC__)
extern "C"
{
#endif

DWORD IO_DLLFUNC io_SetUnits(LPVOID, DWORD);
DWORD IO_DLLFUNC io_Initialize(char *);
DWORD IO_DLLFUNC io_Exit(void);
DWORD IO_DLLFUNC io_Setup(void);
DWORD IO_DLLFUNC io_Diagnosis(void);
DWORD IO_DLLFUNC io_GetVersion(LPIOVERSION, DWORD);
DWORD IO_DLLFUNC io_GetConfiguration(LPIOCONFIG, DWORD);
DWORD IO_DLLFUNC io_GetStatus(LPIOSTATUS, DWORD);
DWORD IO_DLLFUNC io_Reset(void);
DWORD IO_DLLFUNC io_InitOutput(DWORD);
DWORD IO_DLLFUNC io_InputBit(DWORD, DWORD, LPDWORD);
DWORD IO_DLLFUNC io_InputByte(DWORD, LPDWORD);
DWORD IO_DLLFUNC io_InputWord(DWORD, LPDWORD);
DWORD IO_DLLFUNC io_InputDWord(DWORD, LPDWORD);
DWORD IO_DLLFUNC io_OutputBit(DWORD, DWORD, DWORD);
DWORD IO_DLLFUNC io_OutputByte(DWORD, DWORD);
DWORD IO_DLLFUNC io_OutputWord(DWORD, DWORD);
DWORD IO_DLLFUNC io_OutputDWord(DWORD, DWORD);
DWORD IO_DLLFUNC io_ReadOutputBit(DWORD, DWORD, LPDWORD);
DWORD IO_DLLFUNC io_ReadOutputByte(DWORD, LPDWORD);
DWORD IO_DLLFUNC io_ReadOutputWord(DWORD, LPDWORD);
DWORD IO_DLLFUNC io_ReadOutputDWord(DWORD, LPDWORD);

#if defined(__BORLANDC__)
}
#endif


										// Explicit binding:
										// Declaration of function prototypes
										// for accessing the IO DLL functions

typedef DWORD (_stdcall * IO_SETUNITS)(LPVOID, DWORD);
typedef DWORD (_stdcall * IO_INITIALIZE)(char *);
typedef DWORD (_stdcall * IO_EXIT)(void);
typedef DWORD (_stdcall * IO_SETUP)(void);
typedef DWORD (_stdcall * IO_DIAGNOSIS)(void);
typedef DWORD (_stdcall * IO_GETVERSION)(LPVOID, DWORD);
typedef DWORD (_stdcall * IO_GETCONFIGURATION)(LPVOID, DWORD);
typedef DWORD (_stdcall * IO_GETSTATUS)(LPVOID, DWORD);
typedef DWORD (_stdcall * IO_RESET)(void);
typedef DWORD (_stdcall * IO_INITOUTPUT)(DWORD);
typedef DWORD (_stdcall * IO_INPUTBIT)(DWORD, DWORD, LPDWORD);
typedef DWORD (_stdcall * IO_INPUTBYTE)(DWORD, LPDWORD);
typedef DWORD (_stdcall * IO_INPUTWORD)(DWORD, LPDWORD);
typedef DWORD (_stdcall * IO_INPUTDWORD)(DWORD, LPDWORD);
typedef DWORD (_stdcall * IO_OUTPUTBIT)(DWORD, DWORD, DWORD);
typedef DWORD (_stdcall * IO_OUTPUTBYTE)(DWORD, DWORD);
typedef DWORD (_stdcall * IO_OUTPUTWORD)(DWORD, DWORD);
typedef DWORD (_stdcall * IO_OUTPUTDWORD)(DWORD, DWORD);
typedef DWORD (_stdcall * IO_READOUTPUTBIT)(DWORD, DWORD, LPDWORD);
typedef DWORD (_stdcall * IO_READOUTPUTBYTE)(DWORD, LPDWORD);
typedef DWORD (_stdcall * IO_READOUTPUTWORD)(DWORD, LPDWORD);
typedef DWORD (_stdcall * IO_READOUTPUTDWORD)(DWORD, LPDWORD);



#endif	// #ifndef _ISELAUTOMATION_EXTIO_H_INCLUDED


