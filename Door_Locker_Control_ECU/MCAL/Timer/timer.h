/*
 * timer.h
 *
 *  Created on: May 4, 2023
 *      Author: user
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_



#include"../../std_types.h"
#include"../../common_macros.h"


/*--------------------->Structures and enumerations definitions<-------------------------- */



/* Enumeration to select the timer mode */
typedef enum TimerModeSelect
{
	NORMAL,COMPARE
}TimerModeSelect;


/*Enumeration to select the timer clock */
typedef enum TimerClockSelect
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}TimerClockSelect;

/* Timer module Configuration structure */
typedef struct TimerConfig
{
	TimerModeSelect mode;     /* To select the timer mode which is normal or compare */
	uint16 initialValue;      /* To initialize the timer */
	TimerClockSelect clock;   /* To select the timer prescaler */
	uint16 compareValue;      /* To initialize the compare register by compare value */
}TimerConfig;

/*---------------------------->Public functions prototypes<------------------------------*/
void Timer0_PWM_Init(uint8 DutyCycle);
void Timer_init(const TimerConfig*);
void Timer_deInit(void);
void Timer1_setCallBack(void(*a_Ptr)());



#endif /* MCAL_TIMER_TIMER_H_ */
