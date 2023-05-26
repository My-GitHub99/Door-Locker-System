/*
 * motor.h
 *
 *  Created on: Apr 3, 2023
 *      Author: ahmed bahaa
 */

#ifndef HAL_MOTOR_MOTOR_H_
#define HAL_MOTOR_MOTOR_H_

#include "../../std_types.h"
#include  "../../MCAL/GPIO/gpio.h" /* for using the file's macro's to identify the motor's pins and ports*/

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_IN1_PORT      PORTC_ID
#define MOTOR_IN1_PIN       PIN4_ID
#define MOTOR_IN2_PORT      PORTC_ID
#define MOTOR_IN2_PIN       PIN5_ID
#define MOTOR_EN_PORT       PORTB_ID
#define MOTOR_EN_PIN        PIN3_ID

/*******************************************************************************
 *                              Type Definitions                                  *
 *******************************************************************************/
typedef enum DcMotor_State{
	MOTOR_OFF,MOTOR_ON_CW,MOTOR_ON_CCW
}DcMotor_State;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*Description
➢ The Function responsible for setup the direction for the two motor pins through the GPIO driver.
➢ Stop at the DC-Motor at the beginning through the GPIO driver.*/

void DcMotor_Init(void);

/*Description:
➢ The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
➢ Send the required duty cycle to the PWM driver based on the required speed value.*/

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* HAL_MOTOR_MOTOR_H_ */
