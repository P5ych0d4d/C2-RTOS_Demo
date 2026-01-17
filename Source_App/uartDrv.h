/*
 * uartDrv.h
 *
 *  Created on: 05.05.2022
 *      Author: huhle
 */

#ifndef APPSOURCE_UARTDRV_H_
#define APPSOURCE_UARTDRV_H_

#include <stdbool.h>

extern void InitConsole(void);
unsigned long SerialReceiveAvailable();
extern bool UARTSend(unsigned char *, unsigned long );
extern long UARTReceive(unsigned char *, unsigned long );

#endif /* APPSOURCE_UARTDRV_H_ */
