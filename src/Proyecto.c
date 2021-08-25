/*
===============================================================================
 Name        : Project_LPCOpen.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
int estado=0;
uint16_t paso=0; //paso max
uint16_t f=0; //funcion
uint16_t amplit=0; //amplitud max
uint16_t n=0; //para cargar el vector n

// TODO: insert other include files here
#include "sapi_dac.h"
#include "sapi_gpio.h"
#include "sapi_rit.h"
#include "sapi_systick.h"
// TODO: insert other definitions and declarations here
// TODO: insert other definitions and declarations here
uint16_t sen[10]={510,812,997,812,512,211,25,23,210,510};
int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    Init_Tick(100000);
    dacInit(DAC_ENABLE);

    gpioInit(0,8,GPIO_INPUT); //inicializo entradas
    gpioInit(0,7,GPIO_INPUT);
    gpioInit(0,6,GPIO_INPUT);
    gpioInit(0,2,GPIO_INPUT);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {

    	if(gpioRead(0,6) == 1){estado=1;}
    	if(gpioRead(0,7) == 1){estado=2;}
    	if(gpioRead(0,8) == 1){estado=3;}
    	if(gpioRead(0,2) == 1){estado=4;}

    	dacWrite(0 , sen[n]);

    	switch (estado)
		{
		case 1://funcion 3.3 10K
		   amplit=1023;
		   paso=102;
		   Init_Tick(100000);
		   estado=0;
			break;
		case 2://funcion 1.65 10K
			amplit=511;
			paso=51;
			Init_Tick(100000);
			estado=0;
			break;
		case 3://funcion 3.3 1K
			amplit=1023;
			paso=102;
			Init_Tick(10000);
			estado=0;
			break;
		case 4://funcion 1.65 1K
			amplit=511;
			paso=51;
			Init_Tick(10000);
			estado=0;
			break;
		}

        i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");


    }
    return 0 ;
	}

/*void SysTick_Handler(void)
{
        if(f>=amplit){f=0;}
        f=f+paso;
        dacWrite( 0,f);
 }*/
void SysTick_Handler(void)
{
	if (n<10)
	{n++;}
	else {n=0;}

}
