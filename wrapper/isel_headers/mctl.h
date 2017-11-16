//****************************************************************************
//
//    File:	MCTL.H  
//
// Purpose:	Declaration of functions which are located inside a Motion
//			Control DLL (Dynamic Link Library for control of machine movements) 
//			To use the functions include this file into your source code
//			and add the resp. LIB file to your project.
//
//			Available LIBs:
//
//			- mctlimc4.lib
//			- mctl_upmv4.lib
//			- mctl_ims6.lib
//
//
// created:	22.06.98 KP, isel Automation
//
// Version: 1.00
//
//			23.11.1998
//			geaendert wegen Vereinheitlichung vonn Softwarestrukturen 
//			in  unterschiedlichen Modulen
//			Vereinheitlichung von Namensstrukturen
//
//			17.01.1999
//			Weitere Anpassungen in Detailbereichen
//			insb. Verwaltung der INI-Datei, 
//			Funktionalitaeten der DLL
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
//			20.07.2000
//			Funktionen mctl_SetTestMode() und mctl_SetPowerState() implementiert
//			Neu: Struct MCTLVELOCITY, Funktionen mctl_SetVelocity(), mctl_GetVelocity()
//			generell sollte der Zugriff auf die Geschwindigkeiten nur ueber
//			die Velocity-Funktionen passieren (wg. allgemein ueblicher Benennung
//			von Bewegungsgeschwindigkeiten mit "Velocity", von Drehzahlen dagegen
//			mit "Speed")
//
//			05.02.2001
//			Umstellung der Linker Direktiven auf geaenderte Aufrufkonvention
//			__declspec(dllexport/dllimport) _stdcall wegen Inkompatibilitaet
//			mit Visual Basic/Delphi, die anscheinend nur StdCall unterstuetzen.
//
//			06.02.2001 KP
//			Erweiterung der Achsenstruktur
//			Aufnahme verschiedener anderer Definitionen und Deklarationen
//
//			21.02.2001 KP
//			Aufnahme der Deklaration fuer die nicht einheitlich nutzbaren
//			Funktionen fuer Lesen, Setzen und Zuruecklesen von Ports innerhalb 
//			einer Motion Control-Umgebung.
//
//			28.05.2001 KP
//			Erweiterung um achsspezifische Funktionen mctl_GetAxisConfig(),
//			MCTL_GetAxisStatus(), sowie deren Datenstructs.
//			Weitere Funktionen fuer Buffered Workmode und Online_Path_Calculation
//			sowie die benoetigten Datenstrukturen.
//
//			27.06.2001 KP
//			Helix interpolation commands, structure for helix parameters
//
//			28.06.2001 KP
//			Declaration of CIRCLEPARAM instead of CIRCLEPOS, makes it similar
//			to declaration of HELIXPARAM
//
//			16.07.2001 KP
//			Definitions and function prototypes for drill cycles
//
//			26/27.07.2001 KP
//			Changed to simplified version without separate buffered 
//			movement functions.
//
//			31.10.2001 KP
//			Added mctl_MoveRelUntilPort() as a public function for common use
//			This function is not available in each Motion Control DLL!
//
//			16.11.2001 KP
//			Drill extension modified: DRILLPARAM contains the additional 
//			parameters dwPlane and dwDirection
//			
//			22.01.2002 KP
//			Software limit switch functions
//			Workpiece zero point: GetWNPStatus 
//			
//			30.01.2002 KP
//			Added Spline and Bezier movement function prototypes
//			
//			11.03.2004 KP
//			Erweiterung der Datenstrukturen auf 9 Achsen
//			
//			10.08.2004
//			Additional definitions	Logosol
//			
//
//****************************************************************************



#ifndef MCTL_H_INCLUDED
#define MCTL_H_INCLUDED


//---Common definitions------------------------------------------------------

#ifndef PI
 #define PI		3.1415926535898
#endif



//---Flags-------------------------------------------------------------------

														// Type of motion control
#define MCTL_TYPE_DCSERVO				0x00000000		// UPMV4 with ISELDRV.VXD
#define MCTL_TYPE_C142					0x00000001		// C142 control / RS232
#define MCTL_TYPE_IFC5					0x00000001		// Interface card V5.c, similar to C142
#define MCTL_TYPE_EP1090				0x00000002		// EP1090 control / RS232
#define MCTL_TYPE_IMC4					0x00000003		// IMC4 control / RS232
#define MCTL_TYPE_MPK3					0x00000004		// MPK3 
#define MCTL_TYPE_MPK1					0x00000005		// MPK1
#define MCTL_TYPE_L292					0x00000006		// L292 
#define MCTL_TYPE_IMK1					0x00000007		// IMK1
#define MCTL_TYPE_PSK1					0x00000008		// PSK1
#define MCTL_TYPE_CANCONTROL			0x00000009		// CAN controlled motion control
#define MCTL_TYPE_IMS6					0x0000000A		// IMS6 control / RS232
#define MCTL_TYPE_CISA					0x0000000B		// CAN Single Axis Control
#define MCTL_TYPE_IFC					0x0000000C		// Common type interface card (IMC4, IFC5, IML4, EP1090)
#define MCTL_TYPE_IML4					0x0000000D		// Stepper motor control IML4
#define MCTL_TYPE_ADMINISTRATOR			0x10000000
#define MCTL_TYPE_OTHER					0x80000000
#define MCTL_TYPE_OEM					0x80000001		// OEM Motion Control
#define MCTL_TYPE_MTASC					0x80000002		// MTASC Motion Control Fa. Trimeta
#define MCTL_TYPE_LOGOSOL_RS485			0x80000003		// KP 10.08.2004 Logosol RS485 Motion Control

#define MCTL_TYPE_UNKNOWN				0xFFFFFFFF		// Unknown Motion Control



#define MCTL_MAX_AXIS					9				// Number of axes which can be handled by this interface
#define MCTL_NUM_AXIS					MCTL_MAX_AXIS


#ifndef NOMOVE
 #define NOMOVE							0x3FFFFFFF		// Constant NOMOVE when executing movement to absolute position
#endif

#ifndef ACTPOS
 #define ACTPOS							0x3FFFFFFF		// same as NOMOVE
#endif

#ifndef MAXMOVE
 #define MAXMOVE						0x3FFFFFFE		// Maximum length of a movement
#endif

#ifndef MAXMOVE_POS
 #define MAXMOVE_POS					0x3FFFFFFE		// Maximum length of a movement in pos. dir.
#endif

#ifndef MAXMOVE_NEG
 #define MAXMOVE_NEG					0xC0000002		// Maximum length of a movement in neg. dir.
#endif

#ifndef CURRENTVALUE
 #define CURRENTVALUE					0x3FFFFFFF		// Constant CURRENTVALUE for universal use
