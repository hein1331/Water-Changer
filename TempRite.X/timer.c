#include <xc.h>
#include "timer.h"

void init_timer(void) {
    // Fast timer init
    // Set clock source to FOSC
    T1CLK = 0b00010;
    
    // Set timer prescalar to 1:8
    T1CONbits.CKPS = 0b11;
    
    // Set 16bit Read mode
    T1CONbits.RD16 = 1;
    
    // Turn on interrupt
    PIE1bits.TMR1IE = 1;
    
    RESET_FAST_TIMER
            
    
    // Slow timer init
    // Set timer to 8 bit timer
    T0CON0bits.MD16 = 0;
    
    // Set postscalar 1:1
    T0CON0bits.OUTPS = 0;
    
    // Set timer clock source to MFINTOSC (500 kHz) clock
    T0CON1bits.CS = 0b101;
    T0CON1bits.ASYNC = 0;

    // Set timer prescalar to 1:512
    T0CON1bits.CKPS = 0b1001;

    // Set timer postscalar to 1:4
    T0CON0bits.OUTPS = 0b0011;

    // Turn on interrupt
    PIE0bits.TMR0IE = 1;
    
    RESET_SLOW_TIMER
    
    // Enable the timers
    T1CONbits.ON = 1;
    T0CON0bits.T0EN = 1;
}