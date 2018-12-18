#include <xc.h>
#include "pic16f689.h"
void InitUART() {
    
    SPBRGH = 0;
    SPBRG = 25;
    BRG16 = 0;
    BRGH = 1;
    
    TXSTAbits.TXEN=1;
    TXSTAbits.SYNC=0;
    RCSTAbits.SPEN=1;
}

void SendChar_UART(char c) {
    int i;
    TXREG=c;
    while (!TXSTAbits.TRMT);
    for (i=0;i<10;i++);
}