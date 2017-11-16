// ******************************************************************
// 
//  File     : axctl.h
//
//  Purpose  : Diese Headerdatei definiert alle oeffentlichen 
//             Funktionen zur Ansteuerung von einzelnen Achsen 
//             (Handlingachsen) ueber den CAN-Bus bzw. 
//             der seriellen Schnittstelle über das 
//             Positioniermodul UVE8112
//
//             In dieser Datei wird ebenfalls die Funktionsweise
//             und Verwendung der Schnittstelle beschrieben.
//             Diese Datei ist somit als Handbuch zur Schnittstelle
//             zu verstehen
//
//  Copyright: isel automation KG
//
//             Um die Schnittstelle in einen Visual C++ 6.0 Projekt verwenden
//             zu können muss eine der beiden Libraries
//
//             axctl_mdd.lib  übersetzt mit Compileroption /MDd (Debugversion)
//             axctl_mtr.lib  übersetzt mit Compileroption /MT  (Releaseversion)
//             
//             in das Projekt eingebunden werden. Diese Datei enthält die
//             entsprechenden Prototypen. Eine DLL ist somit nicht
//             notwendig
//
//             Auf die Funktionen der Schnittstelle kann auch mit 
//             Loadlibrary und GetProcAdress über 
//             die DLL axctl.dll zugegriffen werden,
//             ohne die Libraries hinzubinden zu müssen
//             Hierzu sind entsprechende Funktionstypen am Ende
//             dieser Datei definiert. Somit ist es auch möglich
//             die Schnittstelle über z.B. Delphi zu bedienen. 
//
//             Die Fehlercodes, die die einzelnen Funktionen zurückliefern
//             sind in der Datei axctlerror.h definiert und beschrieben.
//
//
//  Version  : 1.0.0.1 vom 21.06.2002 Erstellung
//             1.0.0.2 vom 16.07.2002 Umstellung von 
//                                    HAXIS als void * auf HAXIS als DWORD
//                                    bzw. HAXIS ist jetzt Nummer der Achse
//                                    Export von AXCTL_AX nicht mehr notwendig
//                                    Einführung Synchronisation der Achsen
//                                    (axctl_Synchronize)
//                                    dwSize für Strukturen eingeführt
//                                    betrifft Funktionen axctl_GetConfiguration,
//                                    axctl_GetAxisConfiguration, axctl_GetStatus
//                                    Steuerung über die serielle Schnittstelle
//                                    möglich
//                                    axctl_GetActVelocity wird über SDO abgefragt
//                                    deshalb diese Funktion nicht zu oft aufrufen
//                                    Nur ein PDO für Statusabfrage und 
//                                    Positionsabfrage der Module
//                                    Änderung der Struktur AXCTLAXISCONFIG
//                                       
//             1.0.0.3 vom 08.08.2002 Bereitstellung von Funktionen, um über
//                                    ProNC mittels der Funktion UserDll die 
//                                    Schnittstelle aufrufen zu können 
//                                    Neue Funktion axctl_ReferenceActPos
//
//             1.0.0.4 vom 22.08.2002 Achsen und CNC-Überwachungssystem eingeführt
//                                    
//             1.0.0.5 vom 28.08.2002 In CAxis::CAxis wurde m_lTimeout nicht initialisiert
//                                    m_lTimeout =50000; wurde dementsprechend ergaenzt
//
//             1.0.0.6 vom 29.08.2002 Timeout für SDOs auf 100 ms als Defaultwert gesetzt
//                                    wegen Anpassung an Windows XP (Laufzeit der PDO ist länger)
//                                    Timeoutzeit kann in INI-Datei konfiguriert werden
//                                    [HandlingAxis] SDOTimeout (in µs)
//
//             1.0.0.7 vom 03.09.2002 Fehler in axctl_Exit() verbessert
//                                    PDO wurden zu früh freigegeben
//                                    Deswegen schlug die Funktion WaitForStatus
//                                    fehl
//                                    Verschieden Teststatement zur Überwachung
//                                    der PDO und SDO-Übertragung
//                                    
//             1.0.0.8 vom 04.08.2002 Herausnahme der SDO-Schnittstelle
//                                    in eine eigene Lib
//                                    
//             1.0.0.9 vom 10.09.2002 Sleep in axctl_WaitForStatus eingebaut
//                                    (Betrifft intern WaitForStatus und WaitForEvent)
//                                    (Status wird über PDO abgefragt. Diese sind nicht
//                                     immer aktuell, deswegen der Einbau der Zeitverzögerung)     
//                                    
//                                    
//             1.0.0.10 vom 07.10.2002 axctl_UVersion eingeführt
//                                    
//             1        vom 21.10.2002 Anpassung an Versionnummer von ProNC
//
//             2        vom 03.02.2003 Einführung der Funktion axctl_SetOperationMode
//                                     Mit dieser Funktion kann der Operationsmodus 
//                                     gewechselt werden
//                                                 
//
//             1.53.0.2 vom 14.08.2008 Fehler in axctl_GetAxisconfiguration verbessert.
//                                     Rotate with max Acceleration eingebaut.
//                                    
//                                    
//                                    
//
//
//  Created  : 01.07.2002 Frank Steinmetz (isel automation KG)
//
//

