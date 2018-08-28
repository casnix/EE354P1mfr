// ------------- READS51 generated header -------------- 
// module  : Y:\Development\8051\Bootstrapper\Bootstrapper\CFuncTest.c
// created : 15:00:18, Sunday, August 26, 2018
// ----------------------------------------------------- 

// Matt Rienzo, CFuncTest.c 8/25/2018

#define MODIFIED_C0

#define ENTRYMODE_ASM

char increment(char i);

char Cmain(char in){
    in =increment(in);
    return in;
}

char increment(char i){
    i++;
    return i;
}
