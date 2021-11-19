/*
* Nibble_MATH.h
* Author: Mohammed Elbagoury
* Created: 19/11/2021
*/

#ifndef _Nibble_MATH_H
#define _Nibble_MATH_H

#define HIGH_NIBBLE 4
#define LOW_NIBBLE 0

#define SET_Nibble(VAR,NibbleNO) (VAR) |=  (0x0f << (NibbleNO))
#define CLR_Nibble(VAR,NibbleNO) (VAR) &= ~(0x0f << (NibbleNO))
#define TOG_Nibble(VAR,NibbleNO) (VAR) ^=  (0x0f << (NibbleNO))
#define GET_Nibble(VAR,NibbleNO) (((VAR) >> (NibbleNO)) & 0x0f)


#endif