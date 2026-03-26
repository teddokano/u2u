#include "r01lib.h"

Serial	uart( D1, D0, 115200 );

const char* str = "Living is easy with eyes closed. Misunderstanding all you see.\r\n";

int main( void )
{
	while ( true )
		uart.printf( str );
}
