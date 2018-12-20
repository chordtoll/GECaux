/* 
 * File:   main.c
 * Author: asent
 *
 * Created on August 8, 2018, 5:02 PM
 */
// PIC16F689 Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = EXTRCCLK  // Oscillator Selection bits (RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include <xc.h>
#include "pic16f689.h"
#include "UART.h"
#include "GPIO.h"
#include "Watchdog.h"

char TERMINATE_M[] = {0x7E,0x00,0x10,0x17,0x03,0x00,0x13,0xA2,0x00,0x40,0xA5,0x42,0xD5,0xFF,0xFE,0x02,0x44,0x31,0x05,0xBB};
char SUCCESS_M[] = {0x7E,0x00,0x0F,0x97,0x03,0x00,0x13,0xA2,0x00,0x40,0xA5,0x42,0xD5,0xFF,0xFE,0x44,0x31,0x00,0x42};

int main() {
    InitUART();
    InitGPIO();
    InitWatchdog();
    char result = 0;
    //16000000/(64*(25+1))

    while (1) 
    {
       // while (!PORTAbits.RA2);
        result = SendChar_GPIO(0,0);
        if(result == 106)
        {
            SendString_UART(TERMINATE_M, 20);
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

