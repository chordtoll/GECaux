#include "pic16f689.h"
void InitWatchdog(void)
{
    WDTCONbits.WDTPS3 = 0;      //set Watchdog timer to time out after 32 seconds
    WDTCONbits.WDTPS2 = 1;
    WDTCONbits.WDTPS1 = 1;
    WDTCONbits.WDTPS0 = 0;
    WDTCONbits.SWDTEN = 1;      //enable the watchdog timer
}

void ResetWatchdog(void)
{
    __asm("CLRWDT;"); //clear the watchdog timer
}
