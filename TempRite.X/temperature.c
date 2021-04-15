#include <xc.h>
//#include <math.h>
#include "temperature.h"

volatile unsigned short temperature = 0;

void init_temperature(void) {
    // Configure ADC
    
    // Bit <7:6>: 11 -> Use internal clock for ADC
    // Bit <5:2>: 0000 -> Use ADC channel 1
    // Bit 1: 0 -> Do not start ADC
    // Bit 0: 1 -> Turn on ADC module
    ADCON0 = 0b11000001;
    
    RESET_ADC
}


void update_temperature(void) {
    temperature = ADRES;
    RESET_ADC
}


unsigned short get_temperature(void) {
    return temperature;
}
