// ------------- READS51 generated header -------------- 
// module  : Y:\Development\8051\Bootstrapper\Bootstrapper\CFuncTest.c
// created : 15:00:18, Sunday, August 26, 2018
// ----------------------------------------------------- 

// Matt Rienzo, CFuncTest.c 8/25/2018
#include <sfr51.h>
#include "../include/c/Registers.h"

//#define     OPTIMIZE
#define     DEBUG

#asm
#define sspush(x)   push    x   \
    lcall   __sspush
#define sspop(x)    lcall   __sspop \
    pop     x
#define sspushl(N)  mov     s0,     #N  \
    push    s0      \
    lcall   __sspush

extern      code    __HIL_C_test
extern      code    __sspush
extern      code    __sspop
#endasm

char increment(char i);

char Cmain(char in){
#asm    
    mov     a,      #0xe1
    lcall   __HIL_C_test
    sspop(acc)
#endasm
    in =increment(in);
    return in;
}

char increment(char i){
    i++;
    return i;
}
