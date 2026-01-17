/**
 * \addtogroup Praktikumsdokumente
 *
 * @{
 *
 * @file hw_api.c
 *
 * Diese Datei enthält die gekapselte Logik für die Hardwareansteuerung.
 *
 * @date 04.04.2010
 * @author Jan Rothkegel
 * modified by JH, 11/07/19
 * modified by JH, 11/08/16	Port-Umwidmung
 * modified by JH, 11/08/23 Select_Switch_Setup
 * modified by JH, 11/08/25 hw_SetPulseWidth() mit Eingabebereich von 0...1000
 * modified by JH, 11/09/02 UART_init
 * modified by JH, 11/09/14 PC5_init für USER-LED
 *******************************************************************************/

/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hw_types.h"
#include "gpio.h"
#include "pwm.h"
#include "hw_memmap.h"
#include "sysctl.h"
#include "adc.h"
#include "hw_ints.h"
#include "uart.h"
#include "interrupt.h"

//void hw_SetFrequency( long FreqHz );
void hw_SetPulseWidth( long WidthPercentage );
void hw_SetBridge( int Bridge1_State, int Bridge2_State, int Bridge3_State );

extern void CommutationControl(void);
extern void CurrentDetection(void);

/*-----------------------------------------------------------*/

long hw_ulPeriod = 0;
long hw_PulseWidth = 0;
int hw_Bridge1 = 0;
int hw_Bridge2 = 0;
int hw_Bridge3 = 0;
int hw_InvertSignals = false;


/*-----------------------------------------------------------*/

/**
 * @brief
 *
 * Invertiert die Signale
 *
 * Das Invertieren der Signale dient vor allem der Richtungsumkehr von Spannung und Strom ohne die weiteren
 * Ansteuerungskomponenten modifizieren zu muessen.
 *
 * @param TrueFalse Mit "true" werden die Signale invertiert.
 *
 */

void hw_Invert(int TrueFalse)
{
	hw_InvertSignals = TrueFalse;
}

/**
 * @brief
 *
 * Setzen der PWM-Frequenz
 *
 * Gemeint ist hier die Periodendauer eines PWM-Taktes, dessen Tastverhaeltnis durch hw_SetPulseWidth()
 * geaendert werden kann.
 *
 * \sa hw_SetPulseWidth()
 *
 * @param FreqHz Frequenz in Hz
 */
/*
void hw_SetFrequency( long FreqHz )
{
	hw_ulPeriod = SysCtlClockGet() / FreqHz;

	hw_SetBridge( hw_Bridge1, hw_Bridge2, hw_Bridge3 );
}
*/
/**
 * @brief
 *
 * Setzen des Tastverhältnisses
 *
 * Unabhaengig von der Grundperiode des PWM-Signals kann durch diese Funktion das Tastverhaeltnis
 * eingestellt werden.
 *
 * @param WidthPercentage Tastverhältnis in Promille, 0...1000
 */
void hw_SetPulseWidth( long WidthPercentage )
{
	/* Umrechnen in Takte */
	hw_PulseWidth = abs(WidthPercentage) * (hw_ulPeriod / 1000);   // auf div. by 1000 geaendert, um feiner Stufung der Stellgr. zu erhalten


	/* Begrenzen auf hoechstens 100% */
	if (abs(WidthPercentage) >= 1000)
	{
		hw_PulseWidth=hw_ulPeriod-1;
	}

	/* Invertieren der Ausgaenge bei negativen Tastverhaeltnissen */
	if (WidthPercentage < 0)
	{
		hw_Invert(true);
	}
	else
	{
		hw_Invert(false);
	}

	/* Aktualisieren der Ausgaenge */
	hw_SetBridge(hw_Bridge1, hw_Bridge2, hw_Bridge3 );

	/* Bei Tastverhaeltnis Null werden PWM Signale deaktiviert */
	if (WidthPercentage == 0)
	{
		PWMOutputState(PWM_BASE, PWM_OUT_3_BIT, false);
		PWMOutputState(PWM_BASE, PWM_OUT_4_BIT, false);
		PWMOutputState(PWM_BASE, PWM_OUT_5_BIT, false);
	}

}

