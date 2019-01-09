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

void WaitS_Timer(int s)
{
    ResetWatchdog();
    TMR1H = 0;                                           //set counter registers to 0
    TMR1L = 0; 
    T1CONbits.TMR1ON = 1;                                //start the timer
    while(((TMR1H << 8) + TMR1L) < (s * TICK_SECONDS)){} //wait for the timer to reach the target time
    T1CONbits.TMR1ON = 0;                                //stop the timer
}
