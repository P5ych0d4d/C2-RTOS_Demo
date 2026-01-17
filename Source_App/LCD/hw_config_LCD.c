/****************************************************************************************
*
* Hardware configuration and low level functions
*
* The idea of HW initialization and configuration have taken on from
* http://vg.ucoz.ru/load/stm32_ickhodnye_teksty_programm_na_si/stm32_biblioteka_podkljuchenija_displeja_na_kontrollere_st7735_dlja_stm32f4/16-1-0-41
****************************************************************************************/
#include <stdio.h>

#include "hw_config_LCD.h"
//#define ulSSI_FREQUENCY						( 3500000UL )
#define ulFrequency						( 4000000UL )


//static __IO uint32_t TimingDelay;

//SPI_TypeDef * SPI_Module;

// Send byte via SPI to controller
void lcd7735_sendbyte(const uint8_t data) {
#ifdef LCD_TO_SPI1
    unsigned long ulTemp;

    //
    // Write the next byte to the controller.
    //
    SSIDataPut(SSI0_BASE, data);

    //
    // Dummy read to drain the fifo and time the GPIO signal.
    //
    SSIDataGet(SSI0_BASE, &ulTemp);

	// now Transmit Buffer Empty
#else
    unsigned char i;
    for(i=0; i<8; i++) {
        if (data & 0x80) LCD_MOSI1;
        else LCD_MOSI0;
        data = data<<1;
        LCD_SCK0;
        LCD_SCK1;
    }
#endif
}


/* Send byte via SPI to controller
void lcd7735_senddata16(const uint16_t data) {
#ifdef LCD_TO_SPI1
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);
#else
    lcd7735_senddata(data >> 8);
    lcd7735_senddata(data &0xFF);
#endif
}
*/

// Send control command to controller
void lcd7735_sendCmd(const uint8_t cmd) {
    LCD_DC0;
    lcd7735_sendbyte(cmd);
    //spi_writeByte(cmd);
#ifdef LCD_TO_SPI2
    while(SPI2->SR & SPI_SR_BSY);
#endif
}

// Send parameters o command to controller
void lcd7735_sendData(const uint8_t data) {
    LCD_DC1;
    lcd7735_sendbyte(data);
    //spi_writeByte(data);
#ifdef LCD_TO_SPI2
    while(SPI2->SR & SPI_SR_BSY);
#endif
}

void spi_init(void)
{
    unsigned long ulTemp;

    //
    // Enable the SSI0 and GPIO port blocks as they are needed by this driver.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the SSI0CLK and SSIOTX pins for SSI operation.
    //
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_5);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_5,
                     GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);


    //
    // Configure and enable the SSI0 port for master mode.
    //
    //RIT128x96x4Enable(ulFrequency);
    //
	// Disable the SSI port.
	//
	SSIDisable(SSI0_BASE);

	//
	// Configure the SSI0 port for master mode.
	//
	SSIConfig(SSI0_BASE, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, ulFrequency, 8);

	//
	// (Re)Enable SSI control of the FSS pin.
	//
	GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_3);
	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_STRENGTH_8MA,
					 GPIO_PIN_TYPE_STD_WPU);

	//
	// Enable the SSI port.
	//
	SSIEnable(SSI0_BASE);
    //
    // Drain the receive fifo.
    //
    while(SSIDataNonBlockingGet(SSI0_BASE, &ulTemp) != 0)
    {
    }


}

// Init hardware
void lcd7735_setupPins(void) {


	spi_init();

    //
    // Configure the GPIO port pin used as a D/CE/RES signal for LCD,
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LCD_RST_PIN | LCD_CS_PIN | LCD_DC_PIN);
    GPIOPadConfigSet(GPIO_PORTA_BASE, LCD_RST_PIN | LCD_CS_PIN | LCD_DC_PIN,
                     GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
    // all non-Pins to high ???
    GPIOPinWrite(GPIO_PORTA_BASE, LCD_RST_PIN | LCD_CS_PIN | LCD_DC_PIN, LCD_RST_PIN | LCD_CS_PIN | LCD_DC_PIN);
}

