#include <xc.h>

#include "commondefines.h"
#include "io.h"
#include "buttons.h"
#include "temperature.h"
#include "display.h"

unsigned volatile char status = OFF;

unsigned short on_prev_state;
unsigned short up_prev_state;
unsigned short dwn_prev_state;

unsigned short on_counter;
unsigned short up_counter;
unsigned short dwn_counter;

int temp_setpoint;
volatile int adc_setpoint;
volatile BOOL update_setpoint = TRUE;

void init_buttons(void) {
    on_prev_state = ON_BUT;
    up_prev_state = UP_BUT;
    dwn_prev_state = DWN_BUT;
    
    on_counter = 0;
    up_counter = 0;
    dwn_counter = 0;
    
    // Get EEPROM value
    set_setpoint_from_nvm();
    adc_setpoint = get_adc_from_temp(temp_setpoint);
}

unsigned char get_status(void) {
    return status;
}

int get_temp_setpoint(void) {
    return temp_setpoint;
}

int get_adc_setpoint(void) {
    return adc_setpoint;
}

void adc_setpoint_update(void) {
    if(update_setpoint)
    {
        adc_setpoint = get_adc_from_temp(temp_setpoint);
        update_setpoint = FALSE;
    }
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
        if(temp_setpoint < MAX_SETPOINT)
        {
            temp_setpoint++;
            update_setpoint = TRUE;
            save_setpoint_to_nvm();
        }
    }
    if(DWN_BUT && dwn_counter == 0)
    {
        if(temp_setpoint > MIN_SETPOINT)
        {
            temp_setpoint--;
            update_setpoint = TRUE;
            save_setpoint_to_nvm();
        }
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


void save_setpoint_to_nvm(void) {
    // Erase the address
    NVMCON1bits.NVMREGS = 0;
    NVMADR = SETPOINT_SAVE_ADDR;
    NVMCON1bits.FREE = 1;
    NVMCON1bits.WREN = 1;
    unlock_nvm();
    
    // Erase is finished
    NVMCON1bits.FREE = 0;
    
    // Load setpoint into latch    
    NVMCON1bits.LWLO = 1;
    NVMADR = SETPOINT_SAVE_ADDR;
    NVMDAT = (unsigned short)temp_setpoint;
    unlock_nvm();
    
    // Write setpoint to NVM
    NVMCON1bits.LWLO = 0;
    unlock_nvm();
    NVMCON1bits.WREN = 0;    
}

void set_setpoint_from_nvm(void) {
    NVMCON1bits.NVMREGS = 0;
    NVMADR = SETPOINT_SAVE_ADDR;
    NVMCON1bits.RD = 1;
    temp_setpoint = (int)NVMDAT;
    
    if(temp_setpoint > MAX_SETPOINT || temp_setpoint < MIN_SETPOINT)
        temp_setpoint = DEFAULT_SETPOINT;
    
}


void unlock_nvm(void) {
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
}