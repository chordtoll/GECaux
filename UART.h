/* 
 * File:   UART.h
 * Author: ADMIN
 *
 * Created on August 8, 2018, 6:51 PM
 */

#ifndef UART_H
#define	UART_H

char TERMINATE_M[] = {0x7E,0x00,0x10,0x17,0x03,0x00,0x13,0xA2,0x00,0x40,0xA5,0x42,0xD5,0xFF,0xFE,0x02,0x44,0x31,0x05,0xBB};
char SUCCESS_M[] =   {0x7E,0x00,0x0F,0x97,0x03,0x00,0x13,0xA2,0x00,0x40,0xA5,0x42,0xD5,0xFF,0xFE,0x44,0x31,0x00,0x42};
enum CUTDOWN_CODE{SUCCESS, UNEXPECTED_MESSAGE, NO_MESSAGE};

//initialize UART
void InitUART();

//send a specified character over UART
void SendChar_UART(char c);

//send a specified string over UART
void SendString_UART(char *s, int length);

//returns the first unread character in the UART receiving FIFO
char ReadChar_UART();

//stores a specified number of characters into a passed in pointer
void ReadString_UART(char *s, int length);

//returns 0 if there is no data in the input FIFO, 1 otherwise
int DataInFIFO();

//attempts a cutdown and returns a cutdown code depending on results
int Cutdown();
#endif	/* UART_H */
