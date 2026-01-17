/**
 * \addtogroup Praktikumsdokumente
 *
 * @{
 *
 * @file app_tasks.c
 *
 * Enthaelt die Tasks und Routinen zur Realisierung des Projektes
 *
 *
 * @date 04.04.2010
 * @author Jan Rothkegel
 * modified by JH, 11/08/29
 * modified by RB, 11/09/15
 * modified by RB, 12/08/02
 * modified by JH, 12/08/27
 * modified by JH, 12/09/21  Projekt-Struktur-Optimierung
 * modified by JH, 12/09/25  Projekt-Struktur-Optimierung
 * modified by JH, 20/01/15  Reglertask entspr. Franke-RT angepasst
 * modified by JH, 22/08/17  CommutationControlEx() optimiert
 * modified by JH, 22/08/23  LCD-Refresh im EXEC_MODE 2 geaendert.
 * modified by JH, 22/08/24	 UART-Service mit Ringpuffern und INT-Mode
 * modified by JH, 24/07/17  Drehzahlproblem nach Taste 'select' behoben
 */

// standard includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <timer_e.h>
// scheduler includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
// application includes
#include "app_tasks.h"
#include "app_additional_funcs.h"
#include "hw_api.h"
#include "lcd_message.h"
// hardware includes
#include "hw_types.h"
#include "gpio.h"
#include "pwm.h"
#include "hw_memmap.h"
#include "adc.h"
#include "uart.h"
#include "sysctl.h"
#include "uartDrv.h"


#ifndef APP_TASKS_C_
#define APP_TASKS_C_

#define timerTIMER_1_COUNT_VALUE		( * ( ( unsigned long * ) ( TIMER1_BASE + 0x48 ) ) )

// Semaphores provided for process synchronisation
extern xSemaphoreHandle xSemaphore1;
extern xSemaphoreHandle xSemaphore2;


// global variable
volatile int CounterValue;		// Anzahl der HALL_Sensor_INT, in der Kommutierungssteuerung inkrem., in der Drehzahlreglung verwendet und genullt.
volatile long Speed;			// gemessene Drehzahl, Quelle: Kommutierungs-ISR   Senke: Drehzahlregler-Task
tBoolean controller_activ = true;	// PID-Regler ist aktiv, kann mittels Links/Rechts-Tasten EIN/AUS-geschaltet werden
tBoolean error_output_toggle;
extern long NominalSpeedWebInternal;	// located in uIP_Task.c
/* Schleifenanzahl in Tasks zur Simulation der Datenverarbeitung: 5000 or 1000 */
#define LOOPS 1000

/* Task Nr. 1 */
void vTask1( void *pvParameters )
{
	//Aufgabe 4.2
	/* OLED Message anlegen/initiieren*/
	xOLEDMessage xMessage;
	xMessage.x = 0;
	xMessage.y = 0;
	xMessage.pcMessage = (const char *) pvParameters;

	/* Verzögerungssschleife */
	for(volatile int i = 0; i < 5000 ; i++)
	{
				;
	}

	/* OLED Message an OLED Queue senden */
	xQueueSend( xOLEDQueue, ( void * ) &xMessage, ( portTickType ) 0 );
}

//Aufgabe 4.3

void vTask2(void *pvParameters)
{
	portTickType xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
    	//Aufgabe 4.4 - rest unten auskommentieren also for und taskDelay
    	xSemaphoreTake(xSemaphore2, portMAX_DELAY);
    	//Aufgabe 4.3
        for(volatile int i = 0; i < 1000; i++);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
    }
}

void vTask3(void *pvParameters)
{
	portTickType xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
    	//Aufgabe 4.4 - rest unten auskommentieren also for und taskDelay
    	xSemaphoreTake(xSemaphore2, portMAX_DELAY);
    	//Aufgabe 4.3
        for(volatile int i = 0; i < 1000; i++);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(15));
    }
}

void vTask4(void *pvParameters)
{
    while(1)
    {
    	// leer bis Aaufgabe 4.4
    	xSemaphoreGive(xSemaphore1);
    	for(volatile int i = 0; i < 10000; i++);

    	xSemaphoreGive(xSemaphore2);
    	for(volatile int i = 0; i < 10000; i++);

    }
}




