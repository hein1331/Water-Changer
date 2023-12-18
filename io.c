#include <xc.h>
#include "io.h"
#include "commondefines.h"

BOOL first_write = TRUE;

void init_io(void) {
    // Enable HF Occilstior
    OSCENbits.HFOEN = 1;
    
    // Set occilator frequency to 16mHZ
    OSCFRQ = 0b100;
        
    // Wait for occilator to be ready
    while(!OSCSTATbits.HFOR);
    
    // Set R0 to ADC and the rest to digital pins
    ANSELA = 0x1;
    ANSELB = 0x0;
    ANSELC = 0x0;
    
    // Init all IO to 0
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    
    // Set all of port A to outputs except RA0
    TRISA = 0x1;
    
    // Set LEDs to outputs and buttons, program pins to inputs
    TRISB = 0b11000111;
    
    // Set all of Port C to outputs
    TRISC = 0;
    
    // Init SPI
    //Disable SPI
    SSP1CON1bits.SSPEN = 0;
    
    // Setup RC3 to be SPI clock in PPS
    RC3PPS = 0x07;
    SSP1CLKPPSbits.PORT  = 0b010;
    SSP1CLKPPSbits.PIN  = 0b011;
    
    // Setup RC2 to be SPI SDO in PPS
    RC2PPS = 0x08;
            
    // Clear write collision
    CLEAR_SPI_COLLISION;
    
    // Set Flag
    RESET_SPI_BUFFER;
    
    // Set clock polarity to idle low
    SSP1CON1bits.CKP = 0;
    
    // Set clock speed to 370kHz
    SSP1CON1bits.SSPM = 0b1010;
    SSP1ADD = 0xA;
    
    // Set clock edge to transmit on low to high transition
    SSP1STATbits.CKE = 1;
    
    // Enable SPI
    SSP1CON1bits.SSPEN = 1;
}


void spi_write(unsigned char data) {
    
    if(SPI_COLLISION_OCCURED) {
        CLEAR_SPI_COLLISION;
        LED1 = 1;
    }
    
    first_write = FALSE;
    
    SSP1BUF = data;
    
    // Wait for write to complete
    while(!SPI_WRITE_COMPLETE);
    
    // Reset the buffer
    RESET_SPI_BUFFER;
    
}
