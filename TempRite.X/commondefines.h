/* 
 * File:   commondefines.h
 * Author: heinrich
 *
 * Created on March 15, 2021, 7:59 PM
 */

#ifndef COMMONDEFINES_H
#define	COMMONDEFINES_H

#define _XTAL_FREQ (16000000)

#define STOP_INTERRUPTS     INTCONbits.GIE = 0; INTCONbits.PEIE = 0
#define START_INTERRUPTS    INTCONbits.GIE = 1; INTCONbits.PEIE = 1

typedef unsigned short BOOL;
#define TRUE    1
#define FALSE   0

typedef unsigned char SYSTEM_STATUS;
#define WATER_OFF 0
#define WATER_ON 1
#define WATER_ON_TEMP 2

#endif	/* COMMONDEFINES_H */