#endif


#define MCTL_CFG_AXIS_NOTINUSE			0x00			// Axis NOT in use in this configuration
#define MCTL_CFG_AXIS_INUSE				0x01			// Axis in use in this configuration

#define MCTL_CFG_AXISTYPE_LINEAR		0x00			// Axis type Linear Axis
#define MCTL_CFG_AXISTYPE_ROT			0x01			// Axis type Rotational Axis

														// Interpolation abilities of the control
#define MCTL_CFG_INTER_LINEAR			0x00000001		// Can execute linear interpolation
#define MCTL_CFG_INTER_CIRCLE			0x00000002		// Can execute circular interpolation
#define MCTL_CFG_INTER_HELIX			0x00000004		// Can execute helix interpolation
#define MCTL_CFG_INTER_SPLINE			0x00000008		// Can execute spline interpolation
#define MCTL_CFG_INTER_BEZIER			0x00000010		// Can execute bezier interpolation
#define MCTL_CFG_PTP					0x00000020		// Can execute point to point movements
#define MCTL_CFG_SYNC_PTP				0x00000040		// Can execute synchronized point to point movements
#define MCTL_CFG_DRILLCYCLE				0x00001000		// KP 16.07.2001 Able to drill via NCDRILL.DLL

#define MCTL_CFG_PATH_PRECALC			0x00010000		// Path processing abilities of the motion control
#define MCTL_CFG_PATH_ONLINE			0x00020000		// 
#define MCTL_CFG_PATH_BLOCKTRANSFER		0x00040000		// 

#define MCTL_CFG_MULTIPLE_MODULE_ACCESS	0x10000000		// Reserved


#ifndef AXIS_NOTINUSE
 #define AXIS_NOTINUSE					0x00			// The more common version MCTL_CFG_AXIS_NOTINUSE
#endif

#ifndef AXIS_INUSE
 #define AXIS_INUSE						0x01			// The more common version MCTL_CFG_AXIS_INUSE
#endif

#ifndef TYPE_LINEAR	
 #define TYPE_LINEAR					0x00			// The more common version MCTL_CFG_AXISTYPE_LINEAR
#endif												                              

#ifndef TYPE_LIN	
 #define TYPE_LIN						0x00			// Another common version MCTL_CFG_AXISTYPE_LIN
#endif												                              
													                              
#ifndef TYPE_ROT
 #define TYPE_ROT						0x01			// The more common version  MCTL_CFG_AXISTYPE_ROT
#endif

														// Definition of mask bits for
														// various function which provide
														// axis access by a mask bit
														// 
														// Bit   8 7 6 5 4 3 2 1 0
														// Axis	 W V U C B A Z Y X
														// Num   9 8 7 6 5 4 3 2 1
#ifndef AXIS_X
 #define AXIS_X							0x001
#endif

#ifndef AXIS_Y
 #define AXIS_Y							0x002
#endif
	
#ifndef AXIS_Z
 #define AXIS_Z							0x004
#endif

#ifndef AXIS_A
 #define AXIS_A							0x008
#endif

#ifndef AXIS_B
 #define AXIS_B							0x010
#endif

#ifndef AXIS_C
 #define AXIS_C							0x020
#endif

#ifndef AXIS_U
 #define AXIS_U							0x040
#endif

#ifndef AXIS_V
 #define AXIS_V							0x080
#endif

#ifndef AXIS_W
 #define AXIS_W							0x100
#endif


#ifndef AXIS_NONE									
 #define AXIS_NONE						0x000			// No axis selected
#endif													

#ifndef AXIS_XYZ												  
 #define AXIS_XYZ						0x007			// Axes X Y Z selected
#endif													

#ifndef AXIS_XYZA									
 #define AXIS_XYZA						0x00F			// Axes X Y Z A selected
#endif													

#ifndef AXIS_ALL									
 #define AXIS_ALL						0x1FF			// All axes selected
#endif




#ifndef ID_X	
 #define ID_X							0		
#endif

#ifndef ID_Y
 #define ID_Y							1
#endif

#ifndef ID_Z
 #define ID_Z							2
#endif

#ifndef ID_A
 #define ID_A							3
#endif

#ifndef ID_B
 #define ID_B							4
#endif

#ifndef ID_C
 #define ID_C							5
#endif
							
#ifndef ID_U
 #define ID_U							6
#endif
							
#ifndef ID_V
 #define ID_V							7
#endif
 
#ifndef ID_W
 #define ID_W							8
#endif

							
#ifndef CI_DIR_CW							
 #define CI_DIR_CW						0x00			// Circular interpolation, direction ClockWise
#endif

#ifndef CI_DIR_CCW							
 #define CI_DIR_CCW						0x01			// Circular interpolation, direction CounterClockWise
#endif
							
#ifndef CI_PLANE_XY							
 #define CI_PLANE_XY					0x00			// Circular interpolation, Plane XY
#endif

#ifndef CI_PLANE_XZ							
 #define CI_PLANE_XZ					0x01			// XZ
#endif

#ifndef CI_PLANE_YZ
 #define CI_PLANE_YZ					0x02			// YZ
#endif


#ifndef HLX_DIR_CW							
 #define HLX_DIR_CW						0x00			// Helix interpolation, direction ClockWise
#endif

#ifndef HLX_DIR_CCW							
 #define HLX_DIR_CCW					0x01			// Helix interpolation, direction CounterClockWise
#endif
							
#ifndef HLX_PLANE_XY							
 #define HLX_PLANE_XY					0x00			// Helix interpolation, Plane XY
#endif

#ifndef HLX_PLANE_XZ							
 #define HLX_PLANE_XZ					0x01			// XZ
#endif

#ifndef HLX_PLANE_YZ
 #define HLX_PLANE_YZ					0x02			// YZ
#endif



#ifndef MSTATE_START									// Flags for access to a running movement
 #define MSTATE_START					0x00			// Restart a stopped motion
#endif

#ifndef MSTATE_STOP								
 #define MSTATE_STOP					0x01			// Stop the currently running motion
#endif

#ifndef MSTATE_BREAK								
 #define MSTATE_BREAK					0x02			// Break currently running motion immediately
#endif

#ifndef MSTATE_ABORT								
 #define MSTATE_ABORT					0x03			// Abort currently running motion
#endif



#define AXIS_STAT_INMOTION				0x00000001		// Status flags, Member dwCommon
#define AXIS_STAT_INSTOPMODE			0x00000002
#define AXIS_STAT_CURRENTOFF			0x00000004
#define AXIS_STAT_ISMOVING				0x00000008
										
