/*
    FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/**
 * \addtogroup Praktikumsdokumente
 *
 * @{
 *
 * @file main.c
 *
 * In dieser Datei ist das Hauptprogramm inkl. Initialisierungsaufrufen enthalten.
 *
 *
 * @date 04.04.2010
 * @author Richard Barry
 * @author Jan Rothkegel
 * modified by JH, 11/08/29
 * modified by RB, 11/09/15
 * modified by RB, 12/08/02
 * modified by JH, 12/08/27
 * modified by JH, 12/09/13  V4.0        Projekt-Struktur-Optimierung/FreeRTOSV7.2.0
 * modified by JH, 22/08/17  V4.1		 mit Farb-LCD
 * modified by JH, 22/08/18  V4.2		 kleine Korrekturen in vOLEDTask()
 * modified by JH, 22/08/23  V4.3		 LCD-Refresh im EXEC_MODE 2 ge�ndert.
 * modified by JH, 22/08/24  V4.4		 UART-Service mit Ringpuffern und INT-Mode
 * modified by JH, 22/10/04	 V4.5		 kleine Anpassungen
 * modified by JH, 22/10/04	 V4.51		 CCS-Version
 * modified by JH, 23/02/02	 V4.52		 httpd-cgi.c und Web-UI angepasst
 * modified by JH, 23/02/03	 V4.53		 httpd-cgi.c und Web-UI angepasst
 */

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Hardware library includes. */
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "sysctl.h"
#include "gpio.h"
#include "pwm.h"
// for LCD
#include "ST7735.h"

#include "lcd_message.h"
//#define logo	1
#ifdef logo
#include "bitmap.h"
#endif
/* app includes. */
#include "main.h"
#include "app_tasks.h"
#include "app_additional_funcs.h"
//#include "hw_api.h"
#include "timertest.h"
#include "uartDrv.h"

#define Oszi_ON 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 1);		// added by JH for Test_OSZI_signal
#define Oszi_OFF 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 0);		// added by JH for Test_OSZI_signal

/* Program Execution Mode:
 * 1: Praktikum Teil 1
 * 2: Praktikum Teil 2
 * 3: Demo
 */
#define EXEC_MODE 1

// Queues provided for process communication
xQueueHandle xOLEDQueue;

// Semaphores provided for process synchronization
xSemaphoreHandle xSemaphore1;
xSemaphoreHandle xSemaphore2;

/*-----------------------------------------------------------*/

/**
 * @fn int main( )
 *
 * @brief
 *
 * Hauptprogramm zur Initialisierung von Hardware und Tasks
 *
 * An dieser Stelle wird die Initialisierung der Hardware und der Prozesskommunikationsmittel aufgerufen,
 * es werden die Tasks aufgesetzt und der Scheduler aktiviert.
 *
 * @author Jan Rothkegel
 *
 */
