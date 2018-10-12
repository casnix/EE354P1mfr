// Matt Rienzo, kthreads.c 9/28/2018
// Last modified 10/10/2018

#include "./include/c/Registers.h"
#include "./include/c/Types.h"
#include "./include/c/ThreadStates.h"

//
// External references

//
//

//
// Function prototypes
void kthreads_isr(void);
byte enable_threads(void);
void kthreads_compile_init(void);
boolean decodeThreadPriority(byte);
//
//

//
// Global variables -- fit in the last 8 bytes of ERAM (2 + 1 + ? ) = 
unsigned int threadmap; //TODO: Store this in ERAM, two bytes at 204*10
unsigned char intCount; //TODO: Store this in ERAM, one byte at 204*10+2
//
//

byte enable_threads(void){
	
	// return false unless all conditions are true
	return FALSE;
}

void kthreads_isr(void) interrupt 5 using 3 { // Will use TIMER2
	byte desiredThreadWaitLo;
	byte desiredThreadWaitHi;
	
	// 1) Check if threading is even enabled
	if(*bte == FALSE) // Threads aren't enabled, so we shouldn't do anything
		return; 
	
	// 2) Check if our current thread is done with it's work
	if(*tseg == TR_FINISH){
		// unmalloc the space in TRID->malloc in ERAM, freeing the space in EEPROM
		// update threadmap string
	}
	
	// 3) Check for thread signals
	if((*bts == TRUE) && (*ntsd == *trid)){ // Is it the current thread?
		// Read signal, determine what to do with it
	}
	
	// 4) Check for priority change
	if(*tsup == TRUE){
		// Reset TSUP
		*tsup = FALSE;
		// The thread sets TSEG on it's own, so we'll compare against interrupt count in step five
	}
	
	// 5) Check interrupt counter against thread priority
	// These are more magic numbers:
	//		Hold priority is the highest, and gets all the thread power until a priority change
	//		High priority gives a thread 15 timer counts
	//		Normal priority gives a thread 10 timer counts
	//		Low priority gives a thread 5 timer counts
	//		Wait priority makes the thread wait until the thread number in TRSV finishes
	//	  WaitHigh priority makes the thread wait until the thread number in TRSV which corresponds with the MSBs
	//			in threadmap finishes
	//			If TRSV is 0xFD, then wait for all the other threads to end
	intCount = decodeThreadPriority(tseg);
	desiredThreadWaitLo = ((unsigned char)threadmap) && *trsv);
	desiredThreadWaitHi = ((unsigned char)(threadmap >> 8)) && *trsv);
	if((*tseg == TSEG_HOLD)){// Do nothing and just exit
		return;
	}else if((*tseg == TSEG_HIGH) && (*nic < intCount)){// We aren't quite at 15 ticks
		*nic++;
		return;
	}else if((*tseg == TSEG_NORMAL) && (*nic < intCount)){// We aren't quite at 10 ticks
		*nic++;
		return;
	}else if((*tseg == TSEG_LOW) && (*nic < intCount)){// We aren't quite at 5 ticks
		*nic++;
		return;
	}else if((*tseg == TSEG_WAIT)){
		
		
}

boolean decodeThreadPriority(byte *thread_priority){
	
}

///--- Keep at bottom of file.
void kthreads_compile_init(void){ // Literally exists to satiate BL51's ruthless desire to make me unhappy
	// Literally NO code path will lead to execution of this, but BL51 freaks if this isn't here.
	
	enable_threads();
}