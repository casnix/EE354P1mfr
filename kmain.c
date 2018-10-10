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
void main(void);	// This memory structure gets destroyed, and it's kind of hackish
									// but Keil C51 just absolutely insists that a C function called main() be placed at 
									// 0x0000, disallowing me from setting up memory my way first.
void _kmain(void);
void dummyCodePath();
//
//

void main(){
	__setup();
	//kmain(); // This will not ever run, but BL51 will not overlay memory for kmain() if it's only called from assembly...
	dummyCodePath();
}

void _kmain(){
	// Set up 
	
	
	// THis is just filler for one debug
	sp = 0x30;
}

/// -- keep at bottom of page
void dummyCodePath(void){
	_kmain();
	kthreads_compile_init();
}