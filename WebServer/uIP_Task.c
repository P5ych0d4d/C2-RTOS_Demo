/*
    FreeRTOS V6.0.3 - Copyright (C) 2010 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS eBook                                  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/**
 * \addtogroup Praktikumsdokumente
 *
 * @{
 *
 * @file uIP_Task.c
 *
 * In dieser Datei befindet sich die Routine vApplicationProcessFormInput(), in welcher Formulardaten abgefragt werden.
 *
 * @date 04.04.2010
 * @author Jan Rothkegel
 * @author Adam Dunkels
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uip/timer_e.h>
#include <uip/uip.h>
#include <uip/uip_arp.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "lcd_message.h"

/* uip includes. */
#include "hw_types.h"

#include "httpd.h"
#include "clock-arch.h"
#include "hw_ethernet.h"
#include "pwm.h"
#include "sysctl.h"
#include "gpio.h"
#include "ethernet.h"
#include "hw_memmap.h"
#include "flash.h"						// changed by JH 1/16
#include "sysctl.h"

/* Demo includes. */
#include "emac.h"
//#include "partest.h"                 // canceled by JH
#include "app_tasks.h"

/*-----------------------------------------------------------*/

/* IP address configuration. */
#define uipIP_ADDR0		172
#define uipIP_ADDR1		25
#define uipIP_ADDR2		218
#define uipIP_ADDR3		19	

/* How long to wait before attempting to connect the MAC again. */
#define uipINIT_WAIT    100

/* Shortcut to the header within the Rx buffer. */
#define xHeader ((struct uip_eth_hdr *) &uip_buf[ 0 ])

/* Standard constant. */
#define uipTOTAL_FRAME_HEADER_SIZE	54

/*-----------------------------------------------------------*/

/*
 * Send the uIP buffer to the MAC.
 */
static void prvENET_Send(void);

/*
 * Setup the MAC address in the MAC itself, and in the uIP stack.
 */
static void prvSetMACAddress( void );

/*
 * Port functions required by the uIP stack.
 */
void clock_init( void );
clock_time_t clock_time( void );

/*-----------------------------------------------------------*/

/* The semaphore used by the ISR to wake up the uIP task. */
extern xSemaphoreHandle xEMACSemaphore;

/*-----------------------------------------------------------*/

void clock_init(void)
{
	/* This is done when the scheduler starts. */
}
/*-----------------------------------------------------------*/

clock_time_t clock_time( void )
{
	return xTaskGetTickCount();
}


void vuIP_Task( void *pvParameters )
{
portBASE_TYPE i;
uip_ipaddr_t xIPAddr;
struct timer periodic_timer, arp_timer;
extern void ( vEMAC_ISR )( void );

	/* Enable/Reset the Ethernet Controller */
	SysCtlPeripheralEnable( SYSCTL_PERIPH_ETH );
	SysCtlPeripheralReset( SYSCTL_PERIPH_ETH );

	/* Create the semaphore used by the ISR to wake this task. */
	vSemaphoreCreateBinary( xEMACSemaphore );
	
	/* Initialise the uIP stack. */
	timer_set( &periodic_timer, configTICK_RATE_HZ / 2 );
	timer_set( &arp_timer, configTICK_RATE_HZ * 10 );
	uip_init();
	uip_ipaddr( xIPAddr, uipIP_ADDR0, uipIP_ADDR1, uipIP_ADDR2, uipIP_ADDR3 );
	uip_sethostaddr( xIPAddr );
	httpd_init();
	uip_listen(HTONS(1000));		// simple echo service

	while( vInitEMAC() != pdPASS )
    {
        vTaskDelay( uipINIT_WAIT );
    }
	prvSetMACAddress();	
	

	for( ;; )
	{
		/* Is there received data ready to be processed? */
		uip_len = uiGetEMACRxData( uip_buf );
		
		if( uip_len > 0 )
		{
			/* Standard uIP loop taken from the uIP manual. */

			if( xHeader->type == htons( UIP_ETHTYPE_IP ) )
			{
				uip_arp_ipin();
				uip_input();

				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if( uip_len > 0 )
				{
					uip_arp_out();
					prvENET_Send();
				}
			}
			else if( xHeader->type == htons( UIP_ETHTYPE_ARP ) )
			{
				uip_arp_arpin();

				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if( uip_len > 0 )
				{
					prvENET_Send();
				}
			}
		}
		else
		{
			if( timer_expired( &periodic_timer ) )
			{
				timer_reset( &periodic_timer );
				for( i = 0; i < UIP_CONNS; i++ )
				{
					uip_periodic( i );
	
					/* If the above function invocation resulted in data that
					should be sent out on the network, the global variable
					uip_len is set to a value > 0. */
					if( uip_len > 0 )
					{
						uip_arp_out();
						prvENET_Send();
					}
				}	
	
				/* Call the ARP timer function every 10 seconds. */
				if( timer_expired( &arp_timer ) )
				{
					timer_reset( &arp_timer );
					uip_arp_timer();
				}
			}
			else
			{			
				/* We did not receive a packet, and there was no periodic
				processing to perform.  Block for a fixed period.  If a packet
				is received during this period we will be woken by the ISR
				giving us the Semaphore. */
				xSemaphoreTake( xEMACSemaphore, configTICK_RATE_HZ / 2 );			
			}
		}
	}
}
/*-----------------------------------------------------------*/

