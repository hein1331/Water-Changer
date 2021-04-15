#include <xc.h>
//#include <math.h>
#include "temperature.h"

volatile unsigned int temperature = 0;

void init_temperature(void) {
    // Configure ADC
    
    // Turn on ADC converter on RA0
    ADCON0bits.CHS = 0;
    
    // Set ADC ref to VDD
    ADCON1bits.PREF = 0;
    
    // Set ADC clock to Fosc/4
    ADCON1bits.CS = 0b100;
    
    // Set the converted register right-justified with ADRESH having MSBs
    ADCON1bits.FM = 1;
    
    // Enable the ADC interrupt
    PIE1bits.ADIE = 1;
    
    RESET_ADC
}


void update_temperature(void) {
    temperature = ADRES;
    RESET_ADC
}


unsigned int get_temperature(void) {
    return temperature;
}