#ifndef __AXCTL_H_INCLUDED
#define __AXCTL_H_INCLUDED

// Aktuelle Versionsnummer der Schnittstelle
#define AXCTL_VERSION_NUMBER 2
#define AXCTL_VERSION_NUMBER_STR "2"

#ifdef AXCTL_IMPORT
#define AXCTL_DLL __declspec(dllimport) _stdcall
#define AXCTL_DLL_EXP __declspec(dllimport)
#endif

#ifndef AXCTL_DLL
#define AXCTL_DLL
#define AXCTL_DLL_EXP
#endif

#include "windows.h"


// Definierte Ereignisse für die Funktion axctl_WaitForEvent
#define AXCTL_EVENT_POSREACHED   1 // Achse hat Position erreicht
#define AXCTL_EVENT_VELREACHED   2 // Geschwindigkeit erreicht (bei Drehzahlregelung)
#define AXCTL_EVENT_VELNULL      3 // Geschwindigkeit = 0 (bei Drehzahlregelung)

// Konstanten für die Funktion axctl_WaitForEvent
#define AXCTL_TIMEOUT_INFINITY   -1  // Konstante für Unendliches Warten für Variable lTimeout
#define AXCTL_STANDARD_TIMEOUT   500 // in ms   Variable lTimeout
#define AXCTL_STANDARD_SLEEPTIME 50  // in ms   Variable lSleeptime


// Konstanten für die Funktion axctl_GetConfiguration
// Type der Achse
#define AXCTL_TYPE_LINEAR       0 // Linearachse
#define AXCTL_TYPE_ROTATION     1 // Rotationsachse

// Operationsmodus (Einstellbar über CANSet)
// Wird in der Funktion axctl_GetConfiguration übergeben
#define AXCTL_OPM_PROFILEPOSITION 1 // Positionierung
#define AXCTL_OPM_PROFILEVELOCITY 3 // Drehzahlregelung

// Macro für Abfrage ob Funktion erfolgreich
// Beispiel:
// if (AXCTLOK(axctl_Reference(hAxis))) {OK} else {Fehler};
//
#define AXCTLOK(x) ((x & 0xFFFF) == AXCTL_SUCCESS)

