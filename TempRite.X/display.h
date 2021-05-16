/* 
 * File:   display.h
 * Author: heinrich
 *
 * Created on March 15, 2021, 7:51 PM
 */

//#define BREADBOARD

#ifndef DISPLAY_H
#define	DISPLAY_H

void init_display(void);
void update_display(void);

//#define SHOW_TEMP

#ifdef SHOW_TEMP
#define GET_TEMP    get_temperature()
#else
#define GET_TEMP    get_temp_setpoint()
#endif

#define ON      0
#define OFF     1

#define DIG_1_EN   0
#define DIG_2_EN   1

#define FLASH   2
#define DIG_OFF    10
#define FLASH_SPEED 25 // Flash every X * 10 ms (25 -> flash every 250ms)

#endif	/* DISPLAY_H */

