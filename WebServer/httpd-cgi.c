
/*
 *
 *         Web server script interface
 *
 *         Adam Dunkels <adam@sics.se>
 *
 */

/*
 * Copyright (c) 2001-2006, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: httpd-cgi.c,v 1.2 2006/06/11 21:46:37 adam Exp $
 *
 */

/**
 * \addtogroup Praktikumsdokumente
 *
 * @{
 *
 * @file httpd-cgi.c
 *
 * In dieser Datei werden dynamische Inhalte generiert.
 *
 * @date 04.04.2010
 * @author Adam Dunkels
 * @author Jan Rothkegel
 * @coauthor J. Huhle, 29.08.2011
 * modified by RB, 12/08/02
 * modified by JH, 12/09/11 	type_adaption in sprintf_fct
 * modified by JH, 18/05/22		alle printf() eliminiert, durch itoa()/usprintf() ersetzt
 * modified by JH, 23/02/02		WEB-UI angepasst, Tabelle besitzt jetzt eine Ueberschrift
 * modified by JH, 23/02/03		WEB-UI angepasst, Tabellenueberschrift in statische Webseite verlagert u.
 * 								input.shtml angepasst.
 */
#include "uip.h"
#include "psock.h"
#include "httpd.h"
#include "httpd-cgi.h"
#include "httpd-fs.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "app_tasks.h"
#include "app_additional_funcs.h"

#include "hw_memmap.h"
#include "hw_types.h"
#include "gpio.h"

extern int usprintf(char *pcBuf, const char *pcString, ...);
#define Oszi_ON 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 1);							// added by JH for Test_OSZI_signal
#define Oszi_OFF 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 0);							// added by JH for Test_OSZI_signal


/* Definition der Einsprungpunkte und zugehoerigen Routinen */
HTTPD_CGI_CALL(controlpage, "control-info", control_page );
HTTPD_CGI_CALL(inputfield, "input-field", input_field );

/* Zusammenfassung der Einsprungpunkte als Liste */
static const struct httpd_cgi_call *calls[] = { &controlpage, &inputfield, NULL };

