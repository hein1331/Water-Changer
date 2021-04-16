#include <xc.h>
#include <math.h>
#include "temperature.h"

volatile int temperature = 0;

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
    // Get ADC value
    double adc_read = (double)ADRES;
    
    // Calculate resistance of thermistor
    double r_therm = (R1 * adc_read)/(MAX_ADC-adc_read);

    // Calculate the resistance
    double log_r_therm = log(r_therm); 
    double t_kelvin = (1.0 / (A + B * log_r_therm + C * log_r_therm * log_r_therm * log_r_therm));
    temperature = (int) (t_kelvin + KELVIN_0C);
    
    RESET_ADC
}


int get_temperature(void) {
    return temperature;
}
