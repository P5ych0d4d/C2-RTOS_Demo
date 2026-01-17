/**
 * \addtogroup Praktikumsdokumente
 *
 * @{
 *
 * @file app_additional_funcs.c
 *
 * Zus�tzliche Funktionen sollten hier untergebracht werden
 *
 * @date 04.04.2010
 * @author Jan Rothkegel
 * modified by JH, 11/08/29
 * modified by JH, 12/09/12       Type-Anpassungen
 * modified by JH, 22/05/13	 Anpassungen fuer CCS-Implementierung
 */

/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "hw_types.h"
#include "hw_memmap.h"
//#include "uart.h"
void itoa(int , char *);
extern int usprintf(char *pcBuf, const char *pcString, ...);

/* Demo app includes. */
//#include "app_tasks.h"
extern xQueueHandle xOLEDQueue;

#ifndef APP_ADDITIONAL_FUNCS_C_
#define APP_ADDITIONAL_FUNCS_C_

/**
 * @brief
 *
 * Tauscht das Element einer 1-elementigen Queue aus
 *
 * Bei Queues, welche nur ein Element besitzen und per xQueuePeek() von mehreren Tasks ausgelesen werden,
 * bietet sich die Verwendung von xQueueChangeValue() an. Das akuelle Element wird gel�scht und es ein neues
 * erstellt.
 *
 * @author Jan Rothkegel
 *
 */
signed portBASE_TYPE xQueueChangeValue( xQueueHandle pxQueue, const void * const pvItemToQueue)
{
	void * const DummyItem = 0;
	signed portBASE_TYPE ReturnValue;

	//Block system in case of a systick-interrupt
	taskENTER_CRITICAL();
	{
		//Delete old item from queue
		xQueueReceive( pxQueue, DummyItem, 0 );
		//Write new item to queue
		ReturnValue = xQueueSend( pxQueue, pvItemToQueue, 0 );
	}
	taskEXIT_CRITICAL();
	return (ReturnValue);
}


void PrintStatus(long Speed, long NominalSpeed, long uk, long Voltage)
{

//	static xOLEDMessage xMessage = {0,0,0,}; //{ "EMPTY" };
//float voltage_f;
//double intpart;
//long Voltage_F;
char DumpLine[30];
int i;
																// mod. by JH, eliminate the display_flicker
	// bei einem Zeichensatz von 6x8 bedeutet: x=60 11.Zeichen in der Zeile und y=20 3.Zeile (2 pixel 'Luft' zw. Zeilen)
	DumpLine[0]=60;  // x_pos of cursor
	DumpLine[1]=20;  // y_pos of cursor
	usprintf( &DumpLine[2], "%04d ", (int)Speed);		// cur. speed
	//itoa((int)Speed, &DumpLine[2]);
	xQueueSend( xOLEDQueue, &DumpLine, 0 );

	DumpLine[0]=60;  // x_pos of cursor
	DumpLine[1]=30;  // y_pos of cursor
	usprintf( &DumpLine[2], "%04d ", (int)NominalSpeed);	// setpoint
	//itoa((int)NominalSpeed, &DumpLine[2]);
	xQueueSend( xOLEDQueue, &DumpLine, 0 );

	DumpLine[0]=60;  // x_pos of cursor
	DumpLine[1]=40;  // y_pos of cursor
	//voltage_f = (modf (Voltage/10.0 , &intpart))*10.0;		// da sprintf(...,%f,...) ERROR liefert
	//Voltage_F=voltage_f;
	//Voltage=intpart;
	//sprintf( &DumpLine[2], "%d.%d ",(int)Voltage,(int)Voltage_F);  // cur. voltage
	itoa((int)Voltage, &DumpLine[2]);
	//i = strlen(DumpLine);
	//DumpLine[i++] = '.';
	//itoa((int)Voltage_F, &DumpLine[i]);

	// setze DP einfacher
	i = strlen(DumpLine);
	DumpLine[i] = DumpLine[i-1];
	DumpLine[i-1] = '.';
	DumpLine[i+1] = ' ';	// loesche zwei LCD_Stellen
	DumpLine[i+2] = ' ';
	DumpLine[i+3] = 0;
	xQueueSend( xOLEDQueue, &DumpLine, 0 );

	DumpLine[0]=60;  // x_pos of cursor
	DumpLine[1]=50;  // y_pos of cursor
	usprintf( &DumpLine[2], "%d ", (int)uk);
	//itoa((int)uk, &DumpLine[2]);
	xQueueSend( xOLEDQueue, &DumpLine, 0 );		// cur. duty cycle
}

// missing stdlib_functions
// reverse:  reverse string s in place
void reverse(char ss[])
{
     int ii, jj;
     char cc;

     for (ii = 0, jj = strlen(ss)-1; ii<jj; ii++, jj--) {
         cc = ss[ii];
         ss[ii] = ss[jj];
         ss[jj] = cc;
     }
}
// itoa:  convert n to characters in s without leading zeros
void itoa(int nn, char ss[])
{
     int ii, sign;

     if ((sign = nn) < 0)  /* record sign */
         nn = -nn;          /* make n positive */
     ii = 0;
     do {       /* generate digits in reverse order */
         ss[ii++] = nn % 10 + '0';   /* get next digit */
     } while ((nn /= 10) > 0);     /* delete it */
     if (sign < 0)
         ss[ii++] = '-';
     ss[ii] = '\0';
     reverse(ss);
}

#endif /* APP_ADDITIONAL_FUNCS_C_ */

//! @}