// Struktur für die Funktion axctl_GetStatus 
// (Abfrage des Status der Achse)
// Die Bedeutung der einzelne Flags sind im folgenden
// beschrieben
typedef struct tagAXCTLAXISSTATUS
{

BOOL fIsBusy;              // Endstufe bearbeitet Befehl und ist beschäftigt 
                           // oder die SDO bzw. PDO-Kommunikation nicht möglich
                           // (Status kann nicht festgestellt werden)
                           // Ist die Variable fIsBusy gesetzt, so sind alle folgenden
                           // Variable ungültig bzw. im undefinierten Zustand  

BOOL fHardwareFail;        // Allgemeiner Fehler in der Endstufe 
                           // nicht näher spezifiziert  ErrorRegister (Bit 0)
                           // alle folgenden Variablen befinden 
                           // sich im undefinierten Zustand

BOOL fCommunicationFail;   // Kommunikationsfehler mit der Endstufe 
                           // ErrorRegister (Bit 4)
                           // Alle folgenden Variable befinden sich im
                           // undefinierten Zustand

BOOL fPowerFail;           // Hauptspannungsversorgung (70 V Spannung) fehlt 
                           // oder fehlerhaft
                           // oder Endstufe nicht freigegeben
                           // (Freigabesignal Eingang 4) 
                           // Ausgewertet werden 
                           // Status Bit 8 und Bit 4 
                           // ErrorRegister Bit 1 und Bit 2

BOOL fCurrentLimiter;      // Strombegrenzung in der Endstufe aktiv

// Endschalter
BOOL fHWLSNegActive;       // Negativer Endschalter aktiv
BOOL fHWLSPosActive;       // Positiver Endschalter aktiv

BOOL fHWLSDuringMotion;    // Mindestens ein Hardwareschalter wurde während der Bewegung aktiv
                           // entspricht im Moment fHWLSNegActive oder fHWLSPosActive aktiv

// Zustände der Endstufe (Statemachine)
BOOL fSwitchOnDisabled;    // Initialisierung abgeschlossen, Endstufe gesperrt, Antriebsfunktion gesperrt
BOOL fReadyToSwitchOn;     // Endstufe gesperrt, Antriebsfunktion gesperrt
BOOL fSwitchedOn;          // Endstufe freigegeben, Antriebsfunktion gesperrt
BOOL fOperationEnable;     // Endstufe freigegeben, Antriebsfunktion freigegeben. Motor ist bestromt
BOOL fFault;               // Endstufe im Fehlerzustand
BOOL fFaultReactionActive; // Fehlerreaktion aktiv es wird automatisch in den Zustand Fault (fFault) 
                           // gewechselt

BOOL fNeedReferenceRun;    // Referenzfahrt der Achse nötig
   

BOOL fInMotion;            // Bewegung aktiv 
BOOL fInStopMode;          // Bewegung wurde angehalten (fInMotion and not fIsMoving)
BOOL fIsMoving;            // Achse bewegt sich physikalisch

BOOL fPositionLagError;    // Nachlauffehler aufgetreten

} AXCTLAXISSTATUS, *LPAXCTLAXISSTATUS;


typedef struct tagAXCTLAXISCONFIG 
{
   BOOL fInUse;    // Achse wird verwendet
                   // Wird die Achse nicht verwendet, so sind byType und cOPMode undefiniert
   BYTE byType;    // Type der Achse (siehe AXCTL_TYPE_... -Konstanten)
   CHAR cOPMode;   // Operationsmodus der Achse (siehe AXCTL_OPM_...-Konstanten)
} AXCTLAXISCONFIG, *LPAXCTLAXISCONFIG;

typedef struct tagAXCTLCONFIG 
{
   DWORD dwAbility;         // Reserviert
   DWORD dwMaxHandlingAxis; // Maximale Anzahl von unterstützen Handlingachsen
   DWORD dwNumHandlingAxis; // Verfügbare Anzahl von (konfigurierten) Handlingachsen
} AXCTLCONFIG, *LPAXCTLCONFIG;

// Definition Handle auf eine Achse (Nummer der Achse)
typedef DWORD HAXIS;

//
// Definition der Konstanten für Handlingachsen
// Die Anzahl der unterstützen Handlingachsen 
// kann mit axctl_GetConfiguration abgefragt werden
//
#define AX_1 1
#define AX_2 2
#define AX_3 3
#define AX_4 4
#define AX_5 5
#define AX_6 6