/**
 * @brief
 *
 * Initialisieren der Queues
 *
 * In dieser Setup-Routine werden alle Queues des Systems initialisiert. Die Kapselung dient der Uebersichtlichkeit.
 *
 * @author Jan Rothkegel
 *
 */
void SetupProcessCommunication()
{
    // alle Queue's bis auf xOLEDQueue sind Ein_Element_Queue's
	xPulseWidthQueue = xQueueCreate(1,sizeof(long));		// Quelle: Task vSpeed_Control()	Senke: WEB-Interface
	xVoltageQueue = xQueueCreate(1,sizeof(long));			// Quelle: Task vVoltage_Supervisor()	Senken: WEB-Interface,vSpeed_Control()
	xSpeedQueue = xQueueCreate(1,sizeof(long));				// Quelle: Task vSpeed_Control()	Senke: WEB-Interface
	xNominalSpeedQueue = xQueueCreate(1,sizeof(long));		// Quelle: WEB-Interface,vVoltage_Supervisor  Senke: Task vSpeed_Control()
	xTimeConstantQueue = xQueueCreate(1,sizeof(long));		// Quelle: WEB-Interface			Senke: Task vSpeed_Control()
	// Queue fuer Anzeigedaten, fuer 20 Elemente zu je 25 Byte
	xOLEDQueue = xQueueCreate(20,25);					   	// Quellen: alle die etwas wissen	Senke: Task vOLEDTask()
}

/**
 * @brief
 *
 * Drehzahl-Regler
 *
 * Dieser Task realisiert einen digitalen Drehzahl-Regler.
 * dt=5ms, da ein Motor als PT1-Glied mit T=25ms zum Einsatz kommt.
 *
 * Er bereitet die vom Kommutierungs-INT-Handler gemessene Drehzahl als Eingangsgroesze auf,
 * prueft, ob vom WEB-Interface neue Sollwertvorgaben oder Zeitkonstantenaenderungen empfangen wurden,
 * bildet die Regeldifferenz und berechnet nach dem Geschwindigkeitsalgorithmus die neue Stellgroesze.
 * Zuletzt werden die Queue's fuer das Display und das WEB-Interface bedient.
 *													processing time ca. 60us
 * @author Jan Rothkegel
 * veraendert von J. Huhle
 */
