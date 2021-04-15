/* 
 * File:   io.h
 * Author: heinrich
 *
 * Created on March 15, 2021, 9:01 PM
 */

#ifndef IO_H
#define	IO_H

#define SEG_A   LATAbits.LATA3
#define SEG_B   LATAbits.LATA4
#define SEG_C   LATAbits.LATA5
#define SEG_D   LATAbits.LATA7
#define SEG_E   LATAbits.LATA6
#define SEG_F   LATCbits.LATC0
#define SEG_G   LATCbits.LATC1
#define DP      LATCbits.LATC2
#define DIG_1   LATCbits.LATC3
#define DIG_2   LATCbits.LATC7

#define ON_BUT  PORTBbits.RB2
#define UP_BUT  PORTBbits.RB0
#define DWN_BUT  PORTBbits.RB1

#define COLD_VALVE LATAbits.LATA1
#define HOT_VALVE LATAbits.LATA2

void init_io(void);

#endif	/* IO_H */

