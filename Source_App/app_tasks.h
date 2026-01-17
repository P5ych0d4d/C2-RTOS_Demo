/**
 * \addtogroup Praktikumsdokumente
 *
 * @file app_tasks.h
 *
 * Definiert Queues global und macht die Tasks bekannt
 *
 * @date 04.04.2010
 * @author Jan Rothkegel
 * modified by JH, 22/08/18
 */

#ifndef APP_TASKS_H_

#define APP_TASKS_H_

//Queues provided for process communication
xQueueHandle xPulseWidthQueue;		// Quelle: Task vSpeed_Control()				Senke: WEB-Interface
xQueueHandle xVoltageQueue;			// Quelle: Task vVoltage_Supervisor()			Senken: WEB-Interface, Peek in vSpeed_Control()
xQueueHandle xSpeedQueue;			// Quelle: Task vSpeed_Control()				Senke: WEB-Interface
xQueueHandle xNominalSpeedQueue;	// Quellen: WEB-Interface,vVoltage_Supervisor	Senke: Task vSpeed_Control()
xQueueHandle xTimeConstantQueue;	// Quelle: WEB-Interface						Senke: Task vSpeed_Control()
extern xQueueHandle xOLEDQueue;		// Quellen: alle die etwas wissen				Senke: Task vOLEDTask()


void SetupProcessCommunication();
void CommutationControlEx( long CommutationOffset );
void CommutationControl(void);
void vBlock_Task( void *pvParameters );
void vSpeed_Control( void *pvParameters );
void vVoltage_Supervisor( void *pvParameters );
//void RunStartSequence( long Direction);
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void vTask3( void *pvParameters );
void vTask4( void *pvParameters );
void vDemo_Task1( void *pvParameters );
void vDemo_Task2( void *pvParameters );
void vDemo_Task3( void *pvParameters );

#define Oszi_ON 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 1);							// added by JH for Test_OSZI_signal
#define Oszi_OFF 	 GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_0, 0);							// added by JH for Test_OSZI_signal

#endif /* APP_TASKS_H_ */
