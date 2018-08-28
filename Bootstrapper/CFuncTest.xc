// ------------- READS51 generated header -------------- 
// module  : Y:\Development\8051\Bootstrapper\Bootstrapper\CFuncTest.c
// created : 15:00:18, Sunday, August 26, 2018
// ----------------------------------------------------- 

char increment(char i);

char Cmain(char in){
    in =increment(in);
    return in;
}

char increment(char i){
    i++;
    return i;
}
