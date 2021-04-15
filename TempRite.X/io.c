#include <xc.h>
#include "io.h"

void init_io(void) {
    // Enable HF Occilstior
    OSCENbits.HFOEN = 1;
    
    // Set occilator frequency to 16mHZ
    OSCFRQ = 0b100;
        
    // Wait for occilator to be ready
    while(!OSCSTATbits.HFOR);
    
    // Set R0 to ADC and the rest to digital pins
    ANSELA = 0x1;
    ANSELB = 0x0;
    ANSELC = 0x0;
    
    // Init all IO to 0
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    
    // Set all of port A to outputs except RA0
    TRISA = 0x1;
    
    // Set LEDs to outputs and buttons, program pins to inputs
    TRISB = 0b11000111;
    
    // Set all of Port C to outputs
    TRISC = 0;
}
