
// PIC16F570 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRC_IO  // Oscillator (INTRC with I/O function on OSC2/CLKOUT)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (Disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection off)
#pragma config IOSCFS = 8MHz    // Internal Oscillator Frequency Select (8 MHz INTOSC Speed)
#pragma config CPSW = OFF       // Code Protection bit - Flash Data Memory (Code protection off)
#pragma config BOREN = ON       //  (BOR Enabled)
#pragma config DRTEN = OFF      //  (DRT Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include "timer.h"
#include "commondefines.h"
#include "io.h"
#include "display.h"
#include "buttons.h"
#include "temperature.h"
#include "temp_regulator.h"

void main(void) {
    // Stop global interrupts
    STOP_INTERRUPTS;

    // Init all functions
    init_io();
    init_timer();
    init_display();
    init_buttons();
    init_temperature();
    
    // Start global interrupts
    START_INTERRUPTS;
    
    while(1)
    {
        BLUE_LED = 0;
    }
}


void __interrupt() ISR(void) {
    STOP_INTERRUPTS;
    if(TIMER_INT) {
        update_display();
        update_buttons();
        temp_regulator_update();
        RESET_TIMER
    }
    if(ADC_INT)
        update_temperature();
    
    
    START_INTERRUPTS;
}