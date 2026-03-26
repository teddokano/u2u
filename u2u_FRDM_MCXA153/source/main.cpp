/*
 *  main.cpp
 *
 *  UART bridge sample for FRDM-MCXA153 using r01lib Serial class
 *
 *  Forwards data bidirectionally between two UART channels:
 *
 *    PC side  : LPUART0  USBTX(P0_3) / USBRX(P0_2)  115200 baud
 *    Target   : LPUART2  D1(TX)      / D0(RX)       115200 baud
 *
 *  Data flow:
 *    PC     --> FRDM (LPUART0 RX) --> forwarded to LPUART2 TX --> Target
 *    Target --> FRDM (LPUART2 RX) --> forwarded to LPUART0 TX --> PC
 *
 *  All forwarding is done inside RX interrupt callbacks.
 *  The TX ring buffer in Serial ensures putc() is non-blocking,
 *  so calling it from an ISR is safe.
 *
 *  Wiring:
 *    FRDM P0_3 (USBTX) --> USB-Serial adapter RX  (PC side)
 *    FRDM P0_2 (USBRX) --> USB-Serial adapter TX  (PC side)
 *    FRDM D1   (TX)    --> Target device RX
 *    FRDM D0   (RX)    --> Target device TX
 *    GND               --> common GND
 *
 *  Prerequisites:
 *    - r01lib built with semihosting enabled (SEMIHOST_OPERATION defined)
 *      For standalone FRDM operation, do not use printf() as it will
 *      block execution when no debugger is attached
 */

#include "r01lib.h"

volatile bool	tx_done	= false;

// ---- UART channels ---------------------------------------------------------

Serial	pc(   USBTX, USBRX, 115200 );   // PC side
Serial	uart( D1,    D0,    115200 );   // Target
//Serial  uart( MB_TX, MB_RX, 115200 );   // Target

// ---- Prototypes ------------------------------------------------------------

void led_color_change();
void start_indicator( int colors );
void on_pc_rx( void );
void on_uart_rx( void );

// ---- main ------------------------------------------------------------------

int main( void )
{
	start_indicator( 16 );

	pc.attach(   on_pc_rx,   Serial::RxIrq );
	uart.attach( on_uart_rx, Serial::RxIrq );

	// Indicate TX/RX activity by cycling the LED color
	while ( true )
	{
		if ( tx_done )
		{
			tx_done	= false;
			led_color_change();
		}
	}
}

// ---- LED controls ----------------------------------------------------------

void led_color_change()
{
	static BusOut	rgb( RED, GREEN, BLUE );
	static uint8_t	color	= 0;

	rgb	= color++ & 0x7;
}

void start_indicator( int colors )
{
	for ( auto i = 0; i < colors; i++ )
	{
		led_color_change();
		wait( 0.05 );
	}
}

// ---- RX callbacks ----------------------------------------------------------

// PC → Target: byte received from PC, forward to uart
void on_pc_rx( void )
{
	int c;

	if ( -1 != ( c = pc.getc() ) )
	{
		uart.putc( c );
		tx_done	= true;
	}
}

// Target → PC: byte received from Target, forward to pc
void on_uart_rx( void )
{
	int c;

	if ( -1 != ( c = uart.getc() ) )
	{
		pc.putc( c );
		tx_done	= true;
	}
}
