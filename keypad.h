/*
 * keypad.h
 *
 *  Created on: Apr 1, 2023
 *      Author: Ali Hassan
 */

//#define STANDARD_KEYPAD
#include "std_types.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPAD_NUM_ROWS				4
#define KEYPAD_NUM_COLS				4

#define KEYPAD_ROW_PORT_ID			PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID

#define KEYPAD_COL_PORT_ID			PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID		PIN4_ID

#define KEYPAD_BUTTON_PRESSED		LOGIC_LOW
#define KEPYAD_BUTTON_UNPRESSED		LOGIC_HIGH


//FUNCTION TO GET PRESSED KEY ON KEYPAD
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
