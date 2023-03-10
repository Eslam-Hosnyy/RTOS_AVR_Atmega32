/****************************************/
/*	Author		: ESLAM_HOSNY			*/
/*	SWC			: SCHEDULER     		*/
/*	Layer		: MCAL					*/
/*	Version   	: 1.0					*/
/*	Date	  	: Jan 	19, 2022		*/
/*	Last Edit 	: N/A					*/
/****************************************/

#include "LSTD_types.h"
#include "LBIT_math.h"
#include "OS_private.h"
#include "OS_interface.h"
#include "MTIM_interface.h"
#include "MGIE_interface.h"

Task OS_SysTasks[OS_NUMBER_OF_TASKS]={0};
volatile u32 OS_u32TickCount=0;

void OS_voidStart(void)
{
	MTIIM_voidInit(MTIM_TIMER0, MTIM_CS_PRESCALER_1024, MTIM_MODE_CTC0, MTIM_HWPIN_DiSCONNECTED);
	MTIM_voidSetCallback(MTIM_INTERRUPT_T0_OCM,OS_voidSchedular);
	MTIM_voidEnableInterrupt(MTIM_INTERRUPT_T0_OCM);
	MGIE_voidEnableGIE();
	MTIM_voidSetOCR(MTIM_TIMER0,79,NO_CHANNELS);
	MTIM_voidStartTimer(MTIM_TIMER0);
	
}

u8	 OS_u8CreateTask(void (*ARG_voidpHandeler)(void) , u16 ARG_u16Periodicity, u8 ARG_u8Priority)
{
	u8 L_u8Rutern;
	if((ARG_u8Priority<=OS_NUMBER_OF_TASKS) && (0==OS_SysTasks[ARG_u8Priority].Handler))
	{
		OS_SysTasks[ARG_u8Priority].Handler=ARG_voidpHandeler;
		OS_SysTasks[ARG_u8Priority].Periodicity=ARG_u16Periodicity;
		OS_SysTasks[ARG_u8Priority].State=OS_STATE_ACTIVE;
		L_u8Rutern=0;
	}
	else
	{	
		L_u8Rutern=1;
	}
	
	return L_u8Rutern;
	
}

void OS_voidDeleteTask(u8 ARG_u8Priority)
{
	if((ARG_u8Priority<=OS_NUMBER_OF_TASKS))
	{
		OS_SysTasks[ARG_u8Priority].Handler=0;
		OS_SysTasks[ARG_u8Priority].Periodicity=0;
	}
}

u8	 OS_voidSuspendTask(u8 ARG_u8Priority)
{
	u8 L_u8Rutern;
	if((ARG_u8Priority<=OS_NUMBER_OF_TASKS) && (0!=OS_SysTasks[ARG_u8Priority].Handler))
	{
		OS_SysTasks[ARG_u8Priority].State=OS_STATE_SUSPAND;
		L_u8Rutern=0;
	}
	else
	{	
		L_u8Rutern=1;
	}
	
	return L_u8Rutern;
}

u8	 OS_voidActiveTask(u8 ARG_u8Priority)
{
	u8 L_u8Rutern;
	if((ARG_u8Priority<=OS_NUMBER_OF_TASKS) && (0!=OS_SysTasks[ARG_u8Priority].Handler))
	{
		OS_SysTasks[ARG_u8Priority].State=OS_STATE_ACTIVE;
		L_u8Rutern=0;
	}
	else
	{	
		L_u8Rutern=1;
	}
	
	return L_u8Rutern;
}

void OS_voidSchedular(void)
{
	u8 L_u8Iter;
	OS_u32TickCount++;
	for(L_u8Iter=0; L_u8Iter<OS_NUMBER_OF_TASKS; L_u8Iter++)
	{
		if(OS_STATE_ACTIVE == OS_SysTasks[L_u8Iter].State)
		{
			if(0==(OS_u32TickCount % OS_SysTasks[L_u8Iter].Periodicity))
			{
				OS_SysTasks[L_u8Iter].Handler();
			}
		}
	}
	
}
