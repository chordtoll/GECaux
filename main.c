/* 
 * File:   main.c
 * Author: asent
 *
 * Created on August 8, 2018, 5:02 PM
 */

#include <xc.h>
#include "pic16f689.h"
#include "UART.h"
#include "GPIO.h"

/*
 * 
 */
int main() {
    InitUART();
    InitGPIO();
    //16000000/(64*(25+1))

    int i;
    while (1) 
    {
       // while (!PORTAbits.RA2);
        for(int num = 48; num < 122; num++)
        {
        SendChar_GPIO(num,1);
        SendChar_UART(num);
        }
        /*if(PORTCbits.RC0)
        {
            SendChar_UART('1');
        }
        else if(PORTCbits.RC1)
        {
            SendChar_UART('2');
        }
        else if(PORTCbits.RC2)
        {
            SendChar_UART('3');
        }
        else if(PORTCbits.RC3)
        {
            SendChar_UART('4');
        }
        else if(PORTCbits.RC4)
        {
            SendChar_UART('5');
        }
        else if(PORTCbits.RC5)
        {
            SendChar_UART('6');
        }
        else if(PORTCbits.RC6)
        {
            SendChar_UART('7');
        }
        else if(PORTCbits.RC7)
        {
            SendChar_UART('8');
        }*/
        
        /*SendChar_UART(PORTC);
        while (PORTAbits.RA2);
        for(i = 0; i < 1000; i++);*/
    }
    return 0;
}

