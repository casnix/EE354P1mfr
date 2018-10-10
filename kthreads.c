// Matt Rienzo, kthreads.c 9/28/2018
// Last modified 10/10/2018

#include "./include/c/Registers.h"
#include "./include/c/Types.h"

//
// External references

//
//

//
// Function prototypes
void kthreads_isr(void);
byte enable_threads(void);
void kthreads_compile_init(void);
//
//

byte enable_threads(void){
	
	// return false unless all conditions are true
	return FALSE;
}

void kthreads_isr(void) interrupt 0 {
	unsigned int debug_filler;
	
	debug_filler = 0;
	while(1)
		debug_filler++;
}

void kthreads_compile_init(void){ // Literally exists to satiate BL51's ruthless desire to make me unhappy
	// Literall NO code path will lead to execution of this, but BL51 freaks if this isn't here.
	
	enable_threads();
}