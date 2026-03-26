/*
 *  main.cpp
 *
 *  Hello-world UART transmitter for FRDM-MCXA153 using r01lib Serial class
 *
 *  Intended as the "Target" side exerciser for the u2u UART bridge.
 *  Continuously transmits a fixed test string so the bridge can be
 *  verified by observing the output on the PC side.
 *
 *    UART : D1(TX) / D0(RX)  115200 baud
 *
 *  Wiring (connect to u2u bridge board):
 *    FRDM D1 (TX) --> Bridge D0 (RX)
 *    GND          --> common GND
 */

#include "r01lib.h"

// UART channel connected to the u2u bridge (Target side)
Serial	uart( D1, D0, 115200 );

// Test string transmitted repeatedly
const char* str = "Living is easy with eyes closed. Misunderstanding all you see.\r\n";

int main( void )
{
	// Transmit the test string in an infinite loop
	while ( true )
		uart.printf( str );
}
