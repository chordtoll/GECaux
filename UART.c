#include <xc.h>
#include "pic16f689.h"
#include "GPIO.h"
#include "watchdog.h"
#include "Timing.h"

char TERMINATE_M[] = {0x7E,0x00,0x10,0x17,0x03,0x00,0x13,0xA2,0x00,0x40,0xA5,0x42,0xD5,0xFF,0xFE,0x02,0x44,0x31,0x05,0xBB};
char SUCCESS_M[] =   {0x7E,0x00,0x0F,0x97,0x03,0x00,0x13,0xA2,0x00,0x40,0xA5,0x42,0xD5,0xFF,0xFE,0x44,0x31,0x00,0x42};
enum CUTDOWN_CODE{SUCCESS, UNEXPECTED_MESSAGE, NO_MESSAGE};

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
    while(!DataInFIFO()); //wait for data to be present in the receiving FIFO
    return RCREG;         //return the top character in the receiving FIFO
}

int DataInFIFO()
{
    return PIR1bits.RCIF; //return FIFO status flag
}

int ParseMessage(char* message)
{
    int index = 0;    //counter for message index
    while(index < 19) //loop until entire message is compared
    {
        if(message[index] != SUCCESS_M[index]) //check to see if current character of message is expected
            return UNEXPECTED_MESSAGE;         //if not, return unexpected message error
        ++index;                               //move to the next character
    }
    return SUCCESS;   //if entire message was compared successfully, return success code
}

int Cutdown()
{
    int period = 0;                      //counter for number of timer periods passed
    int index = 0;                       //counter for characters on received message
    char message[19];                    //holds message received from XBeeR
    WakeXBee();                          //wake the XBee up
    SendString_UART(TERMINATE_M, 20);    //send the terminate message over UART
    StartTimer();                        //start timer
    while(period < 47)                   //loop for 47 timer periods, 25 seconds (47 * 0.524 ~= 25)
    {
        //ResetWatchdog();                 //reset the watchdog
        while(DataInFIFO())              //if data was received over UART
        {
            message[index++] = ReadChar_UART(); //read the next character into message
            if(index > 18)                      //if message is full
            {
                SleepXBee();                    //put the XBee to sleep
                return ParseMessage(message);   //parse the message and return status
            }
        }
        if(PeriodPassed())               //if a timer period has passed
        {
            StartTimer();                //restart the timer
            ++period;                    //update period counter
        }
    }
    SleepXBee();                         //put the XBee to sleep
    if(index)                            //if some characters were read in
        return UNEXPECTED_MESSAGE;       //return error code for undexpected message
    
    return NO_MESSAGE;                   //return error code for no message
}
