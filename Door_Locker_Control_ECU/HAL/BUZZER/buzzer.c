/*
 * buzzer.c
 *
 *  Created on: May 24, 2023
 *      Author: user
 */

#include "buzzer.h"
#include "../../std_types.h"
#include "../../MCAL/GPIO/gpio.h"


void buzzerInit(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT );

}

void buzzerOn(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

void buzzerOff(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
