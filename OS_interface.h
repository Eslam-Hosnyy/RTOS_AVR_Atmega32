/****************************************/
/*	Author		: ESLAM_HOSNY			*/
/*	SWC			: SCHEDULER     		*/
/*	Layer		: MCAL					*/
/*	Version   	: 1.0					*/
/*	Date	  	: Jan 	19, 2022		*/
/*	Last Edit 	: N/A					*/
/****************************************/
#ifndef _OS_INTERFACE_H_
#define _OS_INTERFACE_H_

#define OS_STATE_ACTIVE		0
#define OS_STATE_SUSPAND	1

#define OS_NUMBER_OF_TASKS	255

void OS_voidStart(void);

u8 OS_u8CreateTask(void (*ARG_voidpHandeler)(void) ,u16 ARG_u16Periodicity, u8 ARG_u8Priority);

void OS_voidDeleteTask(u8 ARG_u8Priority);

u8 OS_voidSuspendTask(u8 ARG_u8Priority);

u8 OS_voidActiveTask(u8 ARG_u8Priority);

void OS_voidSchedular(void);


#endif
