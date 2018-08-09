#include <xc.h>

void InitUART() {
    TXSTAbits.TXEN=1;
    TXSTAbits.SYNC=0;
    RCSTAbits.SPEN=1;
}

void SendChar_UART(char c) {
    TXREG=c;
    while (!TXSTAbits.TRMT);
}