int main( void )
{

	/* Hardware-Initialisierung aufrufen */
	prvSetupHardware();
    InitConsole();	// Set up the serial console to use for displaying messages
    // Display the startup message on the console.
    UARTSend("App started \n\r", 14);

	if(EXEC_MODE==1)			/* Praktikum Teil 1 */
	{
		//Aufgabe 4.4 - auskommentieren zuvor
		vSemaphoreCreateBinary(xSemaphore1);
		vSemaphoreCreateBinary(xSemaphore2);

		// Aufgabe 4.2 OLEDQueue anlegen
		xOLEDQueue = xQueueCreate(1, sizeof(xOLEDMessage)); // Fehlerbehandlung hinzufügen



		// Tasks anlegen
		xTaskCreate( vTask1, ( signed char * ) "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL );

		// Aufgabe 4.1
		/* Tasks anlegen */
		xTaskCreate( vVoltage_Supervisor, ( signed portCHAR * ) "Voltage", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY + 2, NULL );
		xTaskCreate( vSpeed_Control, ( signed portCHAR * ) "Speed", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY + 3, NULL );

		// AUfgabe 4.2
		/* Task fuer Display-Anzeige erzeugen */
		xTaskCreate( vOLEDTask, ( signed portCHAR * ) "OLED", mainOLED_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + 4, NULL );


		// Aufgabe 4.3
		/* Tasks Voltage, Speed und OLED obene auskomemntieren*/
		xTaskCreate( vTask2, ( signed char * ) "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL );
		xTaskCreate( vTask3, ( signed char * ) "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL );
		xTaskCreate( vTask4, ( signed char * ) "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL );
	}
	else if(EXEC_MODE==2)		/* Praktikum Teil 2 */
	{
		/* Queues fuer Interprozesskommunikation erzeugen */
		SetupProcessCommunication();

		/* Tasks anlegen */
		xTaskCreate( vVoltage_Supervisor, ( signed portCHAR * ) "Voltage", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY + 2, NULL );
		xTaskCreate( vSpeed_Control, ( signed portCHAR * ) "Speed", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY + 3, NULL );

		// TCP/IP-Stack anlegen
		if( SysCtlPeripheralPresent( SYSCTL_PERIPH_ETH ) )
		{
//		  xTaskCreate( vuIP_Task, ( signed portCHAR * ) "uIP", mainBASIC_WEB_STACK_SIZE, NULL, tskIDLE_PRIORITY + ???, NULL );
		}

		/* Task fuer Display-Anzeige erzeugen */
//		xTaskCreate( vOLEDTask, ( signed portCHAR * ) "OLED", mainOLED_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + ???, NULL );
	}

	vTaskStartScheduler();					// start scheduler

    // program never reaches this point
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/

/**
 * @fn void prvSetupHardware( void )
 *
 * @brief
 *
 * Routine zur Hardware-Initialisierung
 *
 * Die Hardware-Initialisierung besteht aus zwei Komponenten. Einerseits werden boardspezifische
 * Merkmale wie der Systemtakt und die LEDs fuer die Ethernet-Schnittstelle geschalten. Weiterhin
 * wird die Routine hw_Init() aufgerufen, die die anwendungsspezifische Initialisierung vornimmt.
 *
 * @author Jan Rothkegel
 *
 */
void prvSetupHardware( void )
{
	/* If running on Rev A2 silicon, turn the LDO voltage up to 2.75V.  This is
    a workaround to allow the PLL to operate reliably. */
    if( DEVICE_IS_REVA2 )
    {
        SysCtlLDOSet( SYSCTL_LDO_2_75V );
    }

	/* Set the clocking to run from the PLL at 50 MHz */
	SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );

	/* 	Enable Port F for Ethernet LEDs
		LED0        Bit 3   Output
		LED1        Bit 2   Output */
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF );
	GPIODirModeSet( GPIO_PORTF_BASE, (GPIO_PIN_2 | GPIO_PIN_3), GPIO_DIR_MODE_HW );
	GPIOPadConfigSet( GPIO_PORTF_BASE, (GPIO_PIN_2 | GPIO_PIN_3 ), GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );


	/* Rufe eigene Routine zur Initialisierung auf */
	hw_Init();						// Port-Init  und INT-Freigabe

	vSetupHighFrequencyTimer();   // Timer_1 to measure the speed exactly, Timer_0 delivers a high priority periodical INT_source
	// We use the timer_1 counter value to measure the clock cycles between the commutation-interrupts.

//	hw_SetPulseWidth(500);   // orig. 70%, zum Test auf 100% setzen, ab Version 2_04 auf das Zehnfache erhoeht
		// wird bei aktiven Drehzahlregler nicht gebraucht.

	CommutationControlEx(0); // fuer die sichere zweite Umpolung der Wicklungen des Motors  added by JH
}

/*-----------------------------------------------------------*/
/**
 * @brief
 *
 * Routine zur Display-Darstellung
 *
 * Durch das Schreiben von Daten in xOLEDQueue wird dieser Task aktiviert. Er organisiert den Transfer
 * der Pixel- bzw. Textdaten zum Display.
 *
 * @author Jan Rothkegel
 *
 */
void vOLEDTask( void *pvParameters )
{
xOLEDMessage xMessage;
xOLEDMessageLong xMessage2;
unsigned portLONG ulY,ulMaxY;

/* Functions to access the OLED.  The one used depends on the dev kit being used. */
void ( *vOLEDInit )( void ) = NULL;
void ( *vOLEDStringDraw )( portCHAR *, int , int ) = NULL;
void ( *vOLEDImageDraw )( int , int , int , int , bitmapdatatype , int ) = NULL;
void ( *vOLEDClear )( uint16_t ) = NULL;

	/* Map the LCD access functions to the driver functions that are appropriate
	for the evaluation kit being used. */
	vOLEDInit = LCDinit;
	vOLEDStringDraw = lcd7735_print;		// alt: RIT128x96x4StringDraw;
	vOLEDImageDraw = lcd7735_drawBitmap;	// alt: RIT128x96x4ImageDraw;
	vOLEDClear = lcd7735_fillScreen;		// alt: RIT128x96x4Clear;
	ulMaxY = mainMAX_ROWS_128;

	vOLEDInit();	// Initialize the display
	lcd7735_setForeground(ST7735_YELLOW);

	if(EXEC_MODE==2)	// output the message to a predefined LCD-position
	{
#ifdef logo
		vOLEDImageDraw(0,0,160,61,(bitmapdatatype)freertos,1);
#endif
		vOLEDStringDraw( "please wait...", 0, 88);
		vTaskDelay(1000);			// wait one sec
		vOLEDClear(ST7735_BLACK);
		vOLEDStringDraw( "BLDC-WebControl", 10, 0);
		vOLEDStringDraw( "Speed           upm", 0, 20);
		vOLEDStringDraw( "SetPoint        upm", 0, 30);
		vOLEDStringDraw( "Voltage         V", 0, 40);
		vOLEDStringDraw( "PWM (k)         %", 0, 50);
		vOLEDStringDraw( "press SELECT to start", 0, 68);
		vOLEDStringDraw( "TCP:", 0, 120);
		lcd7735_setForeground(ST7735_GREEN);

		for( ;; )
		{
			/* Wait for a message to arrive that requires displaying. */
			xQueueReceive( xOLEDQueue, &xMessage2, portMAX_DELAY );
			// Oszi_ON;  //

			// Write the message to xy_position, coming from the source_task
			vOLEDStringDraw( xMessage2.pcMessage, xMessage2.x, xMessage2.y);
			// Oszi_OFF;  // INT_delay = ca. 3.2ms      mit OLED ca. 500 �s
		}
	}
	else 	// line-oriented output, das Queue-Element hat eine Groesze von acht Byte, x-pos, y-pos, Zeiger auf String
	{
		ulY = ulMaxY;
		for( ;; )
		{
			/* Wait for a message to arrive that requires displaying. */
			xQueueReceive( xOLEDQueue, &xMessage, portMAX_DELAY );

			/* Write the message on the next available row. */
			if( ulY >= ulMaxY )	// check, if y-position exceeds the LCD_end_position
			{
				ulY = 0;
				vOLEDClear(ST7735_BLACK);
			}
			// Display the message
			vOLEDStringDraw( xMessage.pcMessage, xMessage.x, ulY);
			ulY += mainCHARACTER_HEIGHT;	// line y_position for the next
		}
	}
}

/*-----------------------------------------------------------*/

/**
 * @brief
 *
 * Enthaelt eine Endlosschleife, die das System stilllegt.
 *
 * Wird der Stack eines Tasks ueberschritten wird dieser task aktiviert, der das System blockiert und
 * jegliche weitere Abarbeitung der anderen Tasks verhindert. Interrupts werden aber weiterhin behandelt.
 *
 * @author Jan Rothkegel
 *
 */
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
	for( ;; );
}
/**
 * @fn void vApplicationTickHook( void )
 *
 * @brief
 *
 * Routine bei Taskwechsel
 *
 * Aktivierung bei TimerTick.
 *
 * @author Jan Rothkegel
 *
 */
void vApplicationTickHook( void )
{

}
/**
 * @brief
 *
 * Aktivierung dieser Routine erfolgt immer dann, wenn System nicht ausgelastet ist
 *
 * Hier koennen z.B. niederpriore Aufgaben untergebracht werden. Es empfiehlt sich jedoch immer
 * das Anlegen eines seperaten Tasks fuer dererlei Angelegenheiten.
 *
 * @author Jan Rothkegel
 *
 */
void vApplicationIdleHook( void )
{

}

//! @}

/*********************** Generic Wait Functions *******************************/
/**
* @brief   Wait for Timeout (Time Delay)
* @param   millisec      time delay value
* @retval  status code that indicates the execution status of the function.
*/
void delay_ms (uint32_t millisec)
{
#if INCLUDE_vTaskDelay


  vTaskDelay(millisec);          /* Minimum delay = 1 tick */


#else
  (void) millisec;

  return osErrorResource;
#endif
}



