#include "LCD20x4_4bit.h"
void lcdcommand(unsigned char cmnd)
{
	LCD_DPRT = (LCD_DPRT & 0x0f)|(cmnd & 0xf0);		/* SEND COMMAND TO DATA PORT */
	LCD_DPRT &= ~ (1<<LCD_RS);						/* RS = 0 FOR COMMAND */
	LCD_DPRT |= (1<<LCD_EN);						/* EN = 1 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(100);									/* WAIT FOR MAKE ENABLE WIDE */
	
	LCD_DPRT = (LCD_DPRT & 0x0f)|(cmnd << 4);		/* SEND COMMAND TO DATA PORT */
	LCD_DPRT |= (1<<LCD_EN);						/* EN = 1 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_ms(2);									/* WAIT FOR MAKE ENABLE WIDE */
}

void lcddata(unsigned char data)
{
	LCD_DPRT = (LCD_DPRT & 0x0f)|(data & 0xf0);		/* SEND DATA TO DATA PORT */
	LCD_DPRT |= (1<<LCD_RS);						/* MAKE RS = 1 FOR DATA */
	LCD_DPRT |= (1<<LCD_EN);						/* EN=0 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(100);									/* WAIT FOR MAKE ENABLE WIDE */
	
	LCD_DPRT = (LCD_DPRT & 0x0f)|(data << 4);		/*  */
	LCD_DPRT |= (1<<LCD_EN);						/* EN=0 FOR H TO L PULSE*/
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE*/
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE*/
	_delay_ms(2);									/* WAIT FOR MAKE ENABLE WIDE*/
}

void lcdinit()
{
	LCD_DDDR = 0xFF;
	_delay_ms(200);									/* WAIT FOR SOME TIME */
	lcdcommand(0x33);
	lcdcommand(0x32);								/* SEND $32 FOR INIT OT 0X02 */
	lcdcommand(0x28);								/* INIT. LCD 2 LINE, 5 X 7 MATRIX */
	lcdcommand(0x0C);								/* DISPLAY ON CURSOR ON */
	lcdcommand(0x01);								/* LCD CLEAR */
	_delay_ms(2);
	lcdcommand(0x82);								/* SHIFT CURSOR TO WRITE */
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char firstcharadd[]={0x80, 0xC0, 0x94, 0xD4};
	lcdcommand(firstcharadd[y] + x);
}

void lcd_print(char *str)
{
	unsigned char i=0;
	while (str[i] != 0)
	{
		lcddata(str[i]);
		i++;
	}
}

void lcd_clear()
{
	lcdcommand(0x01);
	_delay_ms(2);
}
