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
    InitUART();     //initialize UART
    InitGPIO();     //initialize GPIO
    InitWatchdog(); //initialize watchdog

    while (1) 
    {
        if(ReadString_GPIO("CUT"))                //if "CUT" was received over GPIO
        {
            ExchangeChar_GPIO('?',1);             //send a '?' over GPIO
            ResetWatchdog();                      //reset the watchdog
            if(ReadString_GPIO("DO_IT"))          //if "DO_IT" was received over GPIO
            {
                ResetWatchdog();                  //reset the watchdog
                SendString_UART(TERMINATE_M, 20); //send the terminate message over UART
                
                // this is where we wait for a response from XBeeR
                
                ExchangeChar_GPIO('K',1);         //send a 'K' over GPIO
            }
        }
    }
    return 0;
}

