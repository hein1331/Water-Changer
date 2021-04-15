/* 
 * File:   commondefines.h
 * Author: heinrich
 *
 * Created on March 15, 2021, 7:59 PM
 */

#ifndef COMMONDEFINES_H
#define	COMMONDEFINES_H

#define STOP_INTERRUPTS     INTCONbits.GIE = 0; INTCONbits.PEIE = 0
#define START_INTERRUPTS    INTCONbits.GIE = 1; INTCONbits.PEIE = 1

#endif	/* COMMONDEFINES_H */

