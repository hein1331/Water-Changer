#include <xc.h>
#include "timer.h"

void init_timer(void) {
    // Set timer to 8 bit timer
    T0CON0bits.MD16 = 0;
    
    // Set postscalar 1:1
    T0CON0bits.OUTPS = 0;
    
    // Set timer clock source to FOSC/4 clock
    T0CON1bits.CS = 0b010;
    T0CON1bits.ASYNC = 0;
    
    // Set timer prescalar to 1:128
    T0CON1bits.CKPS = 0b0111;
    
    RESET_TIMER
            
    // Turn on interrupt
    PIE0bits.TMR0IE = 1;
    
    // Enable the timer
    T0CON0bits.T0EN = 1;
    
}