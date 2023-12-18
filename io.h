/* 
 * File:   io.h
 * Author: heinrich
 *
 * Created on March 15, 2021, 9:01 PM
 */

#ifndef IO_H
#define	IO_H

#define DISP_CS_PORT    LATAbits.LATA3
#define DISP_DC_PORT    LATAbits.LATA4
#define DISP_RST_PORT   LATAbits.LATA5
#define SPI_CLK_PORT    LATCbits.LATC3
#define MOSI_PORT       PORTCbits.RC2

#define LED1    LATAbits.LATA7

#define ON_BUT  PORTBbits.RB2
#define UP_BUT  PORTBbits.RB0
#define DWN_BUT  PORTBbits.RB1

#define COLD_VALVE LATAbits.LATA1
#define COLD_VALVE_STAT PORTAbits.RA1
#define HOT_VALVE LATAbits.LATA2
#define HOT_VALVE_STAT PORTAbits.RA2


#define INIT_SPI_BUFFER    PIR1bits.SSP1IF = 1
#define RESET_SPI_BUFFER    PIR1bits.SSP1IF = 0
#define SPI_WRITE_COMPLETE  (PIR1bits.SSP1IF == 1)

#define CLEAR_SPI_COLLISION SSP1CON1bits.WCOL = 0
#define SPI_COLLISION_OCCURED SSP1CON1bits.WCOL == 1

void spi_write(unsigned char data);
void init_io(void);

#endif	/* IO_H */