void vSpeed_Control( void *pvParameters )
{
  #define dummy_const 1
	// Aufgabe 5.2
	  // const for PI_controller, Kp= 0.1,  Ti= 25ms, Ta=5ms
	//float Kp = dummy_const;		// Regler-Verstaerkung                  !!! vom Stud. zu ermitteln Aufgabe 3.2 Kp = 0.1
	float Kp = 0.1;		// Regler-Verstaerkung                  !!! vom Stud. zu ermitteln Aufgabe 3.2 Kp = 0.1
	//long Ti = dummy_const;		// Zeitkonstante des Integrators in ms	!!! vom Stud. zu ermitteln
	long Ti = 25;		// Zeitkonstante des Integrators in ms	!!! vom Stud. zu ermitteln
	float b2;               	//      b2 = Kp*(1+(T/(2*Ti)))
	float b1;       			//      b1 = -Kp*(1-(T/(2*Ti)))
	float b0;   				//      b0 = 0
	long u_min = -1200;			// Tastverhaeltnis-Untergrenze fuer Stellgroesze in Promille-Werten 0..1000
	long u_max = 1200;			// Tastverhaeltnis-Obergrenze fuer Stellgroesze in Promille-Werten
	long b2_i,b1_i,b0_i;		// Integer-Koeffizienten fuer schnellere Berechnung im Regler-Algorithmus
	int	 Ta = 5;				// Periode Digitalregler in ms
	long NominalSpeed = 0;		// Solldrehzahl
	long Speed2;				// IST-Drehzahl
	long ek = 0;				// aktuelle Regelabweichung, fuer Anzeige initialisiert.
	long ek1= 0,ek2= 0;			// Regelabweichungen der letzten beiden Abtastungen
	long uk = 0;				// aktuelle Stellgroesze, Tastverhaeltnis in Promille
	long uk_var;				// temp. Stellgroesze fuer Anzeige
	long ReceiveLong = 0;		// temporurer Speicher
	char buffer[12];			// fuer Ausgabe_String_Erzeugung
	int DisplayCounter = 0;		// nur fuer die Anzeige
//	long Voltage = 0;			// nur fuer die Anzeige
	portTickType xLastWakeTime;
	int i;

	xLastWakeTime = xTaskGetTickCount();

	// berechne die Regler-Koeffizienten fuer den PI-Regler
	b2 =  Kp*(1.0 + (Ta/(2.0 * Ti)));
	b1 = -Kp*(1.0 -(Ta/(2.0 * Ti)));
	b0 = 0.0;								// bei PI-Regler immer NULL

	//... berechne die Koeffizienten fuer einen INTEGER_PID_Algorithmus
	b2_i = b2 * 65536.0;	// Wir transformieren in den Ganzzahlbereich und dividieren spaeter das Ergebnis.
	b1_i = b1 * 65536.0;
	b0_i = b0 * 65536.0;

    UARTSend("   Controller started\n\r", 23);

	for( ;; )
	{
		  // Die Drehzahlbestimmung aus Zaehlwerten der Kommutierung ist zu ungenau.
		  // Deshalb wird mit Pulsdauermessung (PDM) gearbeitet.
		  // Die PDM ist in der ISR der Kommutierung realisiert und liefert die globale Speed-Variable.
		  //  n = N_KommINT /12 * 60[s] / 10E-2[s]   changed by JH, DA S.53

		 Oszi_ON;									// added by JH for Test_OSZI_signal

		  if(CounterValue)  // Wenn es in den letzten 5ms Kommutierungen gab, dann verarbeite den Speed-Wert.
		  {
			Speed2 = Speed;  				// hole aktuellen Drehzahlwert als Eingabegruue des Reglers
											// Der Wert fuer Drehzahl (Speed) ist immer positiv.
			if(CounterValue < 0)			// bei Linksdrehung negative Speed2 fuer Regler erzeugen
		        Speed2 *= (-1);				// in Abhungigkeit CounterValue wird Vorzeichen der Drehzahl gebildet.

			CounterValue = 0;				// Zuruecksetzen der Zaehlvariable in der Kommutierungssteuerung

		  }else
		  {									// wenn es keine Kommutierungen gab, steht der Motor still.
			  Speed2 = 0;					// dann setze Speed zu NULL
		  }

		  // Pruefen, ob neuer Drehzahl-Sollwert vom WEB-Interface vorliegt
		  if (xQueueReceive( xNominalSpeedQueue, &ReceiveLong, 0))
		  {
				NominalSpeed = ReceiveLong;
				if(NominalSpeed<=-10000)						// Wertebereichsueberwachung
					NominalSpeed=-9999;		// begrenzen auf +- 3000 .... 9999
				if(NominalSpeed>=10000)
					NominalSpeed=9999;
				if((NominalSpeed<3000)&&(NominalSpeed>0))
					NominalSpeed=3000;
				if((NominalSpeed>-3000)&&(NominalSpeed<0))
					NominalSpeed=-3000;
				// Wenn NominalSpeed hier begrenzt wurde, wird sie fuer das WEB-Interface aktualisiert.
				//Aufgabe 5.4 hier Vorzeichen ändern
				NominalSpeedWebInternal = NominalSpeed;
		  }

		  // Pruefen, ob neue Zeitkonstante vom WEB-Interface vorliegt
		  if (xQueueReceive( xTimeConstantQueue, &ReceiveLong, 0))
		  {
				Ti = ReceiveLong;
				if((Ti<10)||(Ti>100))							// Wertebereichsueberwachung
					Ti=25;
				// Neuberechnung der Regler-Koeffizienten fuer den PI-Regler
				b2 =  Kp*(1.0 + (Ta/(2.0 * Ti)));
				b1 = -Kp*(1.0 -(Ta/(2.0 * Ti)));
				b0 = 0.0;										// bei PI-Regler immer NULL

				//... berechne die Koeffizienten fuer einen INTEGER_PID_Algorithmus
				b2_i = b2 * 65536.0;	// Wir transformieren in den Ganzzahlbereich und dividieren spaeter das Ergebnis.
				b1_i = b1 * 65536.0;
				b0_i = b0 * 65536.0;
		  }

		  // ***** hier PI-Regler vervollstaendigen  *****
		  if(controller_activ == true)							// links/rechts-Tasten koennen Regler ein/ausschalten
		  {
			//  ***** begin of PID_controller ***********
			 // Oszi_ON; 											// added by JH for Test_OSZI_signal
			  // Regeldifferenz bilden
			  ek = NominalSpeed - Speed2;						// vorzeichenbehaftet

			  // Rekursionsberechnung ausfuehren
              // z.Z. noch ungeregelt, default n ca. 6000 upm
			  uk = NominalSpeed / 10;							// Stellgroesze = 500 Promille, entspricht ca. 6000 upm (ungeregelt) @15V

			  // Sicheren Stillstand gewaehrleisten
			  if (NominalSpeed==0)
				uk=0;

			  // GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_0, 0); // INT_delay = 1,3us for INT-Alg., 6..9us for float
			  if(uk>u_max) uk=u_max;							// simple wind-up
			  if(uk<u_min) uk=u_min;							// begrenze bei 120% die Stellgroesze

			  hw_SetPulseWidth(uk);								// Stellglied aktualisieren

			  // save the current and the old values for the next cycle
			  ek2=ek1;
			  ek1=ek;
			  //  end of PID_controller

			 // Oszi_OFF;			// INT_delay = 18.5 us for INT-Alg.(-O3 us), 26us for float (-O3 16us)
		  }


		  // Sende fuenfmal pro Sekunde eine Aktualisierung der Drehzahl/Stellgroesze an das WEB-Interface
		  if (++DisplayCounter == 40)							// 0,2 Sek-Intervall   !!!
		  {
				DisplayCounter = 0;

				// Aktuelle gemittelte Drehzahl und Stellgroesze in Queue's schreiben
				xQueueChangeValue(xSpeedQueue, &Speed2);		// Ziel: WEB_interface
				uk_var=abs(uk)/10;								// Stellgroesze PWM-Verhaeltnis in Prozent umwandeln
				if (uk_var>100)									// Begrenzung des Tastverhaeltnisses
					uk_var=100;
				xQueueChangeValue(xPulseWidthQueue, &uk_var);   // Ziel: WEB_interface

				// LCD-Refresh wurde ausgelagert zum SuperVisor-Task
				// xQueuePeek( xVoltageQueue, &Voltage, 0 );		// Quelle: vVoltage_Supervisor() Ziel: WEB_interface
				// Der gemessene Spannungswert wird hier "abgezweigt" um ihn auf dem LCD anzuzeigen.
				//PrintStatus(Speed2, NominalSpeed, uk/10, Voltage);  // LCD mit neuen Werten versorgen
		  }

		  //  Die Regelabweichung kann zum Test oefter auf das LCD gesendet werden.
		  if(error_output_toggle)
		  {
			  buffer[0]=60;  // x_pos of cursor
			  buffer[1]=80;  // y_pos of cursor
			  //sprintf( &buffer[2], "%d    ", (int)ek);
			  itoa((int)ek, &buffer[2]);
			  i = strlen(buffer);
			  buffer[i++] = ' ';		// loesche den Rest der vorherigen Ausgabe
			  buffer[i++] = ' ';
			  buffer[i++] = ' ';
			  buffer[i] = 0;
			  xQueueSend( xOLEDQueue, &buffer, 0 );
		  }
		  Oszi_OFF;  // INT_delay = 45 .... 200 us

		  vTaskDelayUntil( &xLastWakeTime, ( Ta / portTICK_RATE_MS ) );   // 5ms : 1 [ms] = 5ms
	}	// end of for
}