#define AXIS_STAT_HWLSNEGACTIVE			0x00000100
#define AXIS_STAT_HWLSPOSACTIVE			0x00000200
#define AXIS_STAT_HWLSDURINGMOTION		0x00000400
#define AXIS_STAT_SWLSNEGACTIVE			0x00001000
#define AXIS_STAT_SWLSPOSACTIVE			0x00002000
#define AXIS_STAT_NEEDREFERENCERUN		0x00010000
#define AXIS_STAT_AFTERRUNERROR			0x00020000
#define AXIS_STAT_COMMUNICATION_FAIL	0x00040000
#define AXIS_STAT_HARDWARE_FAIL			0x00080000		
#define AXIS_STAT_POWER_FAIL			0x00100000
#define AXIS_STAT_SC_FAIL				0x00200000
#define AXIS_STAT_CURRENT_LIMITER		0x00400000
			  
#define AXIS_STAT_ISBUSY				0x00000001		// Status flags, Member dwExtended 
#define AXIS_STAT_DISABLED				0x00000002		
#define AXIS_STAT_ISINITIALIZED			0x00000004		
#define AXIS_STAT_READY					0x00000008		
#define AXIS_STAT_HARDWARESPECERROR		0x00000020		// KP 13.08.01 A hardware specific error is active
#define AXIS_STAT_RESERVED1				0x10000000
#define AXIS_STAT_RESERVED2				0x20000000
#define AXIS_STAT_RESERVED3				0x40000000


#define MCTL_STAT_INMOTION				0x00000001		// Status flags, Member dwCommon
#define MCTL_STAT_INSTOPMODE			0x00000002
#define MCTL_STAT_INTEACHMODE			0x00000004
#define MCTL_STAT_INTESTMODE			0x00000008
#define MCTL_STAT_CURRENTOFF			0x00000010
#define MCTL_STAT_INPATHMOTION			0x00000020
#define MCTL_STAT_ISMOVING				0x00000040
#define MCTL_STAT_PATHSTARTED			0x00000080		// KP Added 29.08.2001

#define MCTL_STAT_NEEDREFERENCERUN		0x00010000
#define MCTL_STAT_BREAKERROR			0x00020000
#define MCTL_STAT_HWLSACTIVE			0x00040000
#define MCTL_STAT_SWLSACTIVE			0x00080000
#define MCTL_STAT_HWLSDURINGMOTION		0x00100000
#define MCTL_STAT_AFTERRUNERROR			0x00200000
#define MCTL_STAT_LOADPATHDATAERROR		0x00400000
#define MCTL_STAT_KEYSWITCHERROR		0x00800000
#define MCTL_STAT_KEYSWDURINGMOTION		0x01000000
#define MCTL_STAT_POWER_FAIL			0x02000000
#define MCTL_STAT_SC_FAIL				0x04000000
#define MCTL_STAT_HARDWARE_FAIL			0x08000000		// KP Neu 24.01.01
#define MCTL_STAT_COMMUNICATION_FAIL	0x10000000		// KP Neu 24.01.01
#define MCTL_STAT_RESERVED1				0x40000000		// KP Neu 23.06.2005


#define MCTL_STAT_HWLS_X_NEG			0x00000001		// Status flags, Member dwHWLSNeg
#define MCTL_STAT_HWLS_Y_NEG			0x00000002								
#define MCTL_STAT_HWLS_Z_NEG			0x00000004								
#define MCTL_STAT_HWLS_A_NEG			0x00000008								
#define MCTL_STAT_HWLS_B_NEG			0x00000010								
#define MCTL_STAT_HWLS_C_NEG			0x00000020
#define MCTL_STAT_HWLS_U_NEG			0x00000040								
#define MCTL_STAT_HWLS_V_NEG			0x00000080								
#define MCTL_STAT_HWLS_W_NEG			0x00000100

#define MCTL_STAT_HWLS_X_POS			0x00000001		// Status flags, Member dwHWLSPos 
#define MCTL_STAT_HWLS_Y_POS			0x00000002		 
#define MCTL_STAT_HWLS_Z_POS			0x00000004		 
#define MCTL_STAT_HWLS_A_POS			0x00000008		 
#define MCTL_STAT_HWLS_B_POS			0x00000010
#define MCTL_STAT_HWLS_C_POS			0x00000020
#define MCTL_STAT_HWLS_U_POS			0x00000040								
#define MCTL_STAT_HWLS_V_POS			0x00000080								
#define MCTL_STAT_HWLS_W_POS			0x00000100
									    
#define MCTL_STAT_SWLS_X_NEG			0x00000001		// Status flags, Member dwSWLSNeg
#define MCTL_STAT_SWLS_Y_NEG			0x00000002		
#define MCTL_STAT_SWLS_Z_NEG			0x00000004		
#define MCTL_STAT_SWLS_A_NEG			0x00000008
#define MCTL_STAT_SWLS_B_NEG			0x00000010
#define MCTL_STAT_SWLS_C_NEG			0x00000020
#define MCTL_STAT_SWLS_U_NEG			0x00000040								
#define MCTL_STAT_SWLS_V_NEG			0x00000080								
#define MCTL_STAT_SWLS_W_NEG			0x00000100
									    
#define MCTL_STAT_SWLS_X_POS			0x00000001		// Status flags, Member dwSWLSPos 
#define MCTL_STAT_SWLS_Y_POS			0x00000002		
#define MCTL_STAT_SWLS_Z_POS			0x00000004
#define MCTL_STAT_SWLS_A_POS			0x00000008
#define MCTL_STAT_SWLS_B_POS			0x00000010
#define MCTL_STAT_SWLS_C_POS			0x00000020
#define MCTL_STAT_SWLS_U_POS			0x00000040								
#define MCTL_STAT_SWLS_V_POS			0x00000080								
#define MCTL_STAT_SWLS_W_POS			0x00000100
									    
						 
#define MCTL_STAT_ISBUSY				0x00000001		// Status flags, Member dwExtended 
#define MCTL_STAT_DISABLED				0x00000002		// KP Neu 24.01.01
#define MCTL_STAT_ISINITIALIZED			0x00000004		// KP Neu 24.01.01
#define MCTL_STAT_READY					0x00000008		// KP New 01.11.01
#define MCTL_STAT_DRILLCYCLEACTIVE		0x00000010		// KP 18.07.01 Drill cycle is active 
#define MCTL_STAT_CTRLSPECERROR			0x00000020		// KP 13.08.01 A control specific error is active


#define MCTL_STAT_WNPACTIVE				0x00000001		// KP 14.03.02 A workpiece zero point is active



#ifndef TESTMODE_OFF
 #define TESTMODE_OFF					0x00			// TestMode Off
#endif

#ifndef TESTMODE_ON
 #define TESTMODE_ON					0x01			// TestMode On
#endif

