/* 
 * File:   timer.h
 * Author: heinrich
 *
 * Created on March 27, 2021, 2:01 PM
 */

#ifndef TIMER_H
#define	TIMER_H

void init_timer(void);

// Fast Timer set to 100Hz
#define FAST_TIMER_FREQ 100
#define FAST_TIMER_INT PIR1bits.TMR1IF
#define RESET_FAST_TIMER FAST_TIMER_INT = 0; TMR1H = 177; TMR1L = 224;

// Fast Timer set to 1Hz
#define SLOW_TIMER_FREQ 1
#define SLOW_TIMER_INT PIR0bits.TMR0IF
#define RESET_SLOW_TIMER SLOW_TIMER_INT = 0; TMR0L = 11; 

#endif	/* TIMER_H */

