/*
    FreeRTOS V6.0.5 - Copyright (C) 2010 Real Time Engineers Ltd.

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

  modified by JH, 11/09/01
				  12/09/12
*/


/* Scheduler includes. */
#include "FreeRTOS.h"

/* Library includes. */
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "interrupt.h"
#include "sysctl.h"
#include "timer.h"
#include "gpio.h"

//#include "task.h"
#include "queue.h"
/* Demo app includes. */
//#include "app_tasks.h"


// The set frequency of the interrupt.  Deviations from this are measured as the jitter.
#define timerINTERRUPT_FREQUENCY		( 1000UL ) // 1ms

// The highest available interrupt priority.
#define timerHIGHEST_PRIORITY			( 0 )

// Misc defines.
#define timerMAX_32BIT_VALUE			( 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Interrupt handler in which the user can do what he want cyclic. */
void Timer0IntHandler( void );

/* Counts the total number of times that the high frequency timer has 'ticked'.
This value is used by the run time stats function to work out what percentage
of CPU time each task is taking. */
volatile unsigned portLONG ulHighFrequencyTimerTicks = 0UL;
/*-----------------------------------------------------------*/

//extern tBoolean ControlledMode,StepperMode;
//extern volatile int CounterValue;

void vSetupHighFrequencyTimer( void )
{
unsigned long ulFrequency;

	/* Timer-0 is used to generate interrupts every 1ms,
	 * Timer-1 provide the ticks (20ns) for measuring the distance between commutation-INTs. */
	SysCtlPeripheralEnable( SYSCTL_PERIPH_TIMER0 );
    SysCtlPeripheralEnable( SYSCTL_PERIPH_TIMER1 );
    TimerConfigure( TIMER0_BASE, TIMER_CFG_32_BIT_PER );
    TimerConfigure( TIMER1_BASE, TIMER_CFG_32_BIT_PER );

	/* Set the timer interrupt to be above the kernel - highest. */
	IntPrioritySet( INT_TIMER0A, timerHIGHEST_PRIORITY );

	/* Just used to measure time. */
    TimerLoadSet(TIMER1_BASE, TIMER_A, timerMAX_32BIT_VALUE );

	/* Ensure interrupts do not start until the scheduler is running. */
	portDISABLE_INTERRUPTS();

	/* The rate at which the timer will interrupt. */
	ulFrequency = configCPU_CLOCK_HZ / timerINTERRUPT_FREQUENCY;
    TimerLoadSet( TIMER0_BASE, TIMER_A, ulFrequency );
    //IntEnable( INT_TIMER0A );
    //TimerIntEnable( TIMER0_BASE, TIMER_TIMA_TIMEOUT );

	/* Enable both timers. */
    TimerEnable( TIMER0_BASE, TIMER_A ); // when disabled, better debugging is provided
    TimerEnable( TIMER1_BASE, TIMER_A );
}
/*-----------------------------------------------------------*/

void Timer0IntHandler( void )
{
//	GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_0, 1);	// added by JH for Test_OSZI_signal

	TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT );

	// Keep a count of the total number of 1KHz ticks.  This is used by ...
	ulHighFrequencyTimerTicks++;

//    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_0, 0);  // INT_delay = 1.5�s

}





