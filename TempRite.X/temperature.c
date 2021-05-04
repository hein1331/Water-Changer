#include <xc.h>

#include "commondefines.h"
#include "temperature.h"

int temperature = 0;
volatile unsigned short adc_read = 300;

void init_temperature(void) {
    // Configure ADC
    
    TRISAbits.TRISA0 = 1; // Set RA0 to input
    ANSELA = 0x00000001; // Set RA0 to analog
    
    // Turn on ADC converter on RA0
    ADCON0bits.CHS = 0;
    
    // Set ADC ref to VDD
    ADCON1bits.PREF = 0;
    
    // Set ADC clock to ADCRC
    ADCON1bits.CS = 0b11;
    
    // Set the converted register right-justified with ADRESH having MSBs
    ADCON1bits.FM = 1;
    
    // Enable the ADC interrupt
    PIE1bits.ADIE = 1;
    
    ADCON0bits.ON = 1;
    
    RESET_ADC
    START_ADC;
}

void update_temperature(void) {
    // Get ADC value
    adc_read = ADRES;
    RESET_ADC
}

int get_raw_adc(void) {
    return (int)adc_read;
}

int get_temperature(void) {
    return (int)temperature;
}

void calculate_temperature(BOOL deg_f) {
    // Calculate resistance of thermistor
    long r_therm = (long)((R1 * adc_read)/(MAX_ADC - adc_read));
    
    // Look up the resistance in the LUT
    unsigned int i = 0;
    for(i = 0; i < LUT_SIZE; i++) {
        if(r_therm >= temp_lookup[i])
            break;
    }
    
    // Deal with lower and upper bounds of LUT
    if(i == 0)
        temperature = 0;
    else if (i == LUT_SIZE)
        temperature = LUT_SIZE * TEMP_INCREMENT;
    else { 
        // Get the two points
        long x0 = (long)temp_lookup[i-1];
        long x1 = (long)temp_lookup[i];
        long y0 = (long)(i-1)*TEMP_INCREMENT;
        long y1 = (long)(i)*TEMP_INCREMENT;

        // Interpolate the points
        temperature = (int)((y0 * (x1 - r_therm) + y1 * (r_therm - x0))/(x1 - x0)); 
    }
    
    if(deg_f)
        temperature = (temperature * 9) / 5 + 32;

}

int get_adc_from_temp(int temperature) {
    long resistance = 0;
    
    // Deal with bounds
    if(temperature < 0)
        resistance = (long) temp_lookup[0];
    else if(temperature > LUT_SIZE * TEMP_INCREMENT)
        resistance = (long) temp_lookup[LUT_SIZE - 1];
    else {
        // Calculate resistance indices
        int lower = temperature/TEMP_INCREMENT;
        int upper = lower + 1;
        
        // Get the two points
        long x0 = (long)lower*TEMP_INCREMENT;
        long x1 = (long)upper*TEMP_INCREMENT;
        long y0 = (long)temp_lookup[upper];
        long y1 = (long)temp_lookup[lower];
        
        resistance = (long)((y0 * (x1 - temperature) + y1 * (temperature - x0))/(x1 - x0)); 
    }
    
    // Calculate adc of thermistor
    return (int) (((unsigned long)resistance * MAX_ADC) / ((unsigned long)resistance - R1));
}