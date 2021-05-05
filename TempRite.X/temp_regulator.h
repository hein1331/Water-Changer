/* 
 * File:   temp_regulator.h
 * Author: heinrich
 *
 * Created on March 27, 2021, 3:48 PM
 */

#ifndef TEMP_REGULATOR_H
#define	TEMP_REGULATOR_H

signed int iterate_pi(void);
void temp_regulator_update(void);
void update_pi_regulator(void);

#define KP  30//20
#define KI  9 //0.1 offset
#define CONTROL_TIME    50 // 10s of milliseconds
#define BIAS    45

#define TEMP_DIFF   3

#define UPDATE_TIME 5

#endif	/* TEMP_REGULATOR_H */

