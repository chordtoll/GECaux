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
    TXREG=c;
    while (!TXSTAbits.TRMT);
}

void SendString_UART(char *s, int length)
{
    int i;
    for (i = 0;i < length; i++)          //loop through each character of the string
        SendChar_UART(*(s++)); //send the current character
}