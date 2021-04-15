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

#ifdef BREADBOARD

#define ON      0
#define OFF     1

#define DIG_1_EN   0
#define DIG_2_EN   1

#else

#define ON      1
#define OFF     0

#define DIG_1_EN   1
#define DIG_2_EN   0

#endif

#define FLASH   2
#define DIG_OFF    10

#endif	/* DISPLAY_H */

