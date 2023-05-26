/*
 * buzzer.h
 *
 *  Created on: May 24, 2023
 *      Author: user
 */

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

#include "../../std_types.h"
#include  "../../MCAL/GPIO/gpio.h" /* for using the file's macro's to identify the motor's pins and ports*/


#define BUZZER_PORT_ID PORTB_ID
#define BUZZER_PIN_ID  PIN0_ID


void buzzerInit(void);
void buzzerOn(void);
void buzzerOff(void);

#endif /* HAL_BUZZER_BUZZER_H_ */
