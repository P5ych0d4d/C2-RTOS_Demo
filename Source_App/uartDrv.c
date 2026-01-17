//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2005-2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 7611 of the EK-LM3S6965 Firmware Package.
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the FTDI virtual serial port on the evaluation board) will be
//! configured in 115,200 baud, 8-n-1 mode.  All characters received on the
//! UART are transmitted back to the UART.
//
//*****************************************************************************
//	adapted by JH 			Version 2.1  14.4.22
//  with ISR_ and queue_based UART-communication
#include <stdbool.h>
/* Hardware library includes. */
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "gpio.h"
#include "pwm.h"
#include "uart.h"
#include "sysctl.h"
#include "ringbuf.h"

//*****************************************************************************
//
//! The size of the ring buffers used for interface between the UART and
//! telnet session (RX).
//
//*****************************************************************************
#define RX_RING_BUF_SIZE        (256)

//*****************************************************************************
//
//! The size of the ring buffers used for interface between the UART and
//! telnet session (TX).
//
//*****************************************************************************
#define TX_RING_BUF_SIZE        (256)

//*****************************************************************************
//
//! The size of the ring buffers used for interface between the UART and
//! telnet session (RX).
//
//*****************************************************************************
#define RX_RING_BUF_SIZE        (256)

//*****************************************************************************
//
//! The size of the ring buffers used for interface between the UART and
//! telnet session (TX).
//
//*****************************************************************************
#define TX_RING_BUF_SIZE        (256)

// prototypes
extern void delay_ms (unsigned long );
void hw_init();

unsigned long SerialReceiveAvailable();

unsigned long SysTickCnt = 0;
bool lcd_ready;
bool RxBufFull;
bool signal_LCD_out;
//*****************************************************************************
//
//! The buffer used to hold characters received from the UART0.
//
//*****************************************************************************
static unsigned char g_pucRX0Buffer[RX_RING_BUF_SIZE];

//*****************************************************************************
//
//! The buffer used to hold characters to be sent to the UART0.
//
//*****************************************************************************
static unsigned char g_pucTX0Buffer[TX_RING_BUF_SIZE];

//*****************************************************************************
//
//! The ring buffers used to hold characters received from the UARTs.
//
//*****************************************************************************
 tRingBufObject g_sRxBuf[1];

//*****************************************************************************
//
//! The ring buffers used to hold characters to be sent to the UARTs.
//
//*****************************************************************************
static tRingBufObject g_sTxBuf[1];



//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void InitConsole(void)
{
    //
    // Initialize the ring buffers used by the UART Drivers.
    //
    RingBufInit(&g_sRxBuf[0], g_pucRX0Buffer, sizeof(g_pucRX0Buffer));
    RingBufInit(&g_sTxBuf[0], g_pucTX0Buffer, sizeof(g_pucTX0Buffer));

	//
	// Enable GPIO port A which is used for UART0 pins.
	// TODO: change this to whichever GPIO port you are using.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	// Configure the first UART for 115,200, 8-N-1 operation.
	 //
	// Enable peripheral, other fault is generated
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	// Configure the Port A, pins 0,1 appropriately.
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
						 (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
						  UART_CONFIG_PAR_NONE));
	// UARTEnable(UART0_BASE);  already done in UARTConfigSetExpClk()
    //
    // Enable the UART interrupt.
    //
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

}