/**
 * @brief
 *
 * Periodischer Task zur Spannungsmessung, Taster-Abfrage, UART-Console und Hochlaufsteuerung mit  T = 50ms
 *
 * Dieser Task misst periodisch die Motorbetriebsspannung, aktualisiert die Messwerte via Queues und
 * realisiert eine UART-Console mit einem einfachen Befehlsprozessor.
 * Zusaetzlich werden die Taster abgefragt. Wenn SELECT betaetigt wurde, dann startet die Drehzahlrampe.
 *
 * @author Jan Rothkegel
 * veraendert von J. Huhle
 */
void vVoltage_Supervisor( void *pvParameters )
{
#define Wref 892			// binaerer Referenzmesswert bei 15.0 V, mit Spannungsteiler = 0,18 ergibt das 2,7V; U_ref=3V --> 90% Aussteuerung
#define ramp_start	2500	// Hochlauframpe beginnt bei 2500upm
#define ramp_end	5000	// und endet bei 5000upm
#define ramp_incr	50		// mit dem Anstieg von 50upm/50ms

	static tBoolean STATE_Hochlauf = false;			// autonomer Motoranlauf ist bei 1 aktiv
	int T = 50;					// Periode dieses Task in ms
	long Um;						// Umgerechneter Messwert in Volt xx.y
	long unsigned Wm;				// binurer Messwert des ADC
//	long ReceiveVal;				// uber diese Variable kann der Task einen Parameter erhalten.
	long SpeedStartVal=ramp_start;	// Startwert der Drehzahlrampe
	long SpeedVal;
	char buffer[25];				// fuer LCD-Ausgabe-Strings
    unsigned long ulData, ulDelta;	// fuer Tasten-Abfrage
//    unsigned char cmdByte;			// UART input
	long Speed = 0;					// IST-Drehzahl vom vSpeed_Control-Task
	long uk_var = 0;				// Tastverhaeltnis vom vSpeed_Control-Task
	int i = 0;
	char Asterisk[] = {'/','-',0x5C,0x7C};	// 	Folge von "/ - \ |"
	int DisplayCounter = 0;		// nur fuer die Anzeige
#define MAXbuffSize 20
  unsigned char consolebuffer[MAXbuffSize];
  unsigned char buffsize;

    //*****************************************************************************
    // The debounced state of the five push buttons.  The bit positions correspond
    // to:
    //     0 - Up		unused
    //     1 - Down		unused
    //     2 - Left
    //     3 - Right
    //     4 - Select
    // ! Only three are used, because the BLDC_driver uses the Ports PE0 and PE1. !
    //*****************************************************************************
    unsigned char g_ucSwitches = 0x1f;		// alle Taster unbetutigt

	portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();
    UARTSend("   Supervisor started\n\r", 23);

	for( ;; )
	{
		// OSZI_ON;  //
		// Es wird die 15V-Betriebsspannung gemessen.
		// internal U_ref = 3V, 10Bit, --> 2.93 mV/Bit
		// Lesen vom ADC initiieren
		ADCProcessorTrigger(ADC_BASE, 0);

		// Warten bis Messwert vorliegt
		while(!ADCIntStatus(ADC_BASE, 0, false))
		{
		}

		// Messwert auslesen
		ADCSequenceDataGet( ADC_BASE, 0, &Wm );

		//Wm = 500;  // only for testing
		// Messwert in V generieren
		Um = (Wm * 150) / Wref;			// mit einer Kommastelle, 15 * 10

		/* Queue aktualisieren */
		xQueueChangeValue(xVoltageQueue, &Um);		// Ziel: Web-Interface, Task vSpeed_Control()

		// Sende fuenfmal pro Sekunde eine Aktualisierung an das Display
		if (++DisplayCounter == 4)							// 4 x 50ms = 0,2 Sek-Intervall   !!!
		{
			DisplayCounter = 0;

			// hier Queue's anzapfen um Werte auf LCD auszugeben
			xQueuePeek(xSpeedQueue, &Speed, 0);					// Quelle: vSpeed_Control-Task Ziel: WEB_interface
			xQueuePeek(xPulseWidthQueue, &uk_var, 0);			// Quelle: vSpeed_Control-Task Ziel: WEB_interface
			PrintStatus(Speed, NominalSpeedWebInternal, uk_var, Um);  // LCD mit neuen Werten versorgen
		}

		// Taster-Abfrage					 added by JH, poll the the SELECT-switch and left/right

		// Read the state of the push buttons.
		ulData = (GPIOPinRead(GPIO_PORTE_BASE, ( GPIO_PIN_2 | GPIO_PIN_3)) |
				              (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) << 3));

	    // Determine the switches that are at a different state than the 'debounced' state.
	    //
	    ulDelta = ulData ^ g_ucSwitches;
	    g_ucSwitches = ulData & 0x1f;	// store the current state for simple debounce

	    // See if the select button was just pressed.
	    if(ulDelta & 0x10)
	    {
	        //
	        // Set a flag to indicate that the select button was just pressed.
	        //
	    	STATE_Hochlauf = true;
			buffer[0]=0;  // x_pos of cursor
			buffer[1]=68;  // y_pos of cursor
			strcpy( &buffer[2], "    thanks           ");
			xQueueSend( xOLEDQueue, &buffer, 0 );	// Start-Kommentar loeschen
	    }
	    // See if the right button was just pressed.
	    if(ulDelta & 0x08)
	    {
	    	controller_activ = false;				// Drehzahlregler wird deaktiviert
	    }
	    // See if the left button was just pressed.
	    if(ulDelta & 0x04)
	    {
	    	controller_activ = true;				// Drehzahlregler wird aktiviert
	    }
	    // Ende der Tastenabfrage

	    // hier wird die Drehzahl-Rampe realisiert.
		if(STATE_Hochlauf == true)					// bei aktiven Hochlauf, Hochlauframpe generieren
		{
			// Senden des Sollwertes an Drehzahlregler
			xQueueSend( xNominalSpeedQueue, &SpeedStartVal, 0);
			SpeedStartVal+=ramp_incr;				// Hochlauframpe beginnt bei 3000upm mit 50upm Inkrementen, Dauer = 4s
			if(SpeedStartVal >= ramp_end+ramp_incr)
			{
				SpeedStartVal = ramp_start;			// fuer den naechsten Hochlauf
				STATE_Hochlauf = false;				// Rampe bei 7000 beenden
				buffer[0]=0;  // x_pos of cursor
				buffer[1]=68;  // y_pos of cursor
				strcpy( &buffer[2], "          ");
				xQueueSend( xOLEDQueue, &buffer, 0 );  // Start-Kommentar loeschen
			}
		}

		// poll the UART_input_queue and when more than 2 characters are received, then echo these
		buffsize = SerialReceiveAvailable();
		if(buffsize >= 2)
		{
			if(buffsize > MAXbuffSize)
				buffsize = MAXbuffSize;
			UARTReceive(consolebuffer, buffsize);
			UARTSend(consolebuffer, buffsize);		// echo the last characters
			if(consolebuffer[0] == 's')				// starte Motorhochlauf
			{
	    		STATE_Hochlauf = true;
				buffer[0]=0;  // x_pos of cursor
				buffer[1]=68;  // y_pos of cursor
				strcpy( &buffer[2], "    thanks           ");
				xQueueSend( xOLEDQueue, &buffer, 0 );	// Start-Kommentar loeschen
			}else if(consolebuffer[0] == 'h')   	// stoppe Motor
			{
				hw_SetPulseWidth(0);
				SpeedVal = 0;
				xQueueSend( xNominalSpeedQueue, &SpeedVal, 0);
			}else if(consolebuffer[0] == 'e')		// error_output_toggle
				error_output_toggle = !error_output_toggle;
			else if(consolebuffer[0] == 'm')		// gibt Befehlsvorrat aus
			{
			    UARTSend("\n\r --- Befehlsliste ---\n\r",25);
			    UARTSend(" s starte Hochlauf\n\r",20);
			    UARTSend(" h halte Motor an\n\r",19);
			    UARTSend(" e schalte Fehlerausgabe um\n\r",29);
			}
		}

		// ein drehendes Kreuz wird auf dem LCD erzeugt
		buffer[0]=150;				// x_pos of cursor
		buffer[1]=120;				// y_pos of cursor
		buffer[2] = Asterisk[i++];	// one element of Asterisk
		buffer[3] = 0;				// NULL terminated for string
		i &= 3;						// limit the Asterisk_index
		xQueueSend( xOLEDQueue, &buffer, 0 );

		// OSZI_OFF;  // INT_delay = 45 .... 200 us

		/* Warten bis 50ms um sind oder neue Nachricht eingeht */
		vTaskDelayUntil( &xLastWakeTime, ( T / portTICK_RATE_MS ) );   // 5ms : 1 [ms] = 5ms
	}
}

