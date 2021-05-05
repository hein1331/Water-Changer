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
void calculate_temperature(BOOL deg_f);
int get_adc_from_temp(int temperature);
int get_raw_adc(void);

#define START_ADC   ADCON0bits.GO = 1

#define ADC_INT PIR1bits.ADIF
#define RESET_ADC ADC_INT = 0;

#define R1 22000L
#define MAX_ADC 1023L

// Temperature lookup table
#define LUT_SIZE    15
#define TEMP_INCREMENT  5
static const unsigned int temp_lookup[LUT_SIZE] = 
{
    35563, // 0deg
    27119, // 5deg
    20860,
    16204,
    12683, 
    10000,
    7942,
    6326,
    5074,
    4102,
    3336,
    2724,
    2237,
    1845,
    1530
};

#endif	/* TEMPERATURE_H */

