/*
* LCD_interface.h
* Author: Mohammed Elbagoury
* Created: 5/1/2022
*/

#ifndef LCD_H_
#define LCD_H_


/* Description: Apply initialization sequence for LCD module                           */
/* Input      : Nothing                                                                */
/* Output     : Nothing                                                                */
void LCD_vidInit(void);


/* Description: Interface to send the configuration commands to the LCD Driver         */
/* Input      : Command number                                                         */
/* Output     : Nothing                                                                */
void LCD_vidSendCommand(u8 u8CmdCpy);


/* Description: Interface to write character on LCD screen                             */
/* Input      : Data to send                                                           */
/* Output     : Nothing                                                                */
void LCD_vidWriteChar(u8 u8DataCpy);


/* Description: Interface to write string on LCD screen                                */
/* Input      : Pointer to the string                                                  */
/* Output     : Nothing                                                                */
void LCD_vidWriteString (u8* pu8StringCpy);

/* Description: Interface to write a number on LCD as a string                         */
/* Input      : Copy_u16Number = Number needs to be written on the LCD                 */
/* Output     : Nothing                                                                */
void LCD_vidWriteNumber(u16 Copy_u16Number);

/* Description: Interface to start the writing process at certain digit in the LCD     */
/* Input      : Y = Row position , X = Column position                                 */
/* Output     : Nothing                                                                */
void LCD_vidGotoxy (u8 Y,u8 X);

/* Description: Interface to write extra characters saved in the CGRAM                 */
/* Input      : Y = Row position , X = Column position                                 */
/* Output     : Nothing                                                                */
void LCD_vidWriteExtraChar (u8* pu8CharCpy, u8 u8CGIndex, u8 Y,u8 X);

#endif /* LCD_H_ */
