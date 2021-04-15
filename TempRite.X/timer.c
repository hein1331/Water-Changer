#include <xc.h>
#include "timer.h"

void init_timer(void) {
    // Set up timer
    RESET_TIMER
    INTCON1bits.T0IE = 1;
}