/**
 * @fn void CommutationControl( )
 *
 * @brief
 *
 * Behandlungsroutine fuer Interrupts der Hall-Sensoreingaenge
 *
 * Es wird CommutationControlEx(0) aufgerufen und damit der Kommutierungsvorgang eingeleitet.
 * Auszerdem erfolgt mittels Pulsdauermessung (Timer1_ticks) die Drehzahlmessung.
 *														processing time ca. 35us
 * @author Jan Rothkegel, J. Huhle
 *
 */
void CommutationControl(void)
{
	// Sicherungsvariable fuer Ausgabe am Oszilloskop
	long Backup_PulseWidth;
	static unsigned portLONG ulLastCount;	// Timer_1_Zuhlerstand der letzten Abtastung, fuer Drehzahlmessung
	unsigned portLONG ulDifference;
	unsigned portLONG ulCurrentCount;
	static unsigned portLONG period_average = 0;
	static unsigned portLONG average_count = 0;
	long speed_temp;			// long, temporure Drehzahl
//	char buffer[12];
//	static long ToggleOszi ;	// by JH for OSZI_signal
//	static unsigned portLONG z_array[50],i=0;

	//  Oszi_ON; 											// added by JH for Test_OSZI_signal

	// We use the timer_1 counter value to measure the clock cycles between the commutation-interrupts.
	ulCurrentCount = timerTIMER_1_COUNT_VALUE;

	// Sichern der Pulsweite am Oszilloskop-Ausgang
	Backup_PulseWidth = PWMPulseWidthGet(PWM_BASE, PWM_OUT_0);

	// Am Oszilloskop anzeigen, dass Interrupt ausgefuehrt wird
	PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, 0);

	// Interruptflags der Hallsensor-Eingaenge zuruecksetzen
	GPIOPinIntClear(GPIO_PORTB_BASE, GPIO_PIN_4);
	GPIOPinIntClear(GPIO_PORTD_BASE, GPIO_PIN_4);
	GPIOPinIntClear(GPIO_PORTD_BASE, GPIO_PIN_7);

	// Aufrufen der eigentlichen Kommutierungsroutine
	CommutationControlEx(0);

	// Zeit zwischen den Kommutierungs-INT messen
		// How many times has Timer_1 counted since the last interrupt?
	ulDifference = 	ulLastCount - ulCurrentCount;   // ulDifference = Z , das sind Timer-ticks (@20ns)
	ulLastCount = ulCurrentCount;					// aktuellen Wert fuer die naechste Berechnung merken

	// convert to UPM for speed
	period_average+=ulDifference;					// Z zwoelfmal aufaddieren, da 12 Kommutierungen pro Umdrehung
	if(++average_count == 12)
	{							// Es sind 12 Kommutierungen vorbei, der Motor drehte eine Runde.
		  average_count=0;								// Kommutierungszaehler loeschen
		  speed_temp = 3000000000UL/period_average;		// Speed in UPM = 60 / (Z * 2 * 10E-8)  delay = 800ns
		  speed_temp = (speed_temp + 5) / 10;			// auf-ab-runden auf Zehner ...
		  Speed = speed_temp * 10;						// runden auf Zehner
		  period_average=0;								// Summe loeschen

		  /* send the value via queue to the display	only for debugging
		  buffer[0]=50;  // x_pos of cursor
		  buffer[1]=80;  // y_pos of cursor
		  sprintf( &buffer[2], "%d ", Speed);
		  xQueueSend( xOLEDQueue, &buffer, 0 );  */
	}
	// Wiederherstellung der Oszilloskopausgabe */
	PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, Backup_PulseWidth);

	// Oszi_OFF;  // INT_delay = 12 .. 13 us   -O3     oder 21.6 .. 26.8 -O0
}

