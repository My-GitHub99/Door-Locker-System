/*
 * main.c
 *
 *  Created on: Apr 3, 2023
 *      Author: user
 */


#include "Application/app.h"
#include <util/delay.h> /* For the delay functions */

#define 	F_CPU                              8000000UL
#define PASSWORD_LENGTH                           5
#define ADDRESS                                  0x0311
#define PASSWORDS_ENTERING_ATTEMPTS                3
#define ALARM_TIME_IN_SECONDS                      10

// Controller Orders ID Table
#define DISPLAY_PASSWORD_FORMAT_ERROR             'A'
#define DISPLAY_PASSWORD_NOT_MATCH_ERROR          'B'
#define DISPLAY_PASSWORD_Changed                  'C'
#define DISPLAY_GET_NEW_PASSWORD_SEQUENCE         'D'
#define DISPLAY_DOOR_OPEN_SEQUENCE                'E'
#define DISPLAY_OPTION_MENU                       'F'
#define GET_ENTERED_PASSWORD                      'I'
#define DISPLAY_SECURITY_ALARM                    'Y'

// HMI MC status
#define HMI_avaliable                             'N'

//Controller status
#define CONTROL_WAITING                           'Q'

// User Input Requests
#define Open_DOOR_REQ_ID                          'G'
#define CHANGE_PASSWORD_REQ_ID                    'H'

// compare password results
#define MATCH                                      0
#define NOT_MATCH                                  1



uint8 entertedPassword[PASSWORD_LENGTH];
uint8 reentertedPAssword[PASSWORD_LENGTH];
uint8 passwordStatus=NOT_MATCH;
uint8 firstpasswordFlag=1;
uint8 userRequest=CHANGE_PASSWORD_REQ_ID;
uint8 accessPassword[PASSWORD_LENGTH];
uint8 EnterpasswordAttempt=PASSWORDS_ENTERING_ATTEMPTS ;



//check HMI ready

/*void isHmiAvaliable(void)
{
	while(HMI_status==HMI_BUSY)
		 {
		  HMI_status=recieveInterfaceStatus();
		 }
}*/






int main()
{
	 appInit();
	 while(1)
	 {

		if (userRequest==CHANGE_PASSWORD_REQ_ID)
		{
            if(firstpasswordFlag==0)
            {

            	passwordStatus=NOT_MATCH;
            	while(passwordStatus==NOT_MATCH)
            	{
            	waitForHMI();
            	sendInterfaceOrder(GET_ENTERED_PASSWORD);

            	sendControllerStatus(CONTROL_WAITING );
            	recievePassword(entertedPassword,PASSWORD_LENGTH );
            	getAccessPassword(accessPassword,PASSWORD_LENGTH ,ADDRESS);
            	passwordStatus=comparePasswords(entertedPassword,accessPassword,PASSWORD_LENGTH );
            	if(passwordStatus==NOT_MATCH)
            	{
            		waitForHMI();
            	 sendInterfaceOrder(DISPLAY_PASSWORD_NOT_MATCH_ERROR);

            	}

            	 else
            	{
            		 waitForHMI();
            	 sendInterfaceOrder(DISPLAY_PASSWORD_Changed);

            	}

            	}



            }

            passwordStatus=NOT_MATCH;
			while(passwordStatus==NOT_MATCH)
				 {
				     waitForHMI(); // wait for hmi to be avaliable
					 sendInterfaceOrder(DISPLAY_GET_NEW_PASSWORD_SEQUENCE);
					 sendControllerStatus(CONTROL_WAITING );
					 recievePassword(entertedPassword,PASSWORD_LENGTH );
					 recievePassword(reentertedPAssword,PASSWORD_LENGTH );
					 passwordStatus=comparePasswords(entertedPassword,reentertedPAssword,PASSWORD_LENGTH );

					 if(passwordStatus==NOT_MATCH)
					 {
						 waitForHMI(); // wait for hmi to be avaliable
						 sendInterfaceOrder(DISPLAY_PASSWORD_NOT_MATCH_ERROR);

					 }

					 else
					 {
						 waitForHMI(); // wait for hmi to be avaliable
						 sendInterfaceOrder(DISPLAY_PASSWORD_Changed);
						 sendInterfaceOrder(DISPLAY_OPTION_MENU );
						 savePassword(entertedPassword,PASSWORD_LENGTH ,ADDRESS);

					 }
				 }
            firstpasswordFlag=0;
		}

		else if(userRequest==Open_DOOR_REQ_ID )
		{
			passwordStatus=NOT_MATCH;
			while(passwordStatus==NOT_MATCH)
			            	{
				            waitForHMI();
			            	sendInterfaceOrder(GET_ENTERED_PASSWORD);

			            	sendControllerStatus(CONTROL_WAITING );
			            	recievePassword(entertedPassword,PASSWORD_LENGTH );
			            	getAccessPassword(accessPassword,PASSWORD_LENGTH ,ADDRESS);
			            	passwordStatus=comparePasswords(entertedPassword,accessPassword,PASSWORD_LENGTH );
			            	if(passwordStatus==NOT_MATCH)
			            	{
			            		EnterpasswordAttempt--;
			            	    if(EnterpasswordAttempt==0)
			            		 {
			                      waitForHMI();
			            		  sendInterfaceOrder( DISPLAY_SECURITY_ALARM );
			            		  triggerBuzzerAlarm(ALARM_TIME_IN_SECONDS );
			            		  EnterpasswordAttempt=PASSWORDS_ENTERING_ATTEMPTS;
			            		  sendInterfaceOrder(DISPLAY_OPTION_MENU );
			            		  break;
			            		 }

			            	 else
			            	 {
			            		 waitForHMI();
			            		 sendInterfaceOrder(DISPLAY_PASSWORD_NOT_MATCH_ERROR);

			            	 }


			            	}

			            	 else
			            	{
			            		 waitForHMI();
			            		 sendInterfaceOrder(DISPLAY_DOOR_OPEN_SEQUENCE);
			            		 doorOpenSequence();
			            		 waitForHMI();
			            		sendInterfaceOrder(DISPLAY_OPTION_MENU );

			            	}

			            	}


		}

		sendControllerStatus(CONTROL_WAITING );
		userRequest= recieveUserRequest();

	 }


}
