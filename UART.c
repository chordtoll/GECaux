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
    while(!PIR1bits.RCIF);
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

int Cutdown()
{
    int i;                               //looping variable
    char message[20];                    //holds message received from XBeeR
    WakeXBee();                          //wake the XBee up
    SendString_UART(TERMINATE_M, 20);    //send the terminate message over UART
    for(i = 0; i < 25; i++)              //loop 25 times (25 seconds)
    {
        ResetWatchdog();                 //reset the watchdog
        WaitS(1);                        //wait for 1 second
        if(DataInFIFO)                   //if data was received over UART
        {
           ReadString_UART(message, 20); //read in the message and store it
           SleepXBee();                  //put the XBee to sleep
           return ParseMessage(message); //parse the message and return status
        }
    }
    SleepXBee();                         //put the XBee to sleep
    return NO_MESSAGE;                   //return error code for no message
}

int ParseMessage(char* message)
{
    int index = 0;
    while(*message)
        if(message[index] != SUCCESS_M[index])
            return UNEXPECTED_MESSAGE;
    return SUCCESS;
}

int DataInFIFO()
{
    return PIR1bits.RCIF; //return FIFO status flag
}
