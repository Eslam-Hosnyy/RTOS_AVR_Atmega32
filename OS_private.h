/****************************************/
/*	Author		: ESLAM_HOSNY			*/
/*	SWC			: SCHEDULER     		*/
/*	Layer		: MCAL					*/
/*	Version   	: 1.0					*/
/*	Date	  	: Jan 	19, 2022		*/
/*	Last Edit 	: N/A					*/
/****************************************/
#ifndef _OS_PRIVATE_H_
#define _OS_PRIVATE_H_

typedef struct
{
	void (*Handler)(void);
	u16	 Periodicity;
	u8	 State;
	u8	 FirstDelay;
	
}Task;



#endif