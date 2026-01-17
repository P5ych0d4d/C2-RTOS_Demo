
extern void hw_Init( void );
extern void hw_SetBridge( int , int , int );
extern void hw_SetPulseWidth( long WidthPercentage );
extern void StopSystem();

/* Variablen zur Speicherung der Magnetfeld-Daten */
int HallA = 0;
int HallB = 0;
int HallC = 0;

/* Struktur zur Aufnahme der Kommutierungssequenz */
typedef struct CommutationElement
{
	int Bridge1;
	int Bridge2;
	int Bridge3;
	int HallA;
	int HallB;
	int HallC;
} CommutationElement;

/* Kommutierungssequenz als Array */
CommutationElement CommutationSequence[6]= {{  1, -1,  0,  1,  1,  0},
											{  1,  0, -1,  1,  0,  0},
											{  0,  1, -1,  1,  0,  1},
											{ -1,  1,  0,  0,  0,  1},
											{ -1,  0,  1,  0,  1,  1},
											{  0, -1,  1,  0,  1,  0}};
