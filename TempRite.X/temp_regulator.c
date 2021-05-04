#include <xc.h>

#include "commondefines.h"
#include "temp_regulator.h"
#include "temperature.h"
#include "io.h"
#include "buttons.h"
#include "display.h"

signed int prev_i = 0;
unsigned int hot_time = 0;
unsigned int cold_time = 0;
unsigned int time = 0;

void temp_regulator_update(void) {
    if(get_status() == ON) {
        if(time >= UPDATE_TIME)
        {
            // Update PI
            signed int err = get_temp_setpoint() - get_temperature();

            signed int p = KP * err;
            signed int i = (KI * (prev_i + (err * CONTROL_TIME)/100))/10;
            signed int new_val = p + i + BIAS;

            if(new_val > 100)
                new_val = 100;

            if(new_val < 0)
                new_val = 0;

            unsigned short pi_val = (unsigned short)new_val;

            prev_i = i;

            hot_time = CONTROL_TIME * 2 * (100 - pi_val) / 10;
            cold_time =CONTROL_TIME * 2 * (pi_val) / 10;

            if(hot_time > CONTROL_TIME*10)
                hot_time = CONTROL_TIME*10;

            if(cold_time > CONTROL_TIME*10)
                cold_time = CONTROL_TIME*10;
            
            time = 1;
        }

        COLD_VALVE = time <= cold_time;
        HOT_VALVE = time <= hot_time;

        time++;
    }
    else {
        COLD_VALVE = 0;
        HOT_VALVE = 0;
    }
}
