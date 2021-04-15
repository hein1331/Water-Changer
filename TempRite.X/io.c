#include <xc.h>
#include "io.h"

void init_io(void) {
    // Internal occilator calibration
    OSCCAL = 0b00100111;
    
    // Set R0 to ADC and the rest to digital pins
    ANSEL = 0x1;
    
    // Bit 7: 1 -> Disable PORTB Interrupt Flag on Pin Change bit
    // Bit 6: 1 -> Disable PORTB Weak Pull-Ups bit
    // Bit 5: 0 -> Timer0 uses internal clock
    // Bit 4: 0 -> Does not matter
    // Bit 3: 0 -> Prescaler assigned to Timer0
    // Bit <2:0>: 110 -> Timer0 Prescalar 1:128
    OPTION = 0b11010110;
    
    // Turn off comparators
    CM1CON0bits.C1ON = 0;
    CM2CON0bits.C2ON = 0;
    
    // Disable op amps
    OPACONbits.OPA1ON = 0;
    OPACONbits.OPA2ON = 0;
    
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
