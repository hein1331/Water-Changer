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
volatile int time = 0;

void temp_regulator_update(void) {
    if(get_status() != WATER_OFF) {
        // Don't turn on both valves at the same time, to save power supply
        COLD_VALVE = time < cold_time && ((time < hot_time && HOT_VALVE_STAT) || time >= hot_time);
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
    if(get_status() != WATER_OFF && time >= CONTROL_TIME)
    {
        int adc_setpoint = get_adc_setpoint();
        int raw_adc = get_raw_adc();

        // Update PI
        signed int err = adc_setpoint - raw_adc;

        signed int p = KP * err;
        signed int i = (KI * (prev_i + (err * time)/10))/100;
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
            hot_time = SATURATE_TIME;

        if(cold_time > CONTROL_TIME)
            cold_time = SATURATE_TIME;

        time = 0;
    }
}
