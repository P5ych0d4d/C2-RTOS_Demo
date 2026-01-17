#ifndef LCD_MESSAGE_H
#define LCD_MESSAGE_H
#include "main.h"

typedef struct		// for message_communication in EXEC_MODE 1
{
	unsigned char x;
	unsigned char y;
	char *pcMessage;
} xOLEDMessage;

typedef struct		// for message_communication in EXEC_MODE 2
{
	unsigned char x;
	unsigned char y;
	char pcMessage[mainMAX_MSG_LEN];
} xOLEDMessageLong;
#endif /* LCD_MESSAGE_H */