//*****************************************************************************
//
// Send a frame to the UART.
//
//! This function send a frame to the UART.  The frame will either be
//! directly written into the UART FIFO or into the UART transmit buffer, as
//! appropriate.
//!
//! \param pucBuffer is the frame pointer
//! \param ulCount is the frame length
//! \return status of success
//
//*****************************************************************************
bool UARTSend(unsigned char *pucBuffer, unsigned long ulCount)
{
    //
    // Disable the UART transmit interrupt while determining how to handle this
    // character.  Failure to do so could result in the loss of this character,
    // or stalled output due to this character being placed into the UART
    // transmit buffer but never transferred out into the UART FIFO.
    //
    UARTIntDisable(UART0_BASE, UART_INT_TX);

    // Loop while there are more characters to send.
    while(ulCount--)
    {
        //UARTCharPutNonBlocking(UART0_BASE, *pucBuffer++);	// Write the next character to the UART.

        // See if the transmit buffer is empty and there is space in the FIFO.
        if(RingBufEmpty(&g_sTxBuf[0]) && UARTSpaceAvail(UART0_BASE))		// RingBufEmpty(&g_sTxBuf[0]) &&
            UARTCharPut(UART0_BASE, *pucBuffer++);	// Write this character directly into the FIFO.
        else
			if(!RingBufFull(&g_sTxBuf[0]))			// See if there is space in the transmit buffer.
				RingBufWriteOne(&g_sTxBuf[0], *pucBuffer++);	// Put this character into the transmit buffer.
			else
				return false;
    }
    UARTIntEnable(UART0_BASE, UART_INT_TX);	// Enable the UART transmit interrupt.
    return true;
}

//*****************************************************************************
//
//! Receives n characters from the UART.
//!
//! \param pucData is pointer for the data to stored there
//! \param ulCount is the frame length
//! This function receives a character from the relevant port's UART buffer.
//!
//! \return Returns -1 if no data is available or the oldest character held in
//! the receive ring buffer.
//
//	!!! must combine with SerialReceiveAvailable() for determining the size to read !!!
//
//*****************************************************************************
long UARTReceive(unsigned char *pucData, unsigned long ulCount)
{
    // See if the receive buffer is empty and there is space in the FIFO.
    if(RingBufEmpty(&g_sRxBuf[0]))
    {
        //
        // Return -1 (EOF) to indicate no data available.
        //
        return(-1);
    }
    //ulData = (long)RingBufReadOne(&g_sRxBuf[0]);	// Read a single character.

    // or read a block of data
    RingBufRead(&g_sRxBuf[0], pucData, ulCount);

    return(0);		// without sense here
}

//*****************************************************************************
//
//! Returns number of characters available in the serial ring buffer.
//!
//! \param ulPort is the UART port number to be accessed.
//!
//! This function will return the number of characters available in the
//! serial ring buffer.
//!
//! \return The number of characters available in the ring buffer..
//
//*****************************************************************************
unsigned long SerialReceiveAvailable()
{
    //
    // Return the value.
    //
    return(RingBufUsed(&g_sRxBuf[0]));
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void UARTIntHandler(void)
{
    unsigned long ulStatus;
    unsigned char ucChar;

    ulStatus = UARTIntStatus(UART0_BASE, true);	// Get the interrupt status

    UARTIntClear(UART0_BASE, ulStatus);			// Clear the asserted interrupts

    //
    // See if there is data to be processed in the receive FIFO.
    //
    if(ulStatus & (UART_INT_RT | UART_INT_RX))	// UART_INT_RT not used here
    {
        //
        // Loop while there are characters available in the receive FIFO.
        //
        while(UARTCharsAvail(UART0_BASE))
        {
            //
            // Get the next character from the receive FIFO.
            //
            ucChar = UARTCharGet(UART0_BASE);
            if(RingBufFree(&g_sRxBuf[0]) >= 1)
            		RingBufWriteOne(&g_sRxBuf[0], ucChar);
            else
            	RxBufFull = true;
        }
    }

    // See if there is space to be filled in the transmit FIFO.
    //
    if(ulStatus & UART_INT_TX)
    {
        //
        // Loop while there is space in the transmit FIFO and characters to be
        // sent.
        //
        while(!RingBufEmpty(&g_sTxBuf[0]) &&
        		UARTSpaceAvail(UART0_BASE))
        {
            //
            // Write the next character into the transmit FIFO.
            //
            UARTCharPut(UART0_BASE, RingBufReadOne(&g_sTxBuf[0]));
        }
    }
}

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

// end of source
