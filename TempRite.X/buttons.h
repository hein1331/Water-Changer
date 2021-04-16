/* 
 * File:   buttons.h
 * Author: heinrich
 *
 * Created on March 17, 2021, 11:41 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#include "timer.h"

void init_buttons(void);
void update_buttons(void);
unsigned char get_status(void);
int get_temp_setpoint(void);

#define DEBOUNCE_TIME 5 // In 10s of ms

#endif	/* BUTTONS_H */

