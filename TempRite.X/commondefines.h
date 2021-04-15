/* 
 * File:   commondefines.h
 * Author: heinrich
 *
 * Created on March 15, 2021, 7:59 PM
 */

#ifndef COMMONDEFINES_H
#define	COMMONDEFINES_H

#define STOP_INTERRUPTS     INTCON0bits.GIE = 0
#define START_INTERRUPTS    INTCON0bits.GIE = 1

#endif	/* COMMONDEFINES_H */

