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
unsigned short get_temperature(void);

#define START_ADC   ADCON0bits.GO = 1

#define ADC_INT INTCON0bits.ADIF
#define RESET_ADC ADC_INT = 0; START_ADC;

#endif	/* TEMPERATURE_H */

