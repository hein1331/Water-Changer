#include <xc.h>

#include "io.h"
#include "buttons.h"
#include "display.h"

unsigned volatile char status = OFF;

unsigned short on_prev_state;
unsigned short up_prev_state;
unsigned short dwn_prev_state;

unsigned short on_counter;
unsigned short up_counter;
unsigned short dwn_counter;

void init_buttons(void) {
    on_prev_state = ON_BUT;
    up_prev_state = UP_BUT;
    dwn_prev_state = DWN_BUT;
    
    on_counter = 0;
    up_counter = 0;
    dwn_counter = 0;
}

unsigned char get_status(void) {
    return status;
}


void update_buttons(void) {
    // Set states based on buttons
    if(ON_BUT && on_counter == 0)
    {
        if(status == OFF)
            status = ON;
        else
            status = OFF;
    }  
    if(UP_BUT && up_counter == 0)
    {
        //if(temp_setpoint < 99)
          //  temp_setpoint++;
    }
    if(DWN_BUT && dwn_counter == 0)
    {
        //if(temp_setpoint > 0)
           // temp_setpoint--;
    }
    
    // Set counters
    if(ON_BUT != on_prev_state) 
        on_counter = DEBOUNCE_TIME;
    
    if(UP_BUT != up_prev_state) 
        up_counter = DEBOUNCE_TIME;
    
    if(DWN_BUT != dwn_prev_state) 
        dwn_counter = DEBOUNCE_TIME;
    
    // Decrement counters
    if(on_counter > 0)
        on_counter--;
    
    if(up_counter > 0)
        up_counter--;
    
    if(dwn_counter > 0)
        dwn_counter--;
}