DWORD AXCTL_DLL axctl_Initialize(char *cfile);
//
// Initialisieren der Schnittstelle
//
// char *cfile Initialisierungsdatei der Schnittstelle
//
// Voraussetzung zur Initialisierung der Schnittstelle
// ist die Initialisierung des CAN-Bus mit
// cpctl_Initialize oder mctl_Initialize.
// In CANSet können die Achsen AX_1 bis AX_6
// konfiguriert werden 
// (Steuerung konfigurieren->
//  Koordinaten und Achsen->
//  Handlingachsen 1. Achse (AX_1), ... 6. Achse (AX_6)).
// Die Initialisierungsdatei cfile für 
// axctl_Initialize ist die selbe wie für
// cpctl_Initialize bzw. mctl_Initialize
// Für die Verwendung der Funktion axctl_Synchronize ist
// die Funktion mctl_Initialize notwendig. Desweiteren 
// muss danach mctl_Reset durchgeführt werden.
// 
// Die Initialisierungsdatei muss folgende Einträge enthalten
// mit dem die Handlingachsen konfiguriert werden:
// 
// [HandlingAxis]
//
// Inhibittime = 25000 ; (int) Zeit zwischen zwei PDOs bei den Handlingachsen in µs
// AxisNo = 1 ; (int) Anzahl der Handling-Achsen der Anlage
//
// ; Handlingachse Nummer 1
// Serial1 = false ; (bool) (false) Anschluss an CAN-Bus, (true) Anschluss an serielle Schnittstelle 
// Baudrate1 = 57600 ; (int) Baudrate für die serielle Schnittstelle
// CanNodeNo1 = 4 ; (int) Can Knoten Nummer oder Port für serielle Schnittstelle
// OPMode1 = 1 ; (int) Operationsmodus: 0 = Positionierung, 1 = Drehzahlregelung
//
// ; Handlingachse Nummer 2 usw. ...

DWORD AXCTL_DLL axctl_Setup();
//
// Setup der Einachsensteuerung
//
// Es wird auf CANSet verwiesen
//
 
DWORD AXCTL_DLL axctl_Diagnosis();
//
// Diagnose der Einachsensteuerung
//
// Es wird auf CANSet verwiesen
//

DWORD AXCTL_DLL axctl_Version();
//
// Zeigt Versionsinformation in einen Dialog an.
//

DWORD AXCTL_DLL axctl_SetOperationMode(HAXIS hAxis, CHAR cOperatiomMode);
//
// Setzt den Operationsmodus der Achse
//
// Nach Ausführung des Befehls ist ein Reset der Achse notwendig
//
// 
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
//
// DWORD dwOperatiomMode Operationmodus der Achse
//
//                    Geben Sie hier folgende Konstanten an:
//
//                    AXCTL_OPM_PROFILEPOSITION Positionierung der Achse
//                    AXCTL_OPM_PROFILEVELOCITY Drehzahlregelung der Achse
//


DWORD AXCTL_DLL axctl_Reset(HAXIS hAxis);
//
// Reset der Achse
// Notwendig im Fehlerfall bzw. nach der Initialisierung
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_GetConfiguration(
   LPAXCTLCONFIG pConfiguration, DWORD dwSize);
//
// Bestimmen der Konfiguration Handlingachsensteuerung
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
// LPAXCTLCONFIG  pAxisConfiguration Zeiger auf Konfigurationsstruktur
//                                         Siehe Struktur AXCTLCONFIG
//
//

DWORD AXCTL_DLL axctl_GetAxisConfiguration(
   HAXIS hAxis, LPAXCTLAXISCONFIG pAxisConfiguration, DWORD dwSize);
//
// Bestimmen der Konfiguration der Achse
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
// LPAXCTLAXISCONFIG  pAxisConfiguration Zeiger auf Konfigurationsstruktur
//                                         Siehe Struktur AXCTLAXISCONFIG
//

