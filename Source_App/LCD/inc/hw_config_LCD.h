#ifndef __VCP_HW_CONFIG__
#define __VCP_HW_CONFIG__

#include <stdint.h>
#include "hw_ssi.h"
#include "hw_memmap.h"
#include "hw_sysctl.h"
#include "hw_types.h"
#include "debug.h"
#include "gpio.h"
#include "ssi.h"
#include "sysctl.h"
#include "ST7735.h"

//
// Hardware SPI if defined
#define LCD_TO_SPI1

// Can't be less 6 MGz according to datasheet on SR7755 controller
#define SPI2_BaudRatePrescaler   SPI_BaudRatePrescaler_2

// CS will be set every time before and and of operation
//#define LCD_SEL_AUTO

//#define 	LCD_GPIO			GPIOB

//#define     LCD_AHB1_GPIO		RCC_AHBPeriph_GPIOB
#ifdef LCD_1  // for self soldered LCD
#define 	LCD_RST_PIN 		GPIO_PIN_6	// PA6 (RST)
#define     LCD_DC_PIN			GPIO_PIN_4	// PA4 (DC)
#define		LCD_CS_PIN			GPIO_PIN_3	// PA3 (CS)
#else	// for AZ-Delivery_LCD
#define 	LCD_RST_PIN 		GPIO_PIN_6	// PA1 (RST)
#define     LCD_DC_PIN			GPIO_PIN_4	// PA4 (DC)
#define		LCD_CS_PIN			GPIO_PIN_3	// PA3 (CS)
#endif

// For software SPI only
#define		LCD_SDA_PIN			GPIO_PIN_5	// PA5 (SSITX)
#define		LCD_SCK_PIN			GPIO_PIN_2	// PA2 (SSICL)

// operate GPIO bits via GPIO function call for debug purposes
//#define NO_BITBIND

// The pin LCD_RST_PIN is not used if defined
//#define LCD_SOFT_RESET

/**************************** don't change anythings below *********************************/

#ifdef NO_BITBIND
#define LCD_RST1  GPIO_SetBits(GPIOB, LCD_RST_PIN)
#define LCD_RST0  GPIO_ResetBits(GPIOB, LCD_RST_PIN)

#define LCD_DC1   GPIO_SetBits(GPIOB, LCD_A0_PIN)
#define LCD_DC0   GPIO_ResetBits(GPIOB, LCD_A0_PIN)

#define LCD_CS1   GPIO_SetBits(GPIOB, LCD_CSE_PIN)
#define LCD_CS0   GPIO_ResetBits(GPIOB, LCD_CSE_PIN)

#else

#define LCD_RST1  GPIOPinWrite( GPIO_PORTA_BASE, LCD_RST_PIN, LCD_RST_PIN)			// GPIOA->BSRR = LCD_RST_PIN
#define LCD_RST0  GPIOPinWrite( GPIO_PORTA_BASE, LCD_RST_PIN, 0)			// GPIOA->BRR = LCD_RST_PIN

#define LCD_DC1   GPIOPinWrite( GPIO_PORTA_BASE, LCD_DC_PIN, LCD_DC_PIN)			// GPIOB->BSRR = LCD_DC_PIN
#define LCD_DC0   GPIOPinWrite( GPIO_PORTA_BASE, LCD_DC_PIN, 0)			// GPIOB->BRR = LCD_DC_PIN

#define LCD_CS1   GPIOPinWrite( GPIO_PORTA_BASE, LCD_CS_PIN, LCD_CS_PIN)			// GPIOB->BSRR = LCD_CS_PIN
#define LCD_CS0   GPIOPinWrite( GPIO_PORTA_BASE, LCD_CS_PIN, 0)			// GPIOB->BRR = LCD_CS_PIN
#endif


#ifndef LCD_TO_SPI1
#define LCD_SCK1  LCD_GPIO->BSRR = LCD_SCK_PIN
#define LCD_SCK0  LCD_GPIO->BRR = LCD_SCK_PIN

#define LCD_MOSI1 LCD_GPIO->BSRR = LCD_SDA_PIN
#define LCD_MOSI0 LCD_GPIO->BRR = LCD_SDA_PIN
#endif

extern void lcd7735_setupPins(void);
extern void lcd7735_sendbyte(const uint8_t cmd);
extern void lcd7735_senddata16(const uint16_t data);
extern void lcd7735_sendCmd(const uint8_t cmd);
extern void lcd7735_sendData(const uint8_t data);

//extern void receive_data(const uint8_t cmd, uint8_t *data, uint8_t cnt);

#endif /* __VCP_HW_CONFIG__ */

