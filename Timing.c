#include <xc.h>
#include "pic16f689.h"
#include "Watchdog.h"

#define TICK_SECONDS 1000000
void InitTimer()
{
    T1CONbits.TMR1GE = 0;  //set timer to always count
    T1CONbits.T1CKPS0 = 0; //1:1 prescaler value
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.T1OSCEN = 0; //disable LP oscillator
    T1CONbits.TMR1CS = 0;  //Internal clock (Fosc/4)
    PIR1bits.TMR1IF = 0;   //clear timer interrupt flag
}

void WaitS(int s)
{
    int i, j;
    for(i = 0; i < s; i++)                                    //loop for number of seconds
    {
        ResetWatchdog();                                     
        TMR1H = 0xFF - ((0xFFFF /4) >> 8);                    //set counter registers to start at 1/4 capacity from overflowing
        TMR1L = 0xFF - (((0xFFFF /4) << 8) >> 8);
        T1CONbits.TMR1ON = 1;                                 //start the timer
        for(j = 0; j < 16; j++)                               //loop 16 times (one period of the timer ~= 1/15.25 seconds)
        {
            while(!PIR1bits.TMR1IF){}                         //wait for the counter registers to overflow
            PIR1bits.TMR1IF = 0;                              //clear the timer overflow flag
        }
        T1CONbits.TMR1ON = 0;                                 //stop the timer
    }
}