DWORD AXCTL_DLL axctl_Reference(HAXIS hAxis);
//
// Referencefahrt der Achse
// Die Funktion wartet, bis die Referencefahrt abgeschlossen ist.
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_ReferenceActPos(HAXIS hAxis);
//
// Referencefahrt der Achse zum aktuellen Position
// der Achse. Die Achse bewegt sich deshalb nicht
// Die Funktion wartet, bis die Referencefahrt abgeschlossen ist.
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_SetVelocity(HAXIS hAxis, DWORD dwVelocity);
//
// Setzen der Geschwindigkeit für die 
// Funktionen axctl_MoveAbs, axctl_MoveRel, axctl_Rotate
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
// DWORD dwVelocity   Geschwindigkeit der Achse in 
//                    µm/s (Linearbewegung) bzw. 
//                    ''/s (Rotationsbewegung)

DWORD AXCTL_DLL axctl_GetVelocity(HAXIS hAxis, DWORD *pdwVelocity);
//
// Lesen der aktuelle eingestellten Geschwindigkeit 
// für die Funktionen axctl_MoveAbs, axctl_MoveRel, axctl_Rotate
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
// DWORD *pdwVelocity Rückgabe Geschwindigkeit der Achse in 
//                    µm/s (Linearbewegung) bzw. 
//                    ''/s (Rotationsbewegung)

DWORD AXCTL_DLL axctl_GetActVelocity(HAXIS hAxis, long *plActVelocity);
//
// Bestimmen der aktuellen Geschwindigkeit der Achse
//
// Das Bestimmen der aktuellen Geschwindigkeit erfolgt über
// eine SDO-Abfrage. Deshalb diese Funktion nicht zu häufig
// aufrufen.
//
// HAXIS hAxis        Handle der Achse (AX_1, ...) 
//                    entspricht Nummer der Handlingachse
// DWORD *plVelocity  Rückgabe Geschwindigkeit der Achse in 
//                    µm/s (Linearbewegung) bzw. 
//                    ''/s (Rotationsbewegung)
//                    Die Geschwindigkeit ist vorzeichenbehaftet
//                    und gibt die Richtung der Bewegung an.
//

DWORD AXCTL_DLL axctl_SetAcceleration(HAXIS hAxis, DWORD dwAcceleration);
//
// Setzen der Beschleunigung
// für die Funktion axctl_Rotate
//
// HAXIS hAxis          Handle der Achse (AX_1, ...) 
//                      entspricht Nummer der Handlingachse
// DWORD dwAcceleration Beschleinigung der Achse in 
//                      ''/(s^2)

DWORD AXCTL_DLL axctl_GetAcceleration(HAXIS hAxis, DWORD *pdwAcceleration);
//
// Lesen der Beschleunigung
// für die Funktion axctl_Rotate
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// DWORD *pdwAcceleration Rückgabe Beschleunigung der Achse in 
//                        ''/(s^2)

// Funktionen zum Setzen und Bestimmen eines Achsennullpunktes
// Betrifft die Funktion axctl_MoveAbs
// Nach Initialisierung entspricht der Koordinatennullpunkt
// dem Maschinennullpunkt.

DWORD AXCTL_DLL axctl_SetZeroPointAbs(HAXIS hAxis, long lpoint);
//
// Setzen des Koordinatennullpunktes bezogen auf den Maschinennullpunkt
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long lpoint            absoluter Koordinatennullpunkt bzgl. 
//                        Maschinennullpunkt
//

DWORD AXCTL_DLL axctl_SetZeroPointRel(HAXIS hAxis, long lpoint);
//
// Setzen des Koordinatennullpunktes relativ zu dem 
// aktuell gesetzten Koordinatennullpunkt
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long lpoint            absoluter Koordinatennullpunkt bzgl. 
//                        Maschinennullpunkt
//

