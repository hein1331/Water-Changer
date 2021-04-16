/* 
 * File:   temperature.h
 * Author: heinrich
 *
 * Created on March 27, 2021, 2:34 PM
 */

#ifndef TEMPERATURE_H
#define	TEMPERATURE_H

void init_temperature(void);
void update_temperature(void);
int get_temperature(void);

#define START_ADC   ADCON0bits.GO = 1

#define ADC_INT PIR1bits.ADIF
#define RESET_ADC ADC_INT = 0; START_ADC;

#define R1 22000.
#define MAX_ADC 1023.

// Steinhart-Hart Coefficients
#define A 1.294101041e-03
#define B 2.161266819e-04
#define C 0.8871575401e-07

#define KELVIN_0C -273.15


#endif	/* TEMPERATURE_H */

