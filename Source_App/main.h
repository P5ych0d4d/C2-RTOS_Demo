#define timerTIMER_1_COUNT_VALUE		( * ( ( unsigned long * ) ( TIMER1_BASE + 0x48 ) ) )

/* Size of the stack allocated to the uIP task. */
#define mainBASIC_WEB_STACK_SIZE            ( configMINIMAL_STACK_SIZE * 4 )

/* The OLED task uses the sprintf function so requires a little more stack too. */
#define mainOLED_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 50 )

/* Dimensions the buffer into which the jitter time is written. */
#define mainMAX_MSG_LEN						25

/* Constants used when writing strings to the display. */
#define mainCHARACTER_HEIGHT				( 9 )
#define mainMAX_ROWS_128					( mainCHARACTER_HEIGHT * 14 )
#define mainMAX_ROWS_96						( mainCHARACTER_HEIGHT * 10 )
#define mainMAX_ROWS_64						( mainCHARACTER_HEIGHT * 7 )
#define mainFULL_SCALE						( 15 )
#define ulSSI_FREQUENCY						( 3500000UL )

xTaskHandle xOLED_Handle;

#define Oszi_ON 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 1);							// added by JH for Test_OSZI_signal
#define Oszi_OFF 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 0);							// added by JH for Test_OSZI_signal

// *********** Funktionsprototypen **************************************
/**
 * @brief
 *
 * Referenz zur uIP-Funktion
 *
 * @author Jan Rothkegel
 * siehe WebServer/uIP_Task.c
 */
extern void vuIP_Task( void *pvParameters );

extern void hw_Init( void );

void vOLEDTask( void *pvParameters );

void prvSetupHardware( void );