DWORD AXCTL_DLL axctl_SetActPosZeroPoint(HAXIS hAxis);
//
// Setzen des Koordinatennullpunktes auf den
// Punkt auf dem die Achse gerade steht 
//
// HAXIS hAxis            Handle der Achse (AX_1, ...)
//                        entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_GetZeroPoint(HAXIS hAxis, long *plpoint);
//
// Lesen des aktuell gesetzten Koordinatennullpunkt
//
// HAXIS hAxis            Handle der Achse (AX_1, ...)
//                        entspricht Nummer der Handlingachse
// long *plpoint          Rückgabe Koordinatennullpunkt bzgl. 
//                        Maschinennullpunkt
//

DWORD AXCTL_DLL axctl_MoveAbs(HAXIS hAxis, long lpos);
//
// Absolute Bewegung bzgl. des Koordinatennullpunktes der Achse
// Die Funktion kehrt sofort zurück
//
// Der Nullpunkt der Achse kann mit den Funktionen
// axctl_SetZeroPointAbs, axctl_SetZeroPointRel, 
// axctl_SetActPosZeroPoint, axctl_GetZeroPoint
// gesetzt bzw. bestimmt werden.
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long lpos              Absolute Zielpostion in µm bzw. '' der Achse
//                        

DWORD AXCTL_DLL axctl_MoveRel(HAXIS hAxis, long lpos);
//
// Relative Bewegung bzgl. der aktuellen Position der Achse
// Die Funktion kehrt sofort zurück
// Mit der Funktion axctl_WaitForEvent kann auf das 
// Erreichen der Position gewartet werden
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long lpos              Absolute Zielpostion in µm bzw. '' der Achse
//

// Drehzahlregelung der Achse
DWORD AXCTL_DLL axctl_Rotate(HAXIS hAxis, long lvelocity);
//
// Drehbewegung der Achse
// Die Funktion kehrt sofort zurück
// Mit der Funktion axctl_WaitForEvent kann auf das 
// Erreichen der Geschwindigkeit gewartet werden
// Mit axctl_Abort bzw. axctl_Break kann die Rotation gestoppt werden
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long lvelocity         Geschwindigkeit der Rotationsbewegung in
//                        ''/s. Die Drehrichtung wird durch das 
//                        Vorzeichen der Geschwindigkeit festgelegt
//

// Drehzahlregelung der Achse
DWORD AXCTL_DLL axctl_RotateWMA(HAXIS hAxis, long lvelocity);
//
// Drehbewegung der Achse mit maximaler Beschleunigung (WMA with max. accelaration)
// Die Funktion kehrt sofort zurück
// Mit der Funktion axctl_WaitForEvent kann auf das 
// Erreichen der Geschwindigkeit gewartet werden
// Mit axctl_Abort bzw. axctl_Break kann die Rotation gestoppt werden
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long lvelocity         Geschwindigkeit der Rotationsbewegung in
//                        ''/s. Die Drehrichtung wird durch das 
//                        Vorzeichen der Geschwindigkeit festgelegt
//

DWORD AXCTL_DLL axctl_WaitForEvent(HAXIS hAxis, DWORD dwEvent, LONG lTimeout, LONG lSleeptime);
//
// Warten auf festdefiniertes Ereignis
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// DWORD dwEvent          Ereignis: Siehe AXCTL_EVENT_... Konstanten
// LONG lTimeout          Maximale Wartezeit auf das Ereignis
//                        Bei Angabe der Konstante AXCTL_TIMEOUT_INFINITY
//                        wird unendlich lang gewartet 
//                        (Achtung es können Endlosschleifen entstehen)
//                                                      
// LONG lSleeptime        Intervall, indem der Status der Achse abgefragt wird
//

DWORD AXCTL_DLL axctl_GetStatus(HAXIS hAxis, LPAXCTLAXISSTATUS pAxisStatus, DWORD dwSize);
//
// Abfrage des Status der Achse
//
// HAXIS hAxis                   Handle der Achse (AX_1, ...) 
//                               entspricht Nummer der Handlingachse
// LPAXCTLAXISSTATUS pAxisStatus Siehe Definition von AXCTLAXISSTATUS 
//

