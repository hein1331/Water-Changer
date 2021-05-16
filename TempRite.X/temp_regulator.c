#include <xc.h>

#include "commondefines.h"
#include "temp_regulator.h"
#include "temperature.h"
#include "io.h"
#include "buttons.h"
#include "display.h"

signed int prev_i = 0;
volatile unsigned int hot_time = 0;
volatile unsigned int cold_time = 0;
volatile unsigned int time = CONTROL_TIME;

void temp_regulator_update(void) {
    if(get_status() == ON) {
        COLD_VALVE = time < cold_time;
        HOT_VALVE = time < hot_time;
        time++;
        
        if(time > cold_time)
            time++;
        
        if(time > hot_time)
            time++;
        
    }
    else {
        COLD_VALVE = 0;
        HOT_VALVE = 0;
    }
}

void update_pi_regulator(void) {
    if(get_status() == ON && time >= CONTROL_TIME)
    {
        int adc_setpoint = get_adc_setpoint();
        int raw_adc = get_raw_adc();

        // Update PI
        signed int err = adc_setpoint - raw_adc;

        signed int p = KP * err;
        signed int i = (KI * (prev_i + (err * CONTROL_TIME)/10))/100;
        signed int new_val = p + i + BIAS;

        if(new_val > 100)
            new_val = 100;

        if(new_val < 0)
            new_val = 0;

        unsigned short pi_val = (unsigned short)new_val;

        prev_i = i;

        hot_time = CONTROL_TIME * 2 * (100 - pi_val) / 100;
        cold_time = CONTROL_TIME * 2 * (pi_val) / 100;

        if(hot_time > CONTROL_TIME)
            hot_time = CONTROL_TIME;

        if(cold_time > CONTROL_TIME)
            cold_time = CONTROL_TIME;

        time = 0;
    }
}
