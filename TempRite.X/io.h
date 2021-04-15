/* 
 * File:   io.h
 * Author: heinrich
 *
 * Created on March 15, 2021, 9:01 PM
 */

#ifndef IO_H
#define	IO_H

#define SEG_A   PORTAbits.RA3
#define SEG_B   PORTAbits.RA4
#define SEG_C   PORTAbits.RA5
#define SEG_D   PORTAbits.RA7
#define SEG_E   PORTAbits.RA6
#define SEG_F   PORTCbits.RC0
#define SEG_G   PORTCbits.RC1
#define DP      PORTCbits.RC2
#define DIG_1   PORTCbits.RC3
#define DIG_2   PORTCbits.RC7

#define BLUE_LED    PORTBbits.RB5

#define ON_BUT  PORTBbits.RB2
#define UP_BUT  PORTBbits.RB0
#define DWN_BUT  PORTBbits.RB1

#define COLD_VALVE PORTAbits.RA1
#define HOT_VALVE PORTAbits.RA2

void init_io(void);

#endif	/* IO_H */

