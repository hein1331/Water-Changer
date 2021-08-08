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
#define TEMP_INCREMENT  50
static const unsigned int temp_lookup[LUT_SIZE] = 
{
    /*35563, // 0deg
    27119, // 5deg
    20860, // 10deg
    16204, // 15deg
    12683, // 20deg
    10000, // 25deg
    7942, // 30deg
    6326, // 35deg
    5074, // 40deg
    4102, // 45deg
    3336,
    2724,
    2237,
    1845,
    1530*/
    
    33607, // 0deg
    25681, // 5deg
    19796, // 10deg
    15393, // 15deg
    12074, // 20deg
    9530, // 25deg
    7576, // 30deg
    6042, // 35deg
    4855, // 40deg
    3930, // 45deg
    3199, // 50deg
    2615, // 55deg
    2149, // 60deg
    1775, // 65deg
    1473 // 70deg
};

#endif	/* TEMPERATURE_H */