/**
 * @brief
 *
 * Setzen der einzelnen Brueckenzweige
 *
 * Es koennen die folgenden Zustaende eingenommen werden:
 *
 * 	(-1) Schalten auf Masse <br>
 *  (0)  Hochohmig machen <br>
 *  (+1) Schalten auf Vcc <br>
 *
 * @param Bridge1_State Zustand von Brücke 1
 * @param Bridge2_State Zustand von Brücke 2
 * @param Bridge3_State Zustand von Brücke 3
 *
 */

void hw_SetBridge( int Bridge1_State, int Bridge2_State, int Bridge3_State )
{

    // ff->niederohmig

	/* Speichern der Konfiguration */
	hw_Bridge1 = Bridge1_State;
	hw_Bridge2 = Bridge2_State;
	hw_Bridge3 = Bridge3_State;

	/* Umkehren der Zustaende bei Invertierung */
	if (hw_InvertSignals==true)
	{
		Bridge1_State = -Bridge1_State;
		Bridge2_State = -Bridge2_State;
		Bridge3_State = -Bridge3_State;
	}


	/* Zunaechst alle Massekontakte eliminieren */
	GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
//	GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, 0x00);
	GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);			// mod. by JH
	GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_6, 0x00);

	/* Wenn das Tastverhaeltnis ungleich Null ist */
	if (hw_PulseWidth!=0)
	{
		/* PWM-Signale erzeugen */

		// Bridge1
		// Output PWM4
		PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, hw_ulPeriod);
		if (Bridge1_State == 1)
		{
			PWMPulseWidthSet(PWM_BASE, PWM_OUT_4, hw_PulseWidth);
			PWMOutputState(PWM_BASE, PWM_OUT_4_BIT, true);
		}
		if (Bridge1_State == -1 || Bridge1_State == 0)
		{
			PWMPulseWidthSet(PWM_BASE, PWM_OUT_4, 1);
			PWMOutputState(PWM_BASE, PWM_OUT_4_BIT, false);
		}

		// Bridge 2 und 3 nicht vertauschen!!!

		//Bridge2
		//Output PWM3
		PWMGenPeriodSet(PWM_BASE, PWM_GEN_1, hw_ulPeriod);
		if (Bridge2_State == 1)
		{
			PWMPulseWidthSet(PWM_BASE, PWM_OUT_3, hw_PulseWidth);
			PWMOutputState(PWM_BASE, PWM_OUT_3_BIT, true);
		}
		if (Bridge2_State == -1 || Bridge2_State == 0)
		{
			PWMPulseWidthSet(PWM_BASE, PWM_OUT_3, 1);
			PWMOutputState(PWM_BASE, PWM_OUT_3_BIT, false);
		}

		// Bridge 2 und 3 nicht vertauschen!!!
		// Bridge3
		// Output PWM5
		PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, hw_ulPeriod);
		if (Bridge3_State == 1)
		{
			PWMPulseWidthSet(PWM_BASE, PWM_OUT_5, hw_PulseWidth);
			PWMOutputState(PWM_BASE, PWM_OUT_5_BIT, true);
		}
		if (Bridge3_State == -1 || Bridge3_State == 0)
		{
			PWMPulseWidthSet(PWM_BASE, PWM_OUT_5, 1);
			PWMOutputState(PWM_BASE, PWM_OUT_5_BIT, false);
		}


		/* Durchschalten des richtigen GPIOs auf Masse */

		// Bridge1
		if (Bridge1_State == 0 || Bridge1_State == 1)
		{
			//GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
		}
		if (Bridge1_State == -1)
		{
			GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_5, 0x20); // oder 0xff
		}

		// Bridge2
		if (Bridge2_State == 0 || Bridge2_State == 1)
		{
			//GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, 0x00);
		}
		if (Bridge2_State == -1)
		{
			GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);	// oder 0xff mod. by JH
		}

		// Bridge3
		if (Bridge3_State == 0 || Bridge3_State == 1)
		{
			//GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_6, 0x00);
		}
		if (Bridge3_State == -1)
		{
			GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_6, 0x40); // oder 0xff
		}
	}else
	{
		;	// für hw_PulseWidth == 0
	}
}