#ifndef TEACHMODE_OFF
 #define TEACHMODE_OFF					0x00			// TeachMode Off
#endif

#ifndef TEACHMODE_ON
 #define TEACHMODE_ON					0x01			// TeachMode On
#endif

#ifndef POWER_OFF
 #define POWER_OFF						0x00			// Disable Power Stages 
#endif

#ifndef POWER_ON
 #define POWER_ON						0x01			// Enable Power Stages 
#endif

														// KP 02.10.2001
#ifndef HWLSBRIDGE_OFF
 #define HWLSBRIDGE_OFF					0x00			// Hardware limit switch bridging off
#endif

#ifndef HWLSBRIDGE_ON
 #define HWLSBRIDGE_ON					0x01			// Hardware limit switch bridging on
#endif



 
//---Data types-------------------------------------------------------------------


#ifndef _AXISPOS_DEFINED_
 #define _AXISPOS_DEFINED_
 typedef struct tagAXISPOS				// Position struct for data transfer
  {
  long X;								// X axis
  long Y;								// Y axis
  long Z;								// Z axis
  long A;								// A revolving around X
  long B;								// B revolving around Y
  long C;								// C revolving around Z
  long U;								// U parallel to X
  long V;								// V parallel to Y
  long W;								// W parallel to Z
  } AXISPOS, *LPAXISPOS;
#endif


#ifndef _DBLAXISPOS_DEFINED_
 #define _DBLAXISPOS_DEFINED_
 typedef struct tagDBLAXISPOS			// double positions
  {
  double X;								// X axis               
  double Y;								// Y axis               
  double Z;								// Z axis               
  double A;								// A revolving around X 
  double B;								// B revolving around Y 
  double C;								// C revolving around Z 
  double U;								// U parallel to X      
  double V;								// V parallel to Y      
  double W;								// W parallel to Z      
  } DBLAXISPOS, *LPDBLAXISPOS;	  
#endif


#ifndef _CIRCLEPARAM_DEFINED_			// KP 28.06.01 Changed to CIRCLEPARAM from CIRCLEPOS
 #define _CIRCLEPARAM_DEFINED_
 typedef struct tagCIRCLEPARAM			// Definition Struct for circle parameters
  {
  DWORD dwPlane;						// Circle working plane
  DWORD dwDirection;					// Circle travel direction (CW/CCW)
  long  lCenter1;						// Center Pt 1 (Plane: XY->X, XZ->X, YZ->Y)
  long  lCenter2;						// Center Pt 2 (Plane: XY->Y, XZ->Z, YZ->Z)
  long  lEndPosX;	 					// Target position of axis X
  long  lEndPosY;						// Target position of axis Y
  long  lEndPosZ;						// Target position of axis Z
  long  lEndPosA;						// Target position of axis A
  long  lEndPosB;						// Target position of axis B
  long  lEndPosC;						// Target position of axis C
  long  lEndPosU;						// Target position of axis U
  long  lEndPosV;						// Target position of axis V
  long  lEndPosW;						// Target position of axis W
  } CIRCLEPARAM, *LPCIRCLEPARAM;
#endif

										// KP 28.06.01 For compatibility with older versions
#ifndef _HELIXPARAM_DEFINED_			// KP New 27.06.01
 #define _HELIXPARAM_DEFINED_
 typedef struct tagHELIXPARAM			// Definition Struct for helix parameters
  {
  DWORD dwPlane;						// Helix working plane
  DWORD dwDirection;					// Helix travel direction (CW/CCW)
  long  lAngle;							// Movement angle
  long  lCenter1;						// Center Pt 1 (Plane: XY->X, XZ->X, YZ->Y)
  long  lCenter2;						// Center Pt 2 (Plane: XY->Y, XZ->Z, YZ->Z)
  long  lEndPosX;						// Target position of axis X
  long  lEndPosY;						// Target position of axis Y
  long  lEndPosZ;						// Target position of axis Z
  long  lEndPosA;						// Target position of axis A
  long  lEndPosB;						// Target position of axis B
  long  lEndPosC;						// Target position of axis C
  long  lEndPosU;						// Target position of axis U
  long  lEndPosV;						// Target position of axis V
  long  lEndPosW;						// Target position of axis W
  } HELIXPARAM, *LPHELIXPARAM;
#endif


#ifndef _MCTLVELOCITY_DEFINED_
 #define _MCTLVELOCITY_DEFINED_
 typedef struct tagMCTLVELOCITY		    // The velocities of the Motion Control
  {
  long lNormVel[2];						// Normal Veloc., linear and rotational axes
  long lFastVel[2];						// Fast Veloc., linear and rotational axes
  long lTeachVel[2];					// Teach Veloc., linear and rotational axes
  long lActVel[2];						// The current physical velocities
  } MCTLVELOCITY, *LPMCTLVELOCITY;
#endif


#ifndef _WNPSTATUS_DEFINED_				// KP New 22.01.2002
 #define _WNPSTATUS_DEFINED_
 typedef struct tagWNPSTATUS		    // The status of the workpiece zero point
  {
  DWORD		dwCommon;					// The common workpiece zero point status
  AXISPOS	Pos;						// Workpiece zero point positions
  } WNPSTATUS, *LPWNPSTATUS;
#endif

										
#ifndef _SWLSSTATUS_DEFINED_			// KP New 22.01.2002
 #define _SWLSSTATUS_DEFINED_
 typedef struct tagSWLSSTATUS		    // The status of the software limit switches
  {
  DWORD		dwEnabled;					// Enabled/disabled status of each axis
  DWORD		dwSWLSNeg;					// Software limit switch status, negative
  DWORD		dwSWLSPos;					// Software limit switch status, positive
  AXISPOS	Neg;						// Negative software limit switch positions
  AXISPOS	Pos;						// Positive software limit switch positions
  BOOL		fActive;					// At least one software limit switch is activated
  } SWLSSTATUS, *LPSWLSSTATUS;
#endif


#ifdef Removed_21_01_2002
#ifndef _MCTLSPEED_DEFINED_				// The older version of the velocity struct
 #define _MCTLSPEED_DEFINED_
 typedef struct tagMCTLSPEED			// The velocities of the Motion Control
  {
  long lNormSpeed[2];					// Normal Veloc., linear and rotational axes
  long lFastSpeed[2];					// Fast Veloc., linear and rotational axes
  long lTeachSpeed[2];					// Teach Veloc., linear and rotational axes
  long lActSpeed[2];					// The current physical velocities
  } MCTLSPEED, *LPMCTLSPEED;
#endif
#endif	//Removed_21_01_2002


