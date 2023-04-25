/*
 * keypad.c
 *
 *  Created on: Apr 1, 2023
 *      Author: Ahmed Hassan
 */
#include "gpio_a.h"
#include "keypad.h"

/*

PROTOTYPES DECLEARED HERE BECAUSE THOSE FUNCTIONS ARE STATIC

*/
#ifndef STANDARD_KEYPAD
#if(KEYPAD_NUM_COLS==3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_num);
#elif(KEYPAD_NUM_COLS==4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_num);
#endif
#endif

uint8 KEYPAD_getPressedKey(void)
{
	uint8 col,row;

	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
#if(KEYPAD_NUM_COLS==4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);
#endif
	while(1)
	{
		for(row=0;row<KEYPAD_NUM_ROWS;row++)
		{
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col=0;col<KEYPAD_NUM_COLS;col++)
			{
				if(GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+col)==KEYPAD_BUTTON_PRESSED)
				{
					#if(KEYPAD_NUM_COLS==3)
						#ifdef STANDARD_KEYPAD
						return((row*KEYPAD_NUM_COLS)+col+1);
						#else
						return(KEYPAD_4x3_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1));
						#endif
					#elif(KEYPAD_NUM_COLS==4)
						#ifdef 	STANDARD_KEYPAD
						return ((row*KEYPAD_NUM_COLS)+col+1);
						#else
						return(KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1));
						#endif
					#endif
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, PIN_INPUT);
		}
	}
}
#ifndef STANDARD_KEYPAD
#if(KEYPAD_NUM_COLS==3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_num)
{
	uint8 res=0;
	switch(button_num)
	{
	case 10:
		res='*';
		break;
	case 11:
		res=0;
		break;
	case 12:
		res='#';
		break;
	default:
		res=button_num;
		break;
	}
	return res;
}
#elif(KEYPAD_NUM_COLS==4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_num)
{
	uint8 res=0;
	switch(button_num)
	{
	case 1:
		res=7;
		break;
	case 2:
		res=8;
		break;
	case 3:
		res=9;
		break;
	case 4:
		res='/';//
		break;
	case 5:
		res=4;
		break;
	case 6:
		res=5;
		break;
	case 7:
		res=6;
		break;
	case 8:
		res='*';
		break;
	case 9:
		res=1;
		break;
	case 10:
		res=2;
		break;
	case 11:
		res=3;
		break;
	case 12:
		res='-';
		break;
	case 13:
		res=13; //ascii code of enter
		break;
	case 14:
		res=0;
		break;
	case 15:
		res='=';
		break;
	case 16:
		res='+';
		break;
	default:
		res=button_num;
		break;
	}
	return res;
}
#endif
#endif
