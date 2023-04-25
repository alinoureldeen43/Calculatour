/*
 * main.c
 *
 *  Created on: Apr 6, 2023
 *      Author: Ahmed Hassan
 */

#include"gpio_a.h"
#include"keypad.h"
#include"lcd.h"
#include<util/delay.h>

int main()
{
	int in,res,var1=0,var2=0,op;

	LCD_init();
	LCD_displayString("ALI Calculator");
	_delay_ms(1000);
	LCD_clearScrean();




	while(1)
	{
		in=KEYPAD_getPressedKey();
		_delay_ms(500);
		if(in>=0 && in <=9)
		{
			LCD_integrToString(in);
			var1= (var1*10)+in;
		}
		else if(!(in>=0 && in <=9) && in !='=')
		{
			LCD_clearScrean();
			op=in;
			var2=var1;
			var1=0;
		}
		else if(in=='=')
		{
			LCD_clearScrean();
			switch(op)
			{
			case'+':
				res=var1+var2;
				break;
			case'-':
				res=var2-var1;
				break;
			case'*':
				res=var1*var2;
				break;
			case'/':
				res=var2/var1;
				break;

			}
			LCD_integrToString(res);
		}
		else if(in==13)
		{
			LCD_clearScrean();
		}
	}
}

