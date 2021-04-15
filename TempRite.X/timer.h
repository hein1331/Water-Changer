/* 
 * File:   timer.h
 * Author: heinrich
 *
 * Created on March 27, 2021, 2:01 PM
 */

#ifndef TIMER_H
#define	TIMER_H

void init_timer(void);

// Timer set to 100Hz
#define TIMER_FREQ 100
#define TIMER_INT PIR0bits.TMR0IF
#define RESET_TIMER TIMER_INT = 0; TMR0L = 100;

#endif	/* TIMER_H */