#ifndef _MCTLVERSION_DEFINED_
 #define _MCTLVERSION_DEFINED_
 typedef struct tagMCTLVERSION			// Version informations of the DLL
  {
  DWORD	dwType;							// Motion control type, MCTL_TYPE_DCSERVO, ....
  int	iVerMajor;						// Major version number of the DLL
  int	iVerMinor;						// Minor version number of the DLL
  int	iVerRelease;					// Release number of the DLL
  int	iVerBuilt;						// Built number of the DLL
  char	szDescription[255];				// Description of the module
  char	szComment[255];					// Comment concerning purpose, functions etc.
  char	szCompanyName[255];				// Name of the module supplier
} MCTLVERSION, *LPMCTLVERSION;
#endif


#ifndef _AXISCONFIG_DEFINED_
 #define _AXISCONFIG_DEFINED_
 typedef struct tagAXISCONFIG			// Configuration of a single axis
  {
  DWORD dwType;							// Axis type: TYPE_LIN | TYPE_ROT
  BOOL  fInUse;							// Axis is used: AXIS_NOTINUSE | AXIS_INUSE
  DWORD dwID;							// Reserved
  long  lRangeMin;						// Minimum position of the axis, normally 0
  long  lRangeMax;						// Maximum position of the axis
  } AXISCONFIG, *LPAXISCONFIG;
#endif


#ifndef _AXISSTATUS_DEFINED_
 #define _AXISSTATUS_DEFINED_
 typedef struct tagAXISSTATUS			// Axis Status information structure
  {
  DWORD dwCommon;						// Common status information	
  DWORD dwExtended;						// Extended status information

  BOOL  fInMotion;						// Axis is in motion
  BOOL  fInStopMode;					// Axis is in Stop Mode
  BOOL  fCurrentOff;					// Amplifier current is switched off
  BOOL  fIsMoving;						// At least one axis is really moving

  BOOL  fNeedReferenceRun;				// A reference run is required for this axis
  BOOL  fHWLSNegActive;					// The negative hardware limit switch is activated
  BOOL  fHWLSPosActive;					// The positive hardware limit switch is activated
  BOOL  fHWLSDuringMotion;				// A hardware limit sw was activated during a motion
  BOOL  fSWLSNegActive;					// The negative software limit switch is activated
  BOOL  fSWLSPosActive;					// The positive software limit switch is activated
  BOOL  fAfterRunError;					// An afterrun error occured during movement
  BOOL  fCommunicationFail;				// A communication error occured (relates to bus controlled axes)
  BOOL  fHardwareFail;					// Hardware self check of the axis module failed
  BOOL  fPowerFail;						// The power supply of this axis is switched off
  BOOL  fSCFail;						// The axis is blocked by security lock signal
  BOOL  fCurrentLimiter;				// The current limiter of this axis was activated

  BOOL  fIsBusy;						// Axis is busy
  BOOL  fDisabled;						// Axis module is disabled
  BOOL  fIsInitialized;					// Axis initialization complete
  BOOL  fReady;							// Axis is ready for operation
  BOOL	fHardwareSpecError;				// KP 13.08.2001 An axis hardware specific error occured
  } AXISSTATUS, *LPAXISSTATUS;
#endif


#ifndef _MCTLCONFIG_DEFINED_
 #define _MCTLCONFIG_DEFINED_
 typedef struct tagMCTLCONFIG			// Configuration of the motion control
  {
  DWORD		dwAbility;					// Abilities of the motion control module
  DWORD		dwNumAxis;					// Number of axes available in this motion control structure
  AXISCONFIG	Axis[MCTL_MAX_AXIS];	// The configuration of the various axes
  } MCTLCONFIG, *LPMCTLCONFIG;
#endif


#ifndef _MCTLSTATUS_DEFINED_
 #define _MCTLSTATUS_DEFINED_
 typedef struct tagMCTLSTATUS			// Status information structure
  {
  DWORD dwCommon;						// Common status information	
  DWORD dwHWLSNeg;						// Hardware limit switch status, negative
  DWORD dwHWLSPos;						// Hardware limit switch status, positive
  DWORD dwSWLSNeg;						// Software limit switch status, negative
  DWORD dwSWLSPos;						// Software limit switch status, positive
  DWORD dwExtended;						// Extended status information

  BOOL  fInMotion;						// At least one axis is in motion
  BOOL  fInStopMode;					// At least one axis is in Stop Mode
  BOOL  fInTeachMode;					// Teach mode activated
  BOOL  fInTestMode;					// Test mode activated
  BOOL  fCurrentOff;					// Amplifier current is switched off
  BOOL  fInPathMotion;					// A path segment is processed at the moment
  BOOL  fIsMoving;						// At least one axis is really moving
  BOOL  fNeedReferenceRun;				// A reference run is required
  BOOL  fBreakError;					// A break was executed, reset required
  BOOL  fHWLSActive;					// At least one hardware limit switch is activated
  BOOL  fSWLSActive;					// At least one software limit switch is activated
  BOOL  fHWLSDuringMotion;				// A hardware limit sw was activated during a motion
  BOOL  fAfterRunError;					// An afterrun error occured during movement
  BOOL  fPowerFail;						// The power supply is switched off
  BOOL  fSCFail;						// Motion control is blocked by security module
  BOOL  fIsBusy;						// The motion control is busy at the moment
  BOOL	fIsInitialized;					// KP 10.07.2001 Motion control is initialized
  BOOL	fDisabled;						// KP 10.07.2001 Motion control is disabled
  BOOL	fHardwareFail;					// KP 10.07.2001 Hardware error was signaled
  BOOL	fCommunicationFail;				// KP 10.07.2001 Communication error between DLL and control
  BOOL	fDrillCycleActive;				// KP 18.07.2001 A drill cycle is currently performed
  BOOL	fCtrlSpecError;					// KP 13.08.2001 A control dpecific error occured
  BOOL	fPathStarted;					// KP 29.08.2001 Path operation was started by user
  } MCTLSTATUS, *LPMCTLSTATUS;
#endif




//---Drill flags and definitions--------------------------------------------------

#define DRILL_CYCLE_SIMPLE				0x01			// Simple drilling
#define DRILL_CYCLE_PECK				0x02			// Peck drilling
#define DRILL_CYCLE_CHIPBREAK			0x03			// Chip break drilling

#define DRILL_STAT_ISBUSY				0x00000001		// A drilling is in progress at the moment
#define DRILL_STAT_ISINITIALIZED		0x00000004		// Drill parameters are already defined

#define DRILL_PLANE_XY					0x00			// Drill plane XY
#define DRILL_PLANE_XZ					0x01			// Drill plane XZ
#define DRILL_PLANE_YZ					0x02			// Drill plane YZ

#define DRILL_DIR_NEG					0x00			// Drill direction negative, standard
#define DRILL_DIR_POS					0x01			// Drill direction positive


//---Drill data types-------------------------------------------------------------


