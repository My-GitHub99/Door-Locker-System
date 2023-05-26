/*
 * motor.c
 *
 *  Created on: Apr 3, 2023
 *      Author: ahmed bahaa
 *      Driver Used: PWM,GPIO
 */
#include  "../../MCAL/GPIO/gpio.h"
#include  "../../MCAL/Timer/timer.h"
#include "../../std_types.h"
#include  "motor.h"



void DcMotor_Init(void)
{

	GPIO_setupPinDirection(MOTOR_EN_PORT ,MOTOR_EN_PIN ,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN1_PORT ,MOTOR_IN1_PIN ,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN2_PORT ,MOTOR_IN2_PIN ,PIN_OUTPUT);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	switch(state)
	{
	case MOTOR_OFF:
		GPIO_writePin(MOTOR_IN1_PORT ,MOTOR_IN1_PIN ,LOGIC_HIGH);
		GPIO_writePin(MOTOR_IN2_PORT ,MOTOR_IN2_PIN ,LOGIC_HIGH);
		break;
	case MOTOR_ON_CW:
		GPIO_writePin(MOTOR_IN1_PORT ,MOTOR_IN1_PIN ,LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT ,MOTOR_IN2_PIN ,LOGIC_HIGH);
		break;
	case MOTOR_ON_CCW:
		GPIO_writePin(MOTOR_IN1_PORT ,MOTOR_IN1_PIN ,LOGIC_HIGH);
		GPIO_writePin(MOTOR_IN2_PORT ,MOTOR_IN2_PIN ,LOGIC_LOW);
		break;
	}
	if(state==MOTOR_ON_CW ||state==MOTOR_ON_CCW  )
	{
	    speed=((uint32)speed*255UL)/100; /* mapping 0->100 duty cycle to be between 0->256*/
	    if(speed<0 || speed>255)
	    {
	    	/* do nothing*/
	    }
	    else
	    {
	    Timer0_PWM_Init(speed);
	    }
	}

	else
	{
		/* do nothing*/
	}
}
