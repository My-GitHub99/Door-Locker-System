/*
 * app.c
 *
 *  Created on: May 4, 2023
 *      Author: user
 */

#include "app.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../MCAL/UART/uart.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define DISPLAY_DELAY 5000




void appInit(void)
{
	LCD_init();
	UART_init(9600);
	SREG|=(1<<7);
}


void getNewPassword(uint8 *password,uint8 *reenterted_password,uint8 length)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("ENTER NEW PASS");

	/* entering a password*/
	for(int i=0;i<length;i++)
	{
		password[i] =KEYPAD_getPressedKey()+48; // store number in array
		_delay_ms(500); // key press time delay
		LCD_moveCursor(1,i); // move to nxt line
		LCD_displayCharacter('*'); // write '*'
	}

	/* rentering the password and checking if both match */
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("RE-ENTER PASS");
	for(int i=0;i<length;i++)
		{
		reenterted_password[i]=KEYPAD_getPressedKey()+48;
			_delay_ms(500);
			LCD_moveCursor(1,i);
			LCD_displayCharacter('*');
			// check if characters match

		}

}

void sendPasswordToController(uint8 *password,uint8 length)
{
	for(int i=0;i<length;i++)
		{
		 UART_sendByte(password[i]);

		}

}



void displaySystemOptions(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("*: Open The Door");
	LCD_moveCursor(1,0);
	LCD_displayString("#: Change Pass");

}

uint8 recieveControllerDecision(void)
{
	uint8 decision=UART_recieveByte();
	return decision;
}

void displayPasswordFormatError(void)
{
	LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("Error");
		LCD_moveCursor(1,0);
		LCD_displayString("choose num bet");
		LCD_moveCursor(2,0);
		LCD_displayString("0-9");
		_delay_ms(2000);

}

void displayPasswordCompareError(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Error");
	LCD_moveCursor(1,0);
	LCD_displayString("Pass Don't Match");
	_delay_ms(2000);

}

void displayPasswordChanged(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Password changed");
	_delay_ms(2000);
}


void displayDoorState(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Door Opening...");
	_delay_ms(DISPLAY_DELAY);
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Door Open !");
	LCD_moveCursor(1,0);
	LCD_displayString("Welcome Home ^_^");
	_delay_ms(DISPLAY_DELAY);
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Door closing...");
   _delay_ms(DISPLAY_DELAY);
}

void StatusAck (uint8 status)
{
	UART_sendByte(status);
}

uint8 getUserRequest(void)
{
	uint8 input=KEYPAD_getPressedKey();
	_delay_ms(500);
	return input;
}

void sendRequestToController(uint8 request)
{
	UART_sendByte(request);
}

void getEnterPassword(uint8 *password,uint8 length)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Enter Password");
		for(int i=0;i<length;i++)
			{
			password[i]=KEYPAD_getPressedKey()+48;
			_delay_ms(500);
			LCD_moveCursor(1,i);
			LCD_displayCharacter('*');
			}

}

void waitForController(void)
{
	uint8 status=  UART_recieveByte();

}

void sendHMIStatus(uint8 status)
{
	UART_sendByte(status);
}
void displaySecurityAlarm(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Security ALARM !");
	LCD_moveCursor(1,0);
	LCD_displayString("Who Are You -_-");
	_delay_ms(10000);
}