static void prvENET_Send(void)
{
    vInitialiseSend();
    vIncrementTxLength( uip_len );
    vSendBufferToMAC();
}
/*-----------------------------------------------------------*/

static void prvSetMACAddress( void )
{
unsigned portLONG ulUser0, ulUser1;
unsigned char pucMACArray[8];
struct uip_eth_addr xAddr;

	/* Get the device MAC address from flash */
    FlashUserGet(&ulUser0, &ulUser1);

	/* Convert the MAC address from flash into sequence of bytes. */
    pucMACArray[0] = ((ulUser0 >>  0) & 0xff);
    pucMACArray[1] = ((ulUser0 >>  8) & 0xff);
    pucMACArray[2] = ((ulUser0 >> 16) & 0xff);
    pucMACArray[3] = ((ulUser1 >>  0) & 0xff);
    pucMACArray[4] = ((ulUser1 >>  8) & 0xff);
    pucMACArray[5] = ((ulUser1 >> 16) & 0xff);

	/* Program the MAC address. */
    EthernetMACAddrSet(ETH_BASE, pucMACArray);

	xAddr.addr[ 0 ] = pucMACArray[0];
	xAddr.addr[ 1 ] = pucMACArray[1];
	xAddr.addr[ 2 ] = pucMACArray[2];
	xAddr.addr[ 3 ] = pucMACArray[3];
	xAddr.addr[ 4 ] = pucMACArray[4];
	xAddr.addr[ 5 ] = pucMACArray[5];
	uip_setethaddr( xAddr );
}
/*-----------------------------------------------------------*/


long NominalSpeedWebInternal = 5000;
long TimeConstantWebInternal = 25;		// PI-Regler mit Tn = 25 ms


void vApplicationProcessFormInput( portCHAR *pcInputString, portBASE_TYPE xInputLength )
{
char *c, *pcText;
long lValue = 0;
//static portCHAR cMessageForDisplay[ 32 ];
//extern xQueueHandle xOLEDQueue;
//extern xQueueHandle xRequestServiceQueue;
//xOLEDMessage xOLEDMessage;


    /* Process the form inputs */

    c = strstr( pcInputString, "?" );

    if( c )
    {

       	/* input.shtml */
		if( strstr( pcInputString, "input.shtml" ) != NULL )
		{

			/* Pr�fen, ob Parameter �bergeben wurde */
			if( strstr( c, "NominalValue=" ) != NULL )
			{

				/* Suchen der Anfangsposition des Sollwertes in URL */
				pcText = strstr( c, "NominalValue=" );
				pcText += strlen( "NominalValue=" );

				/* Konvertieren des Sollwertes nach Long */
				lValue=atol(pcText);

				/* Setzen der webserverinternen Variable (schnell) */
				NominalSpeedWebInternal = lValue;
				/* Senden des Sollwertes an Drehzahlregler (langs.) */
				xQueueSend( xNominalSpeedQueue, &lValue, 0);

				/* Finde Zeitkonstante in URL */
				pcText = strstr( c, "Constant=" );
				pcText += strlen( "Constant=" );

				/* Konvertiere Zeitkonstante nach Long */
				lValue=atol(pcText);

				/* Setzen der webserverinternen Variable */
				TimeConstantWebInternal = lValue;
				/* Senden der neuen Zeitkonstante an Drehzahlregler */
				xQueueSend( xTimeConstantQueue, &lValue, 0);

				/* Zur�cksetzen des Pointers um URL abzuschlie�en  */
				*c = 0x00;

			}

		}

    }
}
//! @}
