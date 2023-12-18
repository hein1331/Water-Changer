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

#define KP  3//20
#define KI  10 //0.01 offset
#define CONTROL_TIME    50 // 10s of milliseconds
#define SATURATE_TIME   500
#define BIAS    50

#define TEMP_DIFF 1

#define UPDATE_TIME 5

#endif	/* TEMP_REGULATOR_H */