/**
 * @brief
 *
 * Kommutierungssteuerung
 *
 * Routine, welche Rotorlage bestimmt und Phasenbestromung einstellt. Es handelt sich um eine Routine,
 * welcher bei jeder Zustandsaenderung der Hall-Sensoren als ISR  oder durch die Anlaufsteuerung aktiviert wird.
 *
 * @author Jan Rothkegel
 *
 * Kommutierungssequenz als Array befindet sich in der hw_api.h
 */
void
CommutationControlEx( long CommutationOffset )
{
	  static int StateBackup = 0;							// changed by JH
	  int i = 0;		// Laufvariable

	  // Oszi_ON; 											// added by JH for Test_OSZI_signal

		/* Einlesen der Hallsensor-Daten */
		HallA = (int) GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_4) / 16;
		HallB = (int) GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_4) / 16;
		HallC = (int) GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7) / 128;

		/* Abschalten, wenn unmoegliche Kombination von Signalen anliegt */
		if (HallA==HallB && HallB==HallC)
		{
			StopSystem();
		}

		/* Durchlaufen aller Eintraege der Kommutierungssequenz */
		for (i = 0; i < 6; i++)
		{
			/* Pruefen, ob Eintrag fuer aktuelle Rotorposition gilt */
			if ( CommutationSequence[i].HallA==HallA &&
				 CommutationSequence[i].HallB==HallB &&
				 CommutationSequence[i].HallC==HallC		)
			{
				/* Kommutierungsoffset-Behandlung ist nur relevant fuer Anlaufvorgang
				i = i + CommutationOffset;

				if (i>5)
					i=i-6;
				if (i<0)
					i=i+6;
				 	 	 	 wird offensichtlich nicht benoetigt */

				/* uebernehmen der Phasenbeschaltung laut Sequenz */
				hw_SetBridge(	CommutationSequence[i].Bridge1,
								CommutationSequence[i].Bridge2,
								CommutationSequence[i].Bridge3	);

				// zaehle die Kommutierungen, wird fuer den Drehzahlregler-Task benoetigt.
				//if ( CommutationOffset==0 )
				//{
					if (StateBackup > i || (StateBackup - i == (-5)))
					{
						/* Bei Linksdrehen dekrementieren */
						CounterValue++;						// changed by JH
					}
					else if (StateBackup < i || (StateBackup - i == (5)))
					{
						/* Bei Rechtsdrehen inkrementieren */
						CounterValue--;						// changed by JH
					}
				//}

				/* Sichern der Rotorposition */
				StateBackup = i;

				break;
			}
		}
		// Oszi_OFF;  // INT_delay = 8.7 .. 9.7 us  -O3
}
/**
 * @brief
 *
 * ISR bei Erkennung von Ueberbelastung
 *
 * In dieser Routine erfolgt das Abschalten des Geraetes bei Stroemen von mehr als 1,2A.
 *
 */