#ifndef _DRILLPARAM_DEFINED_
 #define _DRILLPARAM_DEFINED_
 typedef struct tagDRILLPARAM			// Drill parameters
  {
  DWORD	dwDrillCycle;					// Current drill cycle type
  long  lRefHeight;						// Drill reference plane Z
  long  lDepth;							// Depth of the hole to drill
  long  lDelay;							// Time delay at bottom of the hole
  long	lNormVel;						// Normal velocity in mm/sec.
  long	lFastVel;						// Fast velocity in mm/sec.
  long	lFirstIncrDepth;				// Amount of first peck increment
  long	lOtherIncrDepth;				// Second or other peck increments
  long	lIncrDepthDecr;					// Peck increment decrementation per drill step
  long	lIncrRetreat;					// Relative cutter retraction (chip break) or difference to last position (peck drilling)
  long	lRetreat;						// Retraction height after drilling (rel. to lRefHeight)
  long	lSecurityHeight;				// Security plane after drilling, rel. to lRefPlane
  DWORD	dwPlane;						// Drill reference plane, standard is XY
  DWORD	dwDirection;					// Drill direction, standard is DRILL_DIR_NEG
  } DRILLPARAM, *LPDRILLPARAM;
#endif


#ifndef _DRILLSTATUS_DEFINED_
 #define _DRILLSTATUS_DEFINED_
 typedef struct tagDRILLSTATUS			// Drill status
  {
  DWORD dwCommon;						// Common drill status flags
  BOOL	fIsBusy;						// A drilling is in progress at the moment
  BOOL	fIsInitialized;					// Drill parameters are already defined
  } DRILLSTATUS, *LPDRILLSTATUS;
#endif




//---Buffered work mode and path mode flags---------------------------------------

													// Buffer sizes of motion controls
#define MCTL_BUFSIZE_MIN				1			// with a command buffer option   				  
#define MCTL_BUFSIZE_NORMAL				8
#define MCTL_BUFSIZE_DEFAULT			MCTL_BUFSIZE_NORMAL
#define MCTL_BUFSIZE_MAX				16
#define MCTL_BUFSIZE_INFINITE			0x3FFFFFFF

#define MCTL_PATH_OFF					0x00			// Disable Online Path calculation
#define MCTL_PATH_ON					0x01			// Enable Online Path calculation

#define MCTL_PATH_ISENABLED				0x00000001		// dwCommon flags
#define MCTL_PATH_ISSTARTED				0x00000002

#define MCTL_PATH_ISBUSY				0x00000001		// dwExtended flags



//---Buffered work mode and path mode data types----------------------------------


#ifndef _CPBSTATUS_DEFINED_
 #define _CPBSTATUS_DEFINED_
 typedef struct tagCPBSTATUS			// Continuous Path operation Buffer status
  {
  DWORD dwCommon;						// Common path status information	
  DWORD dwExtended;						// Extended path status information

  long	lBufSize;						// Currently set maximum command buffer size                           
  long	lNumCmdInBuf;					// Number of commands in buffer                                
  long	lNumFreeCmdInBuf;				// Number of free places in the buffer (lNumBufFree=lBufSize-lNumBufCmd)
  long	lCmdInProcess;					// Currently executed command in buffer (zero based index)

  BOOL  fIsEnabled;						// Online Path Calculation is enabled
  BOOL  fIsBusy;
  BOOL  fIsStarted;						// The control is busy doing a path motion
  } CPBSTATUS, *LPCPBSTATUS;
#endif






//---Function prototypes---------------------------------------------


#if defined(_MCTL_DLL_INTERNAL_)
 #define MCTL_DLLFUNC			__declspec(dllexport) _stdcall
#else
 #define MCTL_DLLFUNC			__declspec(dllimport) _stdcall
#endif


