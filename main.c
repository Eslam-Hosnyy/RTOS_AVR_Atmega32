/************************************/
/*	Author		: Eslam_Hosny		*/
/*	SWC			: N/A				*/
/*	Layer		: N/A				*/
/*	Version   	: 0.0				*/
/*	Date	  	: N/A				*/
/*	Last Edit 	: N/A				*/
/************************************/
#define F_CPU	8000000UL
#include <util/delay.h>
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MDIO_interface.h"
#include "PORT_interface.h"
#include "MTIM_interface.h"
#include "MGIE_interface.h"
#include "OS_interface.h"

void LED1(void);
void LED2(void);

int main(void)
{
	PORT_voidInit();


	OS_u8CreateTask(LED1, 100, 1);
	OS_u8CreateTask(LED2, 50, 2);

	OS_voidStart();
	while(1)
	{


	}
	return 0;
}
void LED1(void)
{
	static volatile u8 Flag=0;
	if(0==Flag)
	{
		MDIO_u8SetPinValue(MDIO_PORTA, 0, MDIO_HIGH);
		Flag=1;
	}
	else
	{
		MDIO_u8SetPinValue(MDIO_PORTA, 0, MDIO_LOW);
		Flag=0;
	}
}

void LED2(void)
{
	static volatile u8 Flag=0;
	if(0==Flag)
	{
		MDIO_u8SetPinValue(MDIO_PORTA, 1, MDIO_HIGH);
		Flag=1;
	}
	else
	{
		MDIO_u8SetPinValue(MDIO_PORTA, 1, MDIO_LOW);
		Flag=0;
	}
}
