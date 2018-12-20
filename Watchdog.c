#include "pic16f689.h"
void InitWatchdog(void)
{
    WDTCON |= 1;      //enable the watchdog timer
}

void ResetWatchdog(void)
{
    __asm("CLRWDT;"); //clear the watchdog timer
}