#if defined(__BORLANDC__)
 extern "C"
 {
#endif

DWORD MCTL_DLLFUNC mctl_SetUnits(LPVOID pUnit, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_Initialize(char *szInitFile);
DWORD MCTL_DLLFUNC mctl_Exit(void);
DWORD MCTL_DLLFUNC mctl_Setup(void);
DWORD MCTL_DLLFUNC mctl_Diagnosis(void);
DWORD MCTL_DLLFUNC mctl_GetVersion(LPMCTLVERSION lpMctlVer, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetConfiguration(LPMCTLCONFIG lpMctlCfg, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetAxisConfiguration(UINT nAxis, LPAXISCONFIG lpAxisCfg, DWORD dwSize);	
DWORD MCTL_DLLFUNC mctl_GetStatus(LPMCTLSTATUS lpMctlStatus, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetStatusOnEvent(DWORD dwEvent, DWORD dwMilliSeconds, LPMCTLSTATUS lpMctlStatus, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetAxisStatus(UINT nAxis, LPAXISSTATUS lpAxisStatus, DWORD dwSize);	
DWORD MCTL_DLLFUNC mctl_Reset(void);
DWORD MCTL_DLLFUNC mctl_Reference(DWORD dwAxis);																// Reference run, axes AXIS_X, AXIS_Y,...
DWORD MCTL_DLLFUNC mctl_ReferenceBreak(void);																	// KP New 02.10.2003 mctl_ReferenceBreak() / CAN Bus Control
DWORD MCTL_DLLFUNC mctl_SetTestMode(DWORD dwOnOff);
DWORD MCTL_DLLFUNC mctl_SetTeachMode(DWORD dwOnOff);
DWORD MCTL_DLLFUNC mctl_SetPowerState(DWORD dwOnOff);
DWORD MCTL_DLLFUNC mctl_SetVelocity(LPMCTLVELOCITY lpMctlVel, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetVelocity(LPMCTLVELOCITY lpMctlVel, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_SetOverride(long lOverride);
DWORD MCTL_DLLFUNC mctl_GetOverride(LPLONG lpOverride);
DWORD MCTL_DLLFUNC mctl_SetActPosWNP(void);
DWORD MCTL_DLLFUNC mctl_SetWNPAbs(LPAXISPOS AbsWPZero, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_SetWNPRel(LPAXISPOS RelWPZero, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetWNP(LPAXISPOS WPZero, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetWNPStatus(LPWNPSTATUS WNPStatus, DWORD dwSize);				// KP New 22.01.2002
DWORD MCTL_DLLFUNC mctl_ClearWNP(void);

DWORD MCTL_DLLFUNC mctl_SetSWLS(LPSWLSSTATUS SWLSAbs, DWORD dwSize);					// KP New 22.01.2002
DWORD MCTL_DLLFUNC mctl_GetSWLSStatus(LPSWLSSTATUS SWLSStatus, DWORD dwSize);			// KP New 22.01.2002
DWORD MCTL_DLLFUNC mctl_EnableSWLS(DWORD dwAxis, DWORD dwOptions);						// KP New 22.01.2002
DWORD MCTL_DLLFUNC mctl_ClearSWLS(void);												// KP New 22.01.2002

DWORD MCTL_DLLFUNC mctl_MoveAbs(LPAXISPOS lpAbsPos, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_MoveRel(LPAXISPOS lpRelPos, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_MoveRelUntilPortEvent(LPAXISPOS lpRelPos, DWORD dwSize, DWORD dwMask, DWORD dwValue); 
DWORD MCTL_DLLFUNC mctl_FastAbs(LPAXISPOS lpAbsPos, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_FastRel(LPAXISPOS lpRelPos, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_CircleAbs(LPCIRCLEPARAM lpAbsCiParam, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_CircleRel(LPCIRCLEPARAM lpRelCiParam, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_HelixAbs(LPHELIXPARAM lpAbsHlxParam, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_HelixRel(LPHELIXPARAM lpRelHlxParam, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_SplineAbs(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_SplineRel(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_BezierAbs(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_BezierRel(LPAXISPOS lpNodes, long lNumNodes, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetPosition(LPAXISPOS lpPos, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_GetDestinationPos(LPAXISPOS lpDestPos, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_SetMotionState(DWORD dwState);
DWORD MCTL_DLLFUNC mctl_LeaveHWLS(DWORD dwAxis, LPVOID lpParam);
DWORD MCTL_DLLFUNC mctl_HWLSBridge(DWORD dwOnOff);										// KP 02.10.2001
DWORD MCTL_DLLFUNC mctl_SetDrillParam(LPDRILLPARAM lpDrillParam, DWORD dwSize);			// KP 16.07.2001
DWORD MCTL_DLLFUNC mctl_GetDrillParam(LPDRILLPARAM lpDrillParam, DWORD dwSize);			// KP 18.07.2001
DWORD MCTL_DLLFUNC mctl_Drill(LPAXISPOS lpDrillPos, DWORD dwSize);						// KP 16.07.2001
DWORD MCTL_DLLFUNC mctl_Operate(DWORD dwOperationCode, LPVOID lpParam);					// KP 04.10.2001			// KP 16.07.2001



										// Additional, not unified functions for
										// IO operation based on motion control ports 
DWORD MCTL_DLLFUNC mctl_InputBit(DWORD dwPort, DWORD dwBit, LPDWORD lpValue);
DWORD MCTL_DLLFUNC mctl_InputByte(DWORD dwPort, LPDWORD lpValue);
DWORD MCTL_DLLFUNC mctl_InputWord(DWORD dwPort, LPDWORD lpValue);
DWORD MCTL_DLLFUNC mctl_InputDWord(DWORD dwPort, LPDWORD lpValue);
DWORD MCTL_DLLFUNC mctl_OutputBit(DWORD dwPort, DWORD dwBit, DWORD dwValue);
DWORD MCTL_DLLFUNC mctl_OutputByte(DWORD dwPort, DWORD dwValue);
DWORD MCTL_DLLFUNC mctl_OutputWord(DWORD dwPort, DWORD dwValue);
DWORD MCTL_DLLFUNC mctl_OutputDWord(DWORD dwPort, DWORD dwValue);
DWORD MCTL_DLLFUNC mctl_ReadOutputBit(DWORD dwPort, DWORD dwBit, LPDWORD lpValue);
DWORD MCTL_DLLFUNC mctl_ReadOutputByte(DWORD dwPort, LPDWORD lpValue);
DWORD MCTL_DLLFUNC mctl_ReadOutputWord(DWORD dwPort, LPDWORD lpValue);
DWORD MCTL_DLLFUNC mctl_ReadOutputDWord(DWORD dwPort, LPDWORD lpValue);


										// KP 28.05.2001
										// Buffered Work Mode and 
										// Continuous Path Processing using
										// Online Vector Transit Calculation

										// Commands with prefix mctl_cp_ use the 
										// Motion Control command buffer to store
										// the commands for online path calculation

										// 27.09.2001 KP Changed to simplified version

DWORD MCTL_DLLFUNC mctl_cp_SetBufferSize(DWORD dwBufferSize);
DWORD MCTL_DLLFUNC mctl_cp_EnablePath(DWORD dwFlags);
DWORD MCTL_DLLFUNC mctl_cp_DisablePath(DWORD dwFlags);
DWORD MCTL_DLLFUNC mctl_cp_StartPath(DWORD dwFlags);
DWORD MCTL_DLLFUNC mctl_cp_EndPath(DWORD dwFlags);
DWORD MCTL_DLLFUNC mctl_cp_GetBufferStatus(LPCPBSTATUS lpContPathBufferStatus, DWORD dwSize);

DWORD MCTL_DLLFUNC mctl_cp_SetVelocity(LPMCTLVELOCITY lpMctlVel, DWORD dwSize);
DWORD MCTL_DLLFUNC mctl_cp_OutputBit(DWORD dwPort, DWORD dwBit, DWORD dwValue);
DWORD MCTL_DLLFUNC mctl_cp_OutputByte(DWORD dwPort, DWORD dwValue);
DWORD MCTL_DLLFUNC mctl_cp_OutputWord(DWORD dwPort, DWORD dwValue);
DWORD MCTL_DLLFUNC mctl_cp_OutputDWord(DWORD dwPort, DWORD dwValue);


#if defined(__BORLANDC__)
 }
#endif

										// Explicit binding:
										// Declaration of function prototypes
										// to access the spindle DLL functions

typedef DWORD (_stdcall * MCTL_SETUNITS)(LPVOID, DWORD);
typedef DWORD (_stdcall * MCTL_INITIALIZE)(char *);
typedef DWORD (_stdcall * MCTL_EXIT)(void);
typedef DWORD (_stdcall * MCTL_SETUP)(void);
typedef DWORD (_stdcall * MCTL_DIAGNOSIS)(void);
typedef DWORD (_stdcall * MCTL_GETVERSION)(LPVOID, DWORD);
typedef DWORD (_stdcall * MCTL_GETCONFIGURATION)(LPVOID, DWORD);
typedef DWORD (_stdcall * MCTL_GETAXISCONFIGURATION)(UINT, LPAXISCONFIG, DWORD);
typedef DWORD (_stdcall * MCTL_GETSTATUS)(LPMCTLSTATUS, DWORD);
typedef DWORD (_stdcall * MCTL_GETSTATUSONEVENT)(DWORD, DWORD, LPMCTLSTATUS, DWORD);
typedef DWORD (_stdcall * MCTL_GETAXISSTATUS)(UINT, LPAXISSTATUS, DWORD);
typedef DWORD (_stdcall * MCTL_RESET)(void);
typedef DWORD (_stdcall * MCTL_REFERENCE)(DWORD);
typedef DWORD (_stdcall * MCTL_REFERENCEBREAK)(void);					// KP New 02.10.2003 mctl_ReferenceBreak() / CAN Bus Control
typedef DWORD (_stdcall * MCTL_SETTESTMODE)(DWORD);
typedef DWORD (_stdcall * MCTL_SETTEACHMODE)(DWORD);
typedef DWORD (_stdcall * MCTL_SETPOWERSTATE)(DWORD);
typedef DWORD (_stdcall * MCTL_SETVELOCITY)(LPMCTLVELOCITY, DWORD);
typedef DWORD (_stdcall * MCTL_GETVELOCITY)(LPMCTLVELOCITY, DWORD);
typedef DWORD (_stdcall * MCTL_SETOVERRIDE)(LONG);
typedef DWORD (_stdcall * MCTL_GETOVERRIDE)(LPLONG);
typedef DWORD (_stdcall * MCTL_SETACTPOSWNP)(void);
typedef DWORD (_stdcall * MCTL_SETWNPABS)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_SETWNPREL)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_GETWNP)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_GETWNPSTATUS)(LPWNPSTATUS, DWORD);		// KP New 22.01.2002
typedef DWORD (_stdcall * MCTL_CLEARWNP)(void);
typedef DWORD (_stdcall * MCTL_SETSWLS)(LPSWLSSTATUS, DWORD);		// KP New 22.01.2002
typedef DWORD (_stdcall * MCTL_GETSWLSSTATUS)(LPSWLSSTATUS, DWORD);		// KP New 22.01.2002
typedef DWORD (_stdcall * MCTL_ENABLESWLS)(DWORD, DWORD);				// KP New 22.01.2002
typedef DWORD (_stdcall * MCTL_CLEARSWLS)(void);						// KP New 22.01.2002
typedef DWORD (_stdcall * MCTL_MOVEABS)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_MOVEREL)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_MOVERELUNTILPORTEVENT)(LPAXISPOS, DWORD, DWORD, DWORD); 
typedef DWORD (_stdcall * MCTL_FASTABS)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_FASTREL)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_CIRCLEABS)(LPCIRCLEPARAM, DWORD);
typedef DWORD (_stdcall * MCTL_CIRCLEREL)(LPCIRCLEPARAM, DWORD);
typedef DWORD (_stdcall * MCTL_HELIXABS)(LPHELIXPARAM, DWORD);
typedef DWORD (_stdcall * MCTL_HELIXREL)(LPHELIXPARAM, DWORD);
typedef DWORD (_stdcall * MCTL_SPLINEABS)(LPAXISPOS, long, DWORD);
typedef DWORD (_stdcall * MCTL_SPLINEREL)(LPAXISPOS, long, DWORD);
typedef DWORD (_stdcall * MCTL_BEZIERABS)(LPAXISPOS, long, DWORD);
typedef DWORD (_stdcall * MCTL_BEZIERREL)(LPAXISPOS, long, DWORD);
typedef DWORD (_stdcall * MCTL_GETPOSITION)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_GETDESTINATIONPOS)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_SETMOTIONSTATE)(DWORD);
typedef DWORD (_stdcall * MCTL_LEAVEHWLS)(DWORD, LPVOID);
typedef DWORD (_stdcall * MCTL_HWLSBRIDGE)(DWORD);						// KP 02.10.2001
typedef DWORD (_stdcall * MCTL_SETDRILLPARAM)(LPDRILLPARAM, DWORD);
typedef DWORD (_stdcall * MCTL_GETDRILLPARAM)(LPDRILLPARAM, DWORD);
typedef DWORD (_stdcall * MCTL_DRILL)(LPAXISPOS, DWORD);
typedef DWORD (_stdcall * MCTL_OPERATE)(DWORD, LPVOID);

										// Additional, not unified functions for
										// IO operation based on motion control ports 
typedef DWORD (_stdcall * MCTL_INITOUTPUT)(DWORD);
typedef DWORD (_stdcall * MCTL_INPUTBIT)(DWORD, DWORD, LPDWORD);
typedef DWORD (_stdcall * MCTL_INPUTBYTE)(DWORD, LPDWORD);
typedef DWORD (_stdcall * MCTL_INPUTWORD)(DWORD, LPDWORD);
typedef DWORD (_stdcall * MCTL_INPUTDWORD)(DWORD, LPDWORD);
typedef DWORD (_stdcall * MCTL_OUTPUTBIT)(DWORD, DWORD, DWORD);
typedef DWORD (_stdcall * MCTL_OUTPUTBYTE)(DWORD, DWORD);
typedef DWORD (_stdcall * MCTL_OUTPUTWORD)(DWORD, DWORD);
typedef DWORD (_stdcall * MCTL_OUTPUTDWORD)(DWORD, DWORD);
typedef DWORD (_stdcall * MCTL_READOUTPUTBIT)(DWORD, DWORD, LPDWORD);
typedef DWORD (_stdcall * MCTL_READOUTPUTBYTE)(DWORD, LPDWORD);
typedef DWORD (_stdcall * MCTL_READOUTPUTWORD)(DWORD, LPDWORD);
typedef DWORD (_stdcall * MCTL_READOUTPUTDWORD)(DWORD, LPDWORD);



										// KP 13.09.2001
										// Function prototypes for dynamically 
										// loading of buffered mode and 
										// path operation functions
										// 27.09.2001 KP Changed to simplified version
typedef DWORD (_stdcall * MCTL_CP_SETBUFFERSIZE)(DWORD);
typedef DWORD (_stdcall * MCTL_CP_ENABLEPATH)(DWORD);
typedef DWORD (_stdcall * MCTL_CP_DISABLEPATH)(DWORD);
typedef DWORD (_stdcall * MCTL_CP_STARTPATH)(DWORD);
typedef DWORD (_stdcall * MCTL_CP_ENDPATH)(DWORD);
typedef DWORD (_stdcall * MCTL_CP_GETBUFFERSTATUS)(LPCPBSTATUS, DWORD);
typedef DWORD (_stdcall * MCTL_CP_SETVELOCITY)(LPMCTLVELOCITY, DWORD);
typedef DWORD (_stdcall * MCTL_CP_OUTPUTBIT)(DWORD, DWORD, DWORD);
typedef DWORD (_stdcall * MCTL_CP_OUTPUTBYTE)(DWORD, DWORD);
typedef DWORD (_stdcall * MCTL_CP_OUTPUTWORD)(DWORD, DWORD);
typedef DWORD (_stdcall * MCTL_CP_OUTPUTDWORD)(DWORD, DWORD);



#endif  // #ifndef MCTL_H_INCLUDED