void CurrentDetection(void)
{
	char buffer[25];										// fuer LCD-Ausgabe-Strings
	unsigned portLONG ulStartCount;
	unsigned portLONG ulCurrentCount;
//#define timerTIMER_1_COUNT_VALUE		( * ( ( unsigned long * ) ( TIMER1_BASE + 0x48 ) ) )

	if (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4)==0)		// changed by JH, old: ==1   new: ==0
	                                 // 1->0 edge causes the INT, there is a transistor_inverter in the new_design
	{
		/* Deaktivieren der Interrupts */
		GPIOPinIntDisable(GPIO_PORTD_BASE, GPIO_PIN_4);
		GPIOPinIntDisable(GPIO_PORTD_BASE, GPIO_PIN_7);
		GPIOPinIntDisable(GPIO_PORTB_BASE, GPIO_PIN_4);

		/* Schaltbruecke hochohmig machen */
		hw_SetBridge( 0, 0, 0 );

		/* Nervigen Piepton generieren */
		unsigned long ulPeriod;

		GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

		ulPeriod = SysCtlClockGet() / 440;

		PWMGenConfigure(PWM_BASE, PWM_GEN_0,
						PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

		PWMGenPeriodSet(PWM_BASE, PWM_GEN_0, ulPeriod);

		PWMPulseWidthSet(PWM_BASE, PWM_OUT_1, ulPeriod * 2 / 4);

		PWMOutputState(PWM_BASE, PWM_OUT_1_BIT, true);

		PWMGenEnable(PWM_BASE, PWM_GEN_0);

		// auf LCD Meldung ausgeben, das passiert erst nach dieser ISR
		  buffer[0]=0;  // x_pos of cursor
		  buffer[1]=68;  // y_pos of cursor
		  strcpy( &buffer[2], "overload, restart!");
		  xQueueSend( xOLEDQueue, &buffer, 0 );				// Start-Kommentar loeschen

		// wait a moment
		ulStartCount = timerTIMER_1_COUNT_VALUE;
		do
		{
			ulCurrentCount = timerTIMER_1_COUNT_VALUE;
		}while((ulCurrentCount+10000000)>ulStartCount);

		PWMOutputState(PWM_BASE, PWM_OUT_1_BIT, false);		// Piepton abschalten

		// System blockieren 				deaktiviert
//		for (;;) {};

	}

	GPIOPinIntClear(GPIO_PORTC_BASE, GPIO_PIN_4);			// mod. by JH
}

#endif /* APP_TASKS_C_ */

//! @}
