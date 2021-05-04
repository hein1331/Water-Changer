#include <xc.h>

#include "commondefines.h"
#include "io.h"
#include "display.h"
#include "buttons.h"
#include "temperature.h"
#include "temp_regulator.h"

const unsigned char NUM_ARRAY[11][7] =   {  { ON,ON,ON,ON,ON,ON,OFF },    // 0
                                            { OFF,ON,ON,OFF,OFF,OFF,OFF },    // 1
                                            { ON,ON,OFF,ON,ON,OFF,ON },    // 2
                                            { ON,ON,ON,ON,OFF,OFF,ON },    // 3
                                            { OFF,ON,ON,OFF,OFF,ON,ON },    // 4
                                            { ON,OFF,ON,ON,OFF,ON,ON },    // 5
                                            { ON,OFF,ON,ON,ON,ON,ON },    // 6
                                            { ON,ON,ON,OFF,OFF,OFF,OFF },    // 7
                                            { ON,ON,ON,ON,ON,ON,ON },    // 8
                                            { ON,ON,ON,OFF,OFF,ON,ON }, // 9
                                            { OFF,OFF,OFF,OFF,OFF,OFF,OFF }}; //OFF

unsigned char num_toggle = DIG_1_EN;
short dp_flash = 0;

volatile unsigned char dp_stat = OFF;

void init_display(void) {
    // Initialize segments
    SEG_A = OFF;
    SEG_B = OFF;
    SEG_C = OFF;
    SEG_D = OFF;
    SEG_E = OFF;
    SEG_F = OFF;
    SEG_G = OFF;

    // Initialize Decimal Point
    DP = OFF;
    
    DIG_1 = !num_toggle;
    DIG_2 = num_toggle;
}


void update_display(void) {
    // Set the number
    int dig_1_num = 0;
    int dig_2_num = 0;
    int num = GET_TEMP;
    
    // Limit reading
    if(num > 99)
        num = 99;
    
    // Calculate first digit
    int dig_1 = (num / 10) % 10;
    if(dig_1 == 0)
        dig_1_num = DIG_OFF;
    else
        dig_1_num = dig_1;
    
    // Calculate second digit
    dig_2_num = num - (dig_1*10);
    
    // Set the decimal point status
    dp_stat = get_status();
    
    // Calculate temp diff to see if the light should flash
    int temp_diff = get_temp_setpoint() - get_temperature();
    int on_temp = (temp_diff <= TEMP_DIFF && temp_diff >= -TEMP_DIFF);
    
    if(dp_stat == ON && on_temp)
        dp_stat = FLASH;
    
    int num_to_set = 0;
    
    num_toggle = !num_toggle;
    
    
    
    DIG_1 = 0;
    DIG_2 = 0;
    
    if(num_toggle == DIG_1_EN)
    {
        DP = OFF;
        num_to_set = dig_1_num;
    }
    else
    {
        num_to_set = dig_2_num;
        // Decimal point processing
        if(dp_stat == FLASH)
        {
            dp_flash++;
            DP = dp_flash >= FLASH_SPEED;

            if(dp_flash >= FLASH_SPEED*2)
                dp_flash = 0;
            
        }
        else
            DP = dp_stat;
    }

    SEG_A = NUM_ARRAY[num_to_set][0];
    SEG_B = NUM_ARRAY[num_to_set][1];
    SEG_C = NUM_ARRAY[num_to_set][2];
    SEG_D = NUM_ARRAY[num_to_set][3];
    SEG_E = NUM_ARRAY[num_to_set][4];
    SEG_F = NUM_ARRAY[num_to_set][5];
    SEG_G = NUM_ARRAY[num_to_set][6];

    DIG_1 = !num_toggle;
    DIG_2 = num_toggle;
}
