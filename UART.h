/* 
 * File:   UART.h
 * Author: ADMIN
 *
 * Created on August 8, 2018, 6:51 PM
 */

#ifndef UART_H
#define	UART_H

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

#endif	/* UART_H */

