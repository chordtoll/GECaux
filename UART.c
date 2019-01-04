#include <xc.h>
#include "pic16f689.h"
void InitUART() {
    
    SPBRGH = 0; //set baud rate to 9600
    SPBRG = 25;
    BRG16 = 0;
    BRGH = 1;
    
    TXSTAbits.TXEN=1;   //enable UART for transmitting and receiving in asynchronous mode
    RCSTAbits.CREN = 1;
    TXSTAbits.SYNC=0;
    RCSTAbits.SPEN=1;    
}

void SendChar_UART(char c) {
    TXREG=c;                 //place the character into the transmitting FIFO
    while (!TXSTAbits.TRMT); //wait until TXREG is empty
}

void SendString_UART(char *s, int length)
{
    int i;
    for (i = 0;i < length; i++) //loop through each character of the string
        SendChar_UART(*(s++));  //send the current character
}

char ReadChar_UART()
{
    return RCREG; //return the top character in the receiving FIFO
}

void ReadString_UART(char *s, int length)
{
    int i;
    for(i = 0; i < length; i++) //loop 'length' times
    {
        while(!PIR1bits.RCIF){} //wait for a character to be available to be read
        s[i] = RCREG;           //store the character in its appropriate index
    }
}