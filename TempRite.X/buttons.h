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
void set_setpoint_from_nvm(void);
void save_setpoint_to_nvm(void);
void unlock_nvm(void);
int get_adc_setpoint(void);
void adc_setpoint_update(void);

#define SETPOINT_SAVE_ADDR  0x3FFF

#define DEBOUNCE_TIME 5 // In 10s of ms

#define MAX_SETPOINT        99
#define MIN_SETPOINT        0
#define DEFAULT_SETPOINT    28

#endif	/* BUTTONS_H */

