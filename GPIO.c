#include <xc.h>
#include "pic16f689.h"

#define OUT_DATA1 PORTCbits.RC7
#define OUT_DATA0 PORTCbits.RC6
#define OUT_TxEnable PORTCbits.RC3
#define IN_CLK0 PORTCbits.RC4
#define IN_CLK1 PORTCbits.RC5
#define IN_TxEnable PORTCbits.RC2
#define IN_DATA1 PORTCbits.RC1
#define IN_DATA0 PORTCbits.RC0

void InitGPIO() {
    
    TRISC = 0b00110111; //set each PortC pin to their corresponding directions
    ANSEL=0;            //disable analog functions on PortC
    ANSELH=0;
    OUT_TxEnable = 0;   //set transmitting flag to 0
    OUT_DATA0 = 0;
    OUT_DATA1 = 0;
}

char SendChar_GPIO(char c, char transmit) {
    unsigned int qByte = 0;    //initialize quarter-byte counter
    char result = 0;           //data received from PIC32
    
    while(IN_CLK0 || IN_CLK1){}//wait for the first clock 
    if(transmit)
      OUT_TxEnable = 1;        //set transmit enable pin
    else
      OUT_TxEnable = 0;
    do
    {   
        OUT_DATA0 = (c & (1 << (qByte * 2))) >> (qByte * 2);         //set 0th bit of current quarter-byte
        OUT_DATA1 = (c & (1 << (1 + qByte * 2))) >> (1 + qByte * 2); //set 1st bit of current quarter-byte
        if(IN_TxEnable)                                              //if the PIC32 is sending information
        {
            //store the received information into the proper quarter-byte of result
            result += (IN_DATA0 << (qByte * 2)) + (IN_DATA1 << (1 + qByte * 2));
        }
        
        unsigned int cCLK = IN_CLK0;
        while(cCLK == IN_CLK0){}
        //wait for the clock to change
        qByte = IN_CLK0 + IN_CLK1 * 2;                               //update the quarter byte counter
    }
    while(qByte !=0);
    OUT_TxEnable = 0;
    OUT_DATA0 = 0;
    OUT_DATA1 = 0;
    return result;                                                   //return the data received by the PIC32
}
