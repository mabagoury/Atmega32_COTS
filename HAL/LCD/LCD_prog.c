/*
* LCD_prog.c
* Author: Mohammed Elbagoury
* Created: 5/1/2022
*/

#define F_CPU 8000000UL

/*AVR LIB*/
#include <util/delay.h>

/*LIB*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/*MCAL*/
#include "../../MCAL/DIO/DIO_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

void LCD_vidInit(void){
    #if LCD_INIT_MODE==LCD_u8_4_BIT
        DIO_voidSetPortDirection(LCD_DATA_PORT,0xff);
        DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_u8_OUTPUT);
        DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_u8_OUTPUT);
        DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_E_PIN,DIO_u8_OUTPUT);
        _delay_ms(30);
        LCD_vidSendCommand(lcd_FunctionSet4bit);
        LCD_vidSendCommand(lcd_FunctionSet4bit);
        LCD_vidSendCommand(0x80);
        _delay_ms(1);
        LCD_vidSendCommand(lcd_DisplayOn);
        LCD_vidSendCommand(lcd_DisplayOn<<4);
        _delay_ms(1);
        LCD_vidSendCommand(lcd_Clear);
        LCD_vidSendCommand(lcd_Clear<<4);
        _delay_ms(15);
        LCD_vidSendCommand(lcd_EntryMode);
        LCD_vidSendCommand(lcd_EntryMode<<4);
        _delay_ms(2);
    #elif LCD_INIT_MODE==LCD_u8_8_BIT
        DIO_voidSetPortDirection(LCD_DATA_PORT,0xff);
        DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_u8_OUTPUT);
        DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_u8_OUTPUT);
        DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_E_PIN,DIO_u8_OUTPUT);
        _delay_ms(30);
        LCD_vidSendCommand(lcd_FunctionSet8bit);
        _delay_ms(1);
        LCD_vidSendCommand(lcd_DisplayOn);
        _delay_ms(1);
        LCD_vidSendCommand(lcd_Clear);
        _delay_ms(15);
        LCD_vidSendCommand(lcd_EntryMode);
        _delay_ms(2);
    #endif       
}

void LCD_vidSendCommand(u8 u8CmdCpy){
    #if LCD_INIT_MODE==LCD_u8_4_BIT
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8_LOW);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8_LOW);
        
        u8 highNibble = GET_Nibble(u8CmdCpy, 0);
        DIO_u8SetLowNibbleValue(LCD_DATA_PORT, highNibble);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_HIGH);
        _delay_us(1);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_LOW);
        _delay_us(1);
        
        u8 lowNibble = GET_Nibble(u8CmdCpy, 0);
        DIO_u8SetLowNibbleValue(LCD_DATA_PORT, lowNibble);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_HIGH);
        _delay_us(1);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_LOW);
        _delay_us(1);     
    #elif LCD_INIT_MODE==LCD_u8_8_BIT
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8_LOW);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8_LOW);
        DIO_voidSetPortValue(LCD_DATA_PORT, u8CmdCpy);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_HIGH);
        _delay_us(1);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_LOW);
        _delay_us(1);
    #endif     
}

void LCD_vidWriteChar(u8 u8DataCpy){
    #if LCD_INIT_MODE==LCD_u8_4_BIT
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8_HIGH);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8_LOW);
        
        u8 highNibble = GET_Nibble(u8DataCpy, 0);
        DIO_u8SetLowNibbleValue(LCD_DATA_PORT, highNibble);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_HIGH);
        _delay_us(1);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_LOW);
        _delay_us(1);
        
        u8 lowNibble = GET_Nibble(u8DataCpy, 0);
        DIO_u8SetLowNibbleValue(LCD_DATA_PORT, lowNibble);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_HIGH);
        _delay_us(1);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_LOW);
        _delay_us(1);
    #elif LCD_INIT_MODE==LCD_u8_8_BIT
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8_HIGH);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8_LOW);
        DIO_voidSetPortValue(LCD_DATA_PORT, u8DataCpy);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_HIGH);
        _delay_ms(1);
        DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8_LOW);
        _delay_ms(1);
    #endif     
}

void LCD_vidWriteString (u8* pu8StringCpy){
	u8 i=0;
    while(pu8StringCpy[i]!= '\0'){
        LCD_vidWriteCharctr(pu8StringCpy[i++]);
        _delay_ms(2);
    }
}

void LCD_vidWriteNumber(u16 Copy_u16Number){
    //get number of digits
    u8 digits=0;
	u16 CopyNumber=Copy_u16Number;
    while(CopyNumber){
		CopyNumber/=10;
		digits++;
	}
    
    //define and initialize an array to store the digits
    u8 digitsArr[digits];
    for(u8 i=digits-1; i>=0; i--)
        digitsArr[i]=0;
    
    //get the digits and store them in the array in reverse order
    for(u8 i=digits-1; i>=0; i--){
        digitsArr[i]=Copy_u16Number%10;
        Copy_u16Number/=10;
    }

    //display the digits
    for(u8 i=0; i<digits; i++){
        LCD_vidWriteCharctr('0'+digitsArr[i]);
    }
}

void LCD_vidGotoxy (u8 Y,u8 X){
    
    if (X>0 && X<=16){
		X--;       //to make it 0 indexed
        switch(Y){
            case 1:
                LCD_vidSendCommand(lcd_SetCursor+X);
                break;
            case 2:
                LCD_vidSendCommand(lcd_SetCursorAtSecondLine+X);
                break;
            default:
                break;
		}
	}
}

void LCD_vidWriteExtraChar (u8* pu8CharCpy, u8 u8CGIndex, u8 Y,u8 X){
    //CG Index (1 to 8) --> addreess in CG RAM
    u8 CGAddress=(u8CGIndex-1)*8;
    //set cursor at the start of CG RAM
    LCD_vidSendCommand(lcd_SetCursorAtCGRAM);
    //Write the character in CG RAM
    for(u8 i=CGAddress ; i<CGAddress+8 ; i++){
		LCD_vidWriteCharctr(pu8CharCpy[i]);
	}

    //get the cursor to point to the given place in DD RAM
    LCD_vidGotoxy(Y,X);
    //addresses (0 to 7) are the CG RAM addresses
    LCD_vidWriteChar(u8CGIndex-1);
}