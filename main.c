/* 
 * File:   main.c
 * Author: asent
 *
 * Created on August 8, 2018, 5:02 PM
 */

#include <xc.h>
#include "UART.h"
#include "GPIO.h"

/*
 * 
 */
int main() {
    InitUART();
    InitGPIO();
    while (1) {
        //while (!PORTAbits.RA2);
        SendChar_UART(0xFF);
        SendChar_UART(0x00);
        SendChar_UART(0xFF);
        SendChar_UART(PORTC);
        //while (PORTAbits.RA2);
    }
    
    return 0;
}