/*---------------------------------------------------------------------------*/
static
PT_THREAD(nullfunction(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
httpd_cgifunction
httpd_cgi(char *name)
{
  const struct httpd_cgi_call **f;

  /* Find the matching name in the table, return the function. */
  for(f = calls; *f != NULL; ++f) {
    if(strncmp((*f)->name, name, strlen((*f)->name)) == 0) {
      return (*f)->function;
    }
  }
  return nullfunction;
}

/*---------------------------------------------------------------------------*/

/**
 * @brief
 *
 * In dieser Routine werden dynamische HTML-Inhalte fuer die Anzeige der Prozessgroeszen erstellt.
 *
 */

static unsigned short
generate_control_page(void *arg)
{
	char Speed[8]="0";					// Anzeigetext Drehzahl
	char NominalSpeed[8];				// Anzeigetext Solldrehzahl
	char Voltage[8]="0";				// Anzeigetext Betriebsspannung
	char PWM[5]="0";					// Anzeigetext Tastverhaeltnis
	char RelativePWM[5]="0";			//
	char RelativeSpeed[8]="0";			// Parameter fuer Balkengrafik
	char RelativeNominalSpeed[8]="0";	//
	long lSpeed = 0;					// Drehzahl
//	long lNominalSpeed = 0;				// Solldrehzahl
	long lVoltage = 0;					// Betriebsspannung multipliziert mit Faktor 10
	long lPWM = 0;						// Tastverhaeltnis PWM in Prozent
	long lRelativePWM = 0;				//
	long lRelativeSpeed = 0;			// Parameter fuer Balkengrafik
	long lRelativeNominalSpeed = 0;		//
	char ResultingDoc[430];				// Datenfeld mit HTML-Code, Groesze muss beim Anpassen der Tabelle beachtet werden.
	unsigned short length;

	Oszi_ON;			// delay ~500µs

	/* EINLESEN DER PROZESSDATEN
	 * Nutzen Sie hierfuer den Befehl xQueuePeek() und die Queues
	 * xSpeedQueue, xVoltageQueue und xPulseWidthQueue.
	 * Schreiben Sie die Daten in die Variablen
	 * lSpeed, lVoltage und lPWM. */

	/* Einlesen der Prozessdaten */
	//Aufgabe 5.3
	xQueuePeek(xSpeedQueue, &lSpeed, (portTickType)10);
	xQueuePeek(xVoltageQueue, &lVoltage, (portTickType)10);
	xQueuePeek(xPulseWidthQueue, &lPWM, (portTickType)10);

	extern long NominalSpeedWebInternal;


	/* BESCHRAENKUNG DES TASTVERHAELTNISSES
	 * Welche Einschraenkungen sind fuer lPWM sinnvoll?
	 * Setzen Sie diese um.
	 */

	//Aufgabe 5.3 - Negative oder über 100 % liegende Tastverhältnisse sind physikalisch nicht sinnvoll und würden die Webanzeige verfälschen.
	if (lPWM < 0)   lPWM = 0;
	if (lPWM > 100) lPWM = 100;

	/* Normieren von Parametern fuer Balkengrafiken */
	lRelativeSpeed = (abs(lSpeed) * 200) / 15000;
	lRelativeNominalSpeed = (abs(NominalSpeedWebInternal) * 200)  / 15000;
	lRelativePWM = 1 * lPWM;

	/* ALLE WERTE IN TEXTFORM UEBERFUEHREN
	 * uebertragen Sie die Variablen lSpeed, lRelativeSpeed,
	 * lRelativeNominalSpeed, lPWM, lRelativePWM und lVoltage
	 * in entsprechende Zeichenketten.
	 * Nutzen Sie hierfuer die Funktionen itoa bzw. usprintf */

	itoa((int)NominalSpeedWebInternal, NominalSpeed);
	// usprintf( NominalSpeed, "%d", (int)NominalSpeedWebInternal );
	//Aufgabe 5.3
	itoa((int)lSpeed, Speed);
	itoa((int)lVoltage, Voltage);
	itoa((int)lPWM, PWM);
	itoa((int)lRelativeSpeed, RelativeSpeed);
	itoa((int)lRelativeNominalSpeed, RelativeNominalSpeed);
	itoa((int)lRelativePWM, RelativePWM);


	/* Erzeugung des HTML-Codes, currently uses max. 425 byte in field ResultingDoc[] */
	strcpy( ResultingDoc, "<tr><td width=\"180\">Drehzahl</td><td width=\"110\">" );
	strcat( ResultingDoc, Speed );
	strcat( ResultingDoc, " upm</td><td width=\"200\"> <hr align=\"left\" color=\"#FFD827\" size=\"8\" width=\"" );
	strcat( ResultingDoc, RelativeSpeed );
	strcat( ResultingDoc, "\"></td></tr><tr><td>Solldrehzahl</td><td>" );
	strcat( ResultingDoc, NominalSpeed );
	strcat( ResultingDoc, " upm</td><td> <hr align=\"left\" color=\"#FFD827\" size=\"8\" width=\"" );
	strcat( ResultingDoc, RelativeNominalSpeed );
	strcat( ResultingDoc, "\"></td></tr><tr><td>PWM-Duty-Cycle</td><td>" );
	strcat( ResultingDoc, PWM );
	strcat( ResultingDoc, " %</td><td> <hr align=\"left\" color=\"#FFD827\" size=\"8\" width=\"" );
	strcat( ResultingDoc, RelativePWM );
	strcat( ResultingDoc, "\"></td></tr><tr><td>Betriebsspannung</td><td>" );
	strcat( ResultingDoc, Voltage );
	strcat( ResultingDoc, " V</td><td></td></tr>" );

	/* Rueckgabe des erzeugten HTML-Codes */

	if((strlen( ResultingDoc )+1) > (sizeof(ResultingDoc)-5))
		// heap corrupted !!!
		ResultingDoc[22] = 'E';	// Feldueberlauf, 'E' wird in der Ueberschrift eingeblendet

	strcpy( uip_appdata, ResultingDoc);		// frueher sprintf( uip_appdata, ResultingDoc);
	length = strlen(uip_appdata);

	Oszi_OFF
	return length;
}

/**
 * @brief
 *
 * Routine wird aufgerufen, wenn Einsprungspunkt aktiviert wird.
 *
 */
static PT_THREAD(control_page(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_control_page, NULL);
  PSOCK_END(&s->sout);
}


/**
 * @brief
 *
 * In dieser Routine werden dynamische HTML-Inhalte fuer die Anzeige des Eingabefensters erstellt.
 *
 */
static unsigned short
generate_input_field(void *arg)
{
	char NominalSpeed[8];		// Anzeigetext Solldrehzahl
	char TimeConstant[8];		// Anzeigetext Zeitkonstante
	char ResultingDoc[260];		// Puffer fuer erzeugtes Dokument
	int length;

	/* Webserverinterne Parameterspeicherung */
	extern long NominalSpeedWebInternal;
	extern long TimeConstantWebInternal;

	/* Uebertragen der Long-Werte in das Textformat */
	//sprintf( NominalSpeed, "%d", (int)NominalSpeedWebInternal );
	//sprintf( TimeConstant, "%d", (int)TimeConstantWebInternal );
	itoa((int)NominalSpeedWebInternal, NominalSpeed);
	itoa((int)TimeConstantWebInternal, TimeConstant);


	/* Verkettung von HTML und Parametern, max. 250 byte im Feld */
	strcpy( ResultingDoc, "<td align=\"left\"><input type=\"text\" name=\"NominalValue\" maxlength=\"5\" value=\"" );
	strcat( ResultingDoc, NominalSpeed );
	strcat( ResultingDoc, "\" size=\"5\"> upm</td></tr><tr><td align=\"right\">Zeitkonstante:</td><td align=\"left\"><input type=\"text\" name=\"Constant\" value=\"" );
	strcat( ResultingDoc, TimeConstant );
	strcat( ResultingDoc, "\" maxlength=\"4\" size=\"5\"> ms</td></tr>" );

	/* Rueckgabe des erzeugten HTML-Codes */
	//usprintf( uip_appdata, ResultingDoc);
	strcpy( uip_appdata, ResultingDoc);
	length = strlen( uip_appdata );
	return length;
}

/**
 * @brief
 *
 * Routine wird aufgerufen, wenn Einsprungpunkt aktiviert wird.
 *
 */
static PT_THREAD(input_field(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_input_field, NULL);
  PSOCK_END(&s->sout);
}

//! @}

