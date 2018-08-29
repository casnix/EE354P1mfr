// ------------- READS51 generated header -------------- 
// module  : Y:\Development\8051\Bootstrapper\Bootstrapper\CFuncTest.c
// created : 15:00:18, Sunday, August 26, 2018
// ----------------------------------------------------- 

// Matt Rienzo, CFuncTest.c 8/25/2018
// Last modified 8/29/2018
//#include <sfr51.h>
//#include "./include/c/Registers.h"

//#define     OPTIMIZE
#define     DEBUG

extern unsigned char _HIL_C_test(unsigned char);
char increment(char i);

unsigned char test(char q){
	q--;
	return q;
}

char _Cmain(){
		unsigned char in = _HIL_C_test(0xff);
		unsigned char qi = test(0x00);
    return in;
}

char increment(char i){
    i++;
    return i;
}
