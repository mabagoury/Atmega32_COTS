/*
* LCD_config.h
* Author: Mohammed Elbagoury
* Created: 5/1/2022
*/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_DATA_PORT              DIO_u8_PORTB
#define LCD_CONTROL_PORT           DIO_u8_PORTC
#define LCD_RS_PIN                 DIO_u8_PIN0
#define LCD_RW_PIN                 DIO_u8_PIN1
#define LCD_E_PIN                  DIO_u8_PIN2

/*Options:
    1- LCD_u8_4_BIT
    2- LCD_u8_8_BIT     */
#define LCD_INIT_MODE              LCD_u8_4_BIT

#endif