DWORD AXCTL_DLL axctl_GetPosition(HAXIS hAxis, long *plposition);
//
// Aktuelle physikalische Position der Achse
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long *plposition       Rückgabe aktuelle physikalische Position bzgl.
//                        der Koordinatenursprungs der Achse
//                        in µm bzw. ''
//

DWORD AXCTL_DLL axctl_GetDestinationPos(HAXIS hAxis, long *plposition);
//
// Zielposition der Achse, wie sie der Regler vorgibt
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
// long *plposition       Rückgabe Zielposition der Achse in µm bzw. ''
//                        der Koordinatenursprungs der Achse
//

DWORD AXCTL_DLL axctl_LeaveHWLS(HAXIS hAxis);
//
// Endschalter freifahren
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_Abort(HAXIS hAxis);
//
// Bewegung unterbrechen (Bewegungsvektor geht verloren)
// Der Modus Operation Enable bleibt erhalten
// Entsprechend kann auch eine Drehbewegung, die
// mit axctl_Rotate gestartet wurde, beendet werden.
// mit axctl_WaitForEvent kann auf die 
// Geschwindigkeit 0 gewartet werden.
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_Stop(HAXIS hAxis);
//
// Bewegung unterbrechen (Bewegungsvektor bleibt erhalten)
// mit axctl_Start kann die Bewegung wieder gestartet werden.
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_Break(HAXIS hAxis);
//
// Bewegung unterbrechen (Bewegungsvektor geht verloren)
// Die Achse wird in den Zustand SwitchOnDisable gefahren
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_Start(HAXIS hAxis);
//
// Eine Bewegung, die mit axctl_Stop 
// unterbrochen wurde kann mit diesem Befehl
// wieder gestartet werden
//
// HAXIS hAxis            Handle der Achse (AX_1, ...) 
//                        entspricht Nummer der Handlingachse
//

DWORD AXCTL_DLL axctl_Synchronize(HAXIS hAxis1, HAXIS hAxis2);
//
// Synchronization der Achse 1 und Achse 2
// 
// Diese Funktion befindet sich noch im Beta-Status
//
// Bevor die Achse 1 mit der Achse 2 synchronisiert werden kann
// muss für Achse 1 ein Reset durchgeführt werden.
//
// Nach Aufruf der Funktion wird die Achse 2 an die 
// Bewegung der Achse 1 gekoppelt.
// d.h. wird die Achse 1 bewegt, so wird die Achse 2 entsprechend
// mitbewegt. Auf die Achse 2 wird ein Reset durchgeführt 
// und die Achse 2 in den Interpolationmodus gefahren.
// Die Befehle axctl_MoveAbs und axctl_MoveRel sind deshalb ohne
// Wirkung. Gesteuert werden die beiden Achsen über die Funktionen
// der Achse 1.
// Nach erfolgreichen Ausführen der Funktion axctl_Synchronize 
// werden die Referenzpunkte der beiden Achsen auf deren 
// aktuelle Position gelegt.
// Nach Fehlerfall oder Reset oder Referenzfahrt 
// der Achsen wird die Verbindung der beiden Achsen aufgehoben.
// Beide Achsen müssen an den CAN-Bus angeschlossen sein.
//
// Schwingt die Achse 2 bei abrupten Geschwindigkeitsänderungen
// nach, so muss für die 1. Achse der Wert der
// maximale Geschwindigkeit und der Wert der maximale Beschleunigung
// kleiner gewählt werden (DCSetup)
//
// Für die Verwendung der Funktion axctl_Synchronize ist
// die Funktion mctl_Initialize notwendig. Desweiteren 
// muss danach mctl_Reset durchgeführt werden, da von der
// mctl-Schnittstelle das Synchronisationssignal erzeugt wird
//
// HAXIS hAxis1           Handle der Achse 1 (AX_1, ...)
//                        entspricht Nummer der Handlingachse
// HAXIS hAxis2           Handle der Achse 2 (AX_1, ...)
//                        entspricht Nummer der Handlingachse
//