/**
 * @brief
 *
 * Initialisierung der Hardware-Schnittstellen
 *
 * Im Zuge der Hardware-Initialisierung wird diese Routine aufgerufen, um die anwendungsspezifischen
 * Hardware-Einheiten zu konfigurieren. Dazu zaehlen ADC, PWM und GPIOs.
 *
 */
void hw_Init( void )
{
	/* Speichern initialer PWM-Werte */
	hw_ulPeriod = SysCtlClockGet() / 10000;				// bei 50MHz werden das 5000, f_pwm = 10kHz
	hw_PulseWidth = 1;

	// ADC0 aktivieren, für Ub-Messung, internal U_ref = 3V, 10Bit, --> 2.93 mV/Bit
    SysCtlADCSpeedSet(SYSCTL_ADCSPEED_125KSPS);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
	ADCSequenceConfigure(ADC_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);  // sequenz_number 0
	ADCSequenceStepConfigure(ADC_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
	ADCSequenceEnable(ADC_BASE, 0);
	ADCIntClear(ADC_BASE, 0);  // added by JH
	/* ADC1 aktivieren 								// added by JH, internal U_ref = 3V, 10Bit, --> 2.93 mV/Bit
	ADCSequenceConfigure(ADC_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);  // sequenz_number 3, single sample
	ADCSequenceStepConfigure(ADC_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH1);
	ADCSequenceEnable(ADC_BASE, 3);   */


	/* Verwendete Hardware-Ports aktivieren */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	/* Konfiguration der Sensoreingaenge */
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_7);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4);
	// Die integrierten pullups sind für die HALL-Ausgaenge zu groß!
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_4, 0, GPIO_PIN_TYPE_STD_WPU);  // 2,7k gefordert, Pullup = 50...110k
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_7, 0, GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_4, 0, GPIO_PIN_TYPE_STD_WPU);
	// INT-Prio für HALL-Signale anpassen
	IntPrioritySet( INT_GPIOB, 1 );				// added by JH to minimize the jitter
	IntPrioritySet( INT_GPIOD, 1 );

	/* Konfiguration der Interrupts für Sensoraenderung */
	GPIOPortIntRegister(GPIO_PORTD_BASE, CommutationControl);
	GPIOPortIntRegister(GPIO_PORTB_BASE, CommutationControl);
	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_BOTH_EDGES);
	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_BOTH_EDGES);
	GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_BOTH_EDGES);
	GPIOPinIntEnable(GPIO_PORTD_BASE, GPIO_PIN_4);
	GPIOPinIntEnable(GPIO_PORTD_BASE, GPIO_PIN_7);
	GPIOPinIntEnable(GPIO_PORTB_BASE, GPIO_PIN_4);

	// Konfiguration des Ueberstrom-Interrupts	// mod. by JH, von PA0 auf PC4 verlegt
	GPIOPortIntRegister(GPIO_PORTC_BASE, CurrentDetection);
	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	// pull_up ist notwendig, da Transistor ihn als R_L benoetigt
	GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);   // mod. by JH, only H/L-edge
	GPIOPinIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4);

	/* Setze PWM-Clock auf Systemtakt */
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	/* Aktiviere PWM-Ports */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);

	/*
	 * Wichtig: Dieser Befehl sorgt für Deaktivierung der PWM-Ports beim Debuggen!
	 * 			Das ist noetig um Kurschluesse zu verhindern!
	 */
	PWMOutputFault(PWM_BASE, PWM_OUT_0_BIT | PWM_OUT_3_BIT | PWM_OUT_4_BIT | PWM_OUT_5_BIT, true);

	/* Konfigurieren von PWM0 für Oszilloskop-Ausgabe */
	long ulPeriod_Osci = 0;
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);
	ulPeriod_Osci = SysCtlClockGet() / 7000000;   // 5000000 are 9 steps, aber leichte Welligkeit
	PWMGenConfigure(PWM_BASE, PWM_GEN_0,
					PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM_BASE, PWM_GEN_0, ulPeriod_Osci);
	PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, 1);								// in der DA: PWM_BASE, PWM_OUT_0, 1);
	PWMOutputState(PWM_BASE, PWM_OUT_0_BIT, true);
	PWMGenEnable(PWM_BASE, PWM_GEN_0);

	/*
	 * Bridge1 setzen
	 */

	// PB5
	GPIODirModeSet( GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT );
    GPIOPadConfigSet( GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );
    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);

    // PWM4
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_0);
	PWMGenConfigure(PWM_BASE, PWM_GEN_2,
						PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, hw_ulPeriod);
	PWMPulseWidthSet(PWM_BASE, PWM_OUT_4, 1);
	PWMOutputState(PWM_BASE, PWM_OUT_4_BIT, true);
	PWMGenEnable(PWM_BASE, PWM_GEN_2);

	/*
	 * Bridge2 setzen
	 */

	// PB2																						mod. by JH
	GPIODirModeSet( GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT );
	GPIOPadConfigSet( GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );
	GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);

	// PWM3
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_1);
	PWMGenConfigure(PWM_BASE, PWM_GEN_1,
						PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM_BASE, PWM_GEN_1, hw_ulPeriod);
	PWMPulseWidthSet(PWM_BASE, PWM_OUT_3, 1);
	PWMOutputState(PWM_BASE, PWM_OUT_3_BIT, true);
	PWMGenEnable(PWM_BASE, PWM_GEN_1);

	/*
	 * Bridge3 setzen
	 */

	// PB6
	GPIODirModeSet( GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_DIR_MODE_OUT );
	GPIOPadConfigSet( GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );
	GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_6, 0x00);

	// PWM5
	GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_1);
	PWMGenConfigure(PWM_BASE, PWM_GEN_2,
						PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, hw_ulPeriod);
	PWMPulseWidthSet(PWM_BASE, PWM_OUT_5, 1);
	PWMOutputState(PWM_BASE, PWM_OUT_5_BIT, true);
	PWMGenEnable(PWM_BASE, PWM_GEN_2);


	// PD0 for OSZI_pulse_signal, located on LCD_chassis					// added by JH
	GPIODirModeSet( GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_DIR_MODE_OUT );
    GPIOPadConfigSet( GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );
    GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 0x00);

    // Configure the GPIOs used to read the state of the on-board push buttons.
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    // PF1 for Select-Switch
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,
                         GPIO_PIN_TYPE_STD_WPU);

	// PC5  for user_LED
	GPIODirModeSet( GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT );
	GPIOPadConfigSet( GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );
	GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, 0x00);


    /* Configure the first UART for 115,200, 8-N-1 operation.
    //
	// Enable peripheral, other fault is generated
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	// Configure the Port A, pins 0,1 appropriately.
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    UARTEnable(UART0_BASE);
	*/
    IntMasterEnable();
}

void StopSystem()
{
	/* Deaktivieren der Interrupts */
	GPIOPinIntDisable(GPIO_PORTD_BASE, GPIO_PIN_4);
	GPIOPinIntDisable(GPIO_PORTD_BASE, GPIO_PIN_7);
	GPIOPinIntDisable(GPIO_PORTB_BASE, GPIO_PIN_4);

	/* Schaltbrücke hochohmig machen */
	hw_SetBridge( 0, 0, 0 );
}
/*-----------------------------------------------------------*/
//! @}
