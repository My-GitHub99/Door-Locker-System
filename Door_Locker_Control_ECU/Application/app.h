/*
 * app.h
 *
 *  Created on: May 4, 2023
 *      Author: user
 */



#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_

#include "../common_macros.h" /* To use the macros like SET_BIT */
#include "../std_types.h"



void appInit(void);

void recievePassword(uint8 *newPassword,uint8 length);

uint8 comparePasswords(uint8 *,uint8 *,uint8 );

void savePassword(uint8*,uint8,uint16);

void triggerBuzzerAlarm(uint32 alarmTime);

void doorOpenSequence(void);

void sendInterfaceOrder(uint8 order);

uint8 recieveInterfaceStatus (void);

uint8 recieveUserRequest(void);

void getAccessPassword(uint8* password,uint8 length,uint16 u16addr);

void waitForHMI(void);

void sendControllerStatus(uint8 status);






#endif /* APPLICATION_APP_H_ */
