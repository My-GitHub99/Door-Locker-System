/*
 * app.h
 *
 *  Created on: May 4, 2023
 *      Author: user
 */

/*the HMI ECU Tasks
 * display new password sequency on HMI
 * send newpassword to control ECU
 * display the system options
 * */

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_

#include "../common_macros.h" /* To use the macros like SET_BIT */
#include "../std_types.h"

typedef enum Password_Status
{
	MATCH,NOT_MATCH,INCORRECT_FORMAT
};


void appInit(void);

void getNewPassword(uint8 *password,uint8 *reenterted_password,uint8 length);

void sendPasswordToController(uint8 *password,uint8 length);

void displaySystemOptions(void);

uint8 recieveControllerDecision(void);

void displayPasswordCompareError(void);

void StatusAck (uint8 status);

void displayPasswordFormatError(void);

void displayPasswordChanged(void);

void displayDoorState(void);

uint8 getUserRequest(void);

void sendRequestToController(uint8 request);

void getEnterPassword(uint8* password,uint8 length);

void sendHMIStatus(uint8);

void waitForController(void);

void displaySecurityAlarm(void);


#endif /* APPLICATION_APP_H_ */
