/*
 * app.c
 *
 *  Created on: May 4, 2023
 *      Author: user
 */
#define 	F_CPU                 8000000UL
#include "app.h"
#include "../HAL/Buzzer/buzzer.h"
#include "../HAL/Motor/motor.h"
#include "../MCAL/UART/uart.h"
#include <util/delay.h>
#include "../HAL/EEPROM/external_eeprom.h"
#include "../std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void appInit(void)
{
	DcMotor_Init();
	buzzerInit();
	UART_init(9600);
	SREG|=(1<<7);
}

void recievePassword(uint8 *newPassword,uint8 length)
{
	for (uint8 i=0;i<length;i++)
	{
		newPassword[i]=UART_recieveByte();
	}


}

uint8 comparePasswords(uint8 *pass1,uint8 *pass2,uint8 length)
{
	uint8 notMatchFlag=0;
	for (uint8 i=0;i<length;i++)
		{
			if(pass1[i]==pass2[i])
			{
				// save password
			}

			else
			{
				notMatchFlag=1;
			}
		}
	return notMatchFlag;
}

void savePassword (uint8* password,uint8 length,uint16 u16addr)
{

	for(uint8 i=0;i<length;i++)
	{
		uint8 status=EEPROM_writeByte(u16addr+i,password[i]);
		_delay_ms(10);
	}

}


void triggerBuzzerAlarm(uint32 alarmTime)
{
	buzzerOn();
	_delay_ms(alarmTime*1000);
	buzzerOff();
}

void doorOpenSequence(void)
{
	DcMotor_Rotate(MOTOR_ON_CW,75);
	_delay_ms(5000);
	DcMotor_Rotate(MOTOR_OFF,0);
	_delay_ms(5000);
	DcMotor_Rotate(MOTOR_ON_CCW,75);
	_delay_ms(5000);
	DcMotor_Rotate(MOTOR_OFF,0);
}

void sendInterfaceOrder(uint8 order)
{
	UART_sendByte(order);
}

uint8 recieveInterfaceStatus (void)
{
	uint8 recievedStatus=  UART_recieveByte();
	return recievedStatus;
}

uint8 recieveUserRequest(void)
{
	uint8 request=  UART_recieveByte();
	return request;
}

void getAccessPassword(uint8* password,uint8 length,uint16 u16addr)
{
	for(uint8 i=0;i<length;i++)
		{
			uint8 status=EEPROM_readByte(u16addr+i,&password[i]);
			_delay_ms(10);

		}
}

void waitForHMI(void)
{
	uint8 status=  UART_recieveByte();
}

void sendControllerStatus(uint8 status)
{
	UART_sendByte(status);
}




