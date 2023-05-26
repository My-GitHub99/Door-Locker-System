/*
 * main.c
 *
 *  Created on: Apr 3, 2023
 *      Author: user
 */


#include "Application/app.h"
#include <util/delay.h> /* For the delay functions */
#include "MCAL/UART/uart.h"

#define PASSWORD_LENGTH           5

// Controller Orders ID Table
#define DISPLAY_PASSWORD_FORMAT_ERROR             'A'
#define DISPLAY_PASSWORD_NOT_MATCH_ERROR          'B'
#define DISPLAY_PASSWORD_Changed                  'C'
#define DISPLAY_GET_NEW_PASSWORD_SEQUENCE         'D'
#define DISPLAY_DOOR_OPEN_SEQUENCE                'E'
#define DISPLAY_OPTION_MENU                       'F'
#define GET_ENTER_PASSWORD                        'I'
#define DISPLAY_SECURITY_ALARM                    'Y'
//HMI_Status
#define HMI_WAITING                               'N'

//Controller status
#define CONTROL_WAITING                           'Q'

// User Input Requests
#define Open_DOOR_REQ_ID                          'G'
#define CHANGE_PASSWORD_REQ_ID                    'H'
#define UART_DELAY                                 150

int main()
{
	 appInit();
	 uint8 password[PASSWORD_LENGTH];
	 uint8 reentertedPAssword[PASSWORD_LENGTH];
	 uint8 controllerOrder=DISPLAY_GET_NEW_PASSWORD_SEQUENCE; // controller requested order
	 uint8 userRequest;
	 sendHMIStatus(HMI_WAITING);
	 while(1)
	 {
		controllerOrder= recieveControllerDecision();

		switch (controllerOrder)
		{
		case DISPLAY_PASSWORD_FORMAT_ERROR:
			displayPasswordFormatError();
			sendHMIStatus(HMI_WAITING);

		break;

		case DISPLAY_PASSWORD_NOT_MATCH_ERROR:
			displayPasswordCompareError();
			sendHMIStatus(HMI_WAITING);

		break;

		case DISPLAY_PASSWORD_Changed:
			displayPasswordChanged();
			sendHMIStatus(HMI_WAITING);

		break;

		case DISPLAY_GET_NEW_PASSWORD_SEQUENCE:
			getNewPassword(password,reentertedPAssword,PASSWORD_LENGTH);
			waitForController();
			sendPasswordToController(password,PASSWORD_LENGTH);
			sendPasswordToController(reentertedPAssword,PASSWORD_LENGTH);
			sendHMIStatus(HMI_WAITING);

		break;

		case DISPLAY_DOOR_OPEN_SEQUENCE:
			displayDoorState();
			sendHMIStatus(HMI_WAITING);

		break;

		case DISPLAY_OPTION_MENU:
			displaySystemOptions();
			userRequest='0';
			while(!(userRequest=='*' || userRequest=='#')){userRequest=getUserRequest();}
			if(userRequest=='*')
			{
				waitForController();
				sendRequestToController(Open_DOOR_REQ_ID);

			}

			else if(userRequest=='#')
		   {
				waitForController();
				sendRequestToController(CHANGE_PASSWORD_REQ_ID);

		   }
			else
			{

			}
			sendHMIStatus(HMI_WAITING);
		break;

		case GET_ENTER_PASSWORD :
			getEnterPassword(password,PASSWORD_LENGTH);
			waitForController();
			sendPasswordToController(password,PASSWORD_LENGTH);
			sendHMIStatus(HMI_WAITING);
		break;

		case DISPLAY_SECURITY_ALARM :
			 displaySecurityAlarm();
			 sendHMIStatus(HMI_WAITING);
			 break;

		}


	 }
}
