// Matt Rienzo, kmain.c 9/28/2018
// Last modified 10/10/2018

#include "./include/c/Registers.h"
#include "./include/c/Types.h"
#include "./include/c/kthreads.h"

#pragma NOREGPARMS

//
// External references
extern void __setup(void);
//
//

//
// Function prototypes
void main(void);	// The memory structure associated with main() gets destroyed immediately after boot,
									// and it's kind of hackish but Keil C51 just absolutely insists that a C function 
									// called main() be placed at 0x0000, disallowing me from setting up memory my way first.
void kmain(void);
void dummyCodePath();
//
//

void main(){
	__setup();
	dummyCodePath();
}

void kmain(){
	// Set up 
	
	// ensure that threading is disabled
	*bte = FALSE;
	
	// THis is just filler for one debug
	sp = 0x30;
}

/// -- keep at bottom of page
void dummyCodePath(void){
	kmain();
	kthreads_compile_init();
}