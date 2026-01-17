;
;    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.;
;
;
;   ***************************************************************************
;    *                                                                       *
;    *    FreeRTOS tutorial books are available in pdf and paperback.        *
;    *    Complete, revised, and edited pdf reference manuals are also       *
;    *    available.                                                         *
;    *                                                                       *
;    *    Purchasing FreeRTOS documentation will not only help you, by       *
;    *    ensuring you get running as quickly as possible and with an        *
;    *    in-depth knowledge of how to use FreeRTOS, it will also help       *
;    *    the FreeRTOS project to continue with its mission of providing     *
;    *    professional grade, cross platform, de facto standard solutions    *
;    *    for microcontrollers - completely free of charge!                  *
;    *                                                                       *
;    *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
;    *                                                                       *
;    *    Thank you for using FreeRTOS, and thank you for your support!      *
;    *                                                                       *
;   ***************************************************************************
;
;
;   This file is part of the FreeRTOS distribution.
;
;   FreeRTOS is free software; you can redistribute it and/or modify it under
;   the terms of the GNU General Public License (version 2) as published by the
;   Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
;   >>>NOTE<<< The modification to the GPL is included to allow you to
;   distribute a combined work that includes FreeRTOS without being obliged to
;   provide the source code for proprietary components outside of the FreeRTOS
;   kernel.  FreeRTOS is distributed in the hope that it will be useful, but
;   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
;   more details. You should have received a copy of the GNU General Public
;   License and the FreeRTOS license exception along with FreeRTOS; if not it
;   can be viewed here: http://www.freertos.org/a00114.html and also obtained
;   by writing to Richard Barry, contact details for whom are available on the
;   FreeRTOS WEB site.
;
;   1 tab == 4 spaces!
;   
;   ***************************************************************************
;    *                                                                       *
;    *    Having a problem?  Start by reading the FAQ "My application does   *
;    *    not run, what could be wrong?                                      *
;    *                                                                       *
;    *    http://www.FreeRTOS.org/FAQHelp.html                               *
;    *                                                                       *
;   ***************************************************************************;
;
;   
;   http://www.FreeRTOS.org - Documentation, training, latest information, 
;   license and contact details.
;   
;   http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
;   including FreeRTOS+Trace - an indispensable productivity tool.
;
;   Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
;   the code with commercial support, indemnification, and middleware, under 
;   the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
;   provide a safety engineered and independently SIL3 certified version under 
;   the SafeRTOS brand: http://www.SafeRTOS.com.
;

	.thumb


	.ref pxCurrentTCB
	.ref vTaskSwitchContext
	.ref prvGetRegistersFromStack

	.def vPortPendSVHandler
	.def vPortClearInterruptMask
	.def vPortSetInterruptMask
	.def vPortSVCHandler
	.def vPortStartFirstTask
	.def vHardFaultExt

NVIC: 		 			.word 0xE000ED08
curTCB:   				.word pxCurrentTCB

; *** IMPORTANT: *** The value of the following configMAX_SYSCALL_INTERRUPT_PRIORITY ***MUST***
; match that defined in FreeRTOSConfig.h
configMAX_SYSCALL_INTERRUPT_PRIORITY:	.equ 0xA0

; -----------------------------------------------------------

vPortClearInterruptMask:
	push {r0}
 	mov r0, #0
 	msr basepri, r0
 	pop {r0}
 	bx r14
 ; -----------------------------------------------------------

vPortSetInterruptMask:
	push {r0}
	mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
	msr basepri, r0
	pop {r0}
	bx r14
; -----------------------------------------------------------

vPortPendSVHandler:

	mrs r0, psp						;  Load the task's stack pointer into R0.

	ldr	r3, curTCB				    ;  Load the address of pxCurrentTCB into R3, this is used on both sides of the context switch....
	ldr	r2, [r3]					;  Load the address of the TCB into R2.

	stmdb r0!, {r4-r11}				;  Store critical nesting and R4 - R11 onto the task's stack.
	str r0, [r2]					;  Save the new top of stack into the first member of the TCB.

	stmdb sp!, {r3, r14}			;  We want to maintain R3 and R14 (so we don't have to load the address of pxCurrentTCB into R3 again).

	mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY ;  Set to highest ISR which can make an API call to protect the data structures used by vTaskSwitchContext.
	msr basepri, r0                 ;  Now running higher priority.
	bl vTaskSwitchContext
	mov r0, #0 ;
	msr basepri, r0                 ;

	ldmia sp!, {r3, r14}			;  Pop R3 and R14 off the system stack.
									;  Restore the context. Instruction ordering designed for maximum speed.
	ldr r1, [r3]					;  R3 already holds the pxCurrentTCB address.  Use this to get the newly selected pxCurrentTCB address.
	ldr r0, [r1]					;  The first item in pxCurrentTCB is the task top of stack.

	ldmia r0!, {r4-r11}				;  Pop the registers that are not automatically saved on exception entry.

	msr psp, r0						;  Restore the task stack pointer.
	bx r14
; -----------------------------------------------------------

vPortSVCHandler:
	mrs r0, psp
	ldr	r3, curTCB		 			; Restore the context.
	ldr r1, [r3]					; Use pxCurrentTCB to get the Current TCB address.
	ldr r0, [r1]					; The first item in pxCurrentTCB is the task top of stack.
	ldmia r0!, {r4-r11}				; Pop the registers that are not automatically saved on exception entry and the critical nesting count.
	msr psp, r0						; Restore the task stack pointer.
	mov r0, #0
	msr	basepri, r0
	orr r14, #0xd
	bx r14
; -----------------------------------------------------------

vPortStartFirstTask:
	ldr r0, NVIC 			; Use the NVIC offset register to locate the stack.
	ldr r0, [r0]
	ldr r0, [r0]
	msr msp, r0				; Set the msp back to the start of the stack.
	cpsie i					; Globally enable interrupts.
	svc #0					; System call to start first task.
	nop
	bx r14					; Will never get here
; -----------------------------------------------------------

vHardFaultExt:
	tst	lr,#4
	ite	eq
	mrseq	r0,msp
	mrsne	r0,psp
	ldr	r1,[r0,#24]
	B prvGetRegistersFromStack