DWORD AXCTL_DLL axctl_Exit();
//
// Deinitialisieren der Schnittstelle
//
// Um den CAN-Bus zu initialisieren ist es
// notwendig nach axctl_Exit die Funktion
// cpctl_Exit bzw. mctl_Exit aufzurufen


// Definition der Funktionen der DLL axctl.dll
// um über LoadLibrary und GetProcAddress auf die 
// DLL zugreifen zu können.
// Beispiel in Visual C++ 6.0 
//
typedef DWORD (_stdcall * AXCTL_INITIALIZE)(char *);
typedef DWORD (_stdcall * AXCTL_SETUP)();
typedef DWORD (_stdcall * AXCTL_DIAGNOSIS)();
typedef DWORD (_stdcall * AXCTL_VERSION)();
typedef DWORD (_stdcall * AXCTL_SETOPERATIONMODE)(HAXIS hAxis, CHAR cOperatiomMode);
typedef DWORD (_stdcall * AXCTL_RESET)(HAXIS);
typedef DWORD (_stdcall * AXCTL_GETCONFIGURATION)(LPAXCTLCONFIG, DWORD);
typedef DWORD (_stdcall * AXCTL_GETAXISCONFIGURATION)(HAXIS, LPAXCTLAXISCONFIG, DWORD);
typedef DWORD (_stdcall * AXCTL_REFERENCE)(HAXIS);
typedef DWORD (_stdcall * AXCTL_REFERENCEACTPOS)(HAXIS);
typedef DWORD (_stdcall * AXCTL_SETVELOCITY)(HAXIS, DWORD);
typedef DWORD (_stdcall * AXCTL_GETVELOCITY)(HAXIS, DWORD *);
typedef DWORD (_stdcall * AXCTL_GETACTVELOCITY)(HAXIS, long *);
typedef DWORD (_stdcall * AXCTL_SETACCELERATION)(HAXIS, DWORD);
typedef DWORD (_stdcall * AXCTL_GETACCELERATION)(HAXIS, DWORD *);
typedef DWORD (_stdcall * AXCTL_SETZEROPOINTABS)(HAXIS, long);
typedef DWORD (_stdcall * AXCTL_SETZEROPOINTREL)(HAXIS, long);
typedef DWORD (_stdcall * AXCTL_SETACTPOSZEROPOINT)(HAXIS);
typedef DWORD (_stdcall * AXCTL_GETZEROPOINT)(HAXIS, long *);
typedef DWORD (_stdcall * AXCTL_MOVEABS)(HAXIS, long);
typedef DWORD (_stdcall * AXCTL_MOVEREL)(HAXIS, long);
typedef DWORD (_stdcall * AXCTL_ROTATE)(HAXIS, long);
typedef DWORD (_stdcall * AXCTL_ROTATEWMA)(HAXIS, long);
typedef DWORD (_stdcall * AXCTL_WAITFOREVENT)(HAXIS, DWORD, LONG, LONG);
typedef DWORD (_stdcall * AXCTL_GETSTATUS)(HAXIS, LPAXCTLAXISSTATUS, DWORD);
typedef DWORD (_stdcall * AXCTL_GETPOSITION)(HAXIS, long *);
typedef DWORD (_stdcall * AXCTL_GETDESTINATIONPOS)(HAXIS, long *);
typedef DWORD (_stdcall * AXCTL_LEAVEHWLS)(HAXIS);
typedef DWORD (_stdcall * AXCTL_ABORT)(HAXIS);
typedef DWORD (_stdcall * AXCTL_STOP)(HAXIS);
typedef DWORD (_stdcall * AXCTL_BREAK)(HAXIS);
typedef DWORD (_stdcall * AXCTL_START)(HAXIS);
typedef DWORD (_stdcall * AXCTL_SYNCHRONIZE)(HAXIS, HAXIS);
typedef DWORD (_stdcall * AXCTL_EXIT)();

#endif
