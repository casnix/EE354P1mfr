// Matt Rienzo, kthreads.c 9/28/2018
// Last modified 10/14/2018

#pragma SRC

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
byte decodeThreadPriority(byte*);
//
//

//
// Global variables -- fit in the last 8 bytes of ERAM (2 + 1 + 1 + ? ) = 
unsigned int xdata threadmap _at_ (204*10); //TODO: Store this in ERAM, two bytes at 204*10
byte xdata intCount _at_ (204*10+2); //TODO: Store this in ERAM, one byte at 204*10+2
byte xdata topThread _at_ (204*10+3); //TODO: Store this in ERAM, one byte at 204*10+3
//
//

byte enable_threads(void){
	// return false unless all set up conditions are true
	return FALSE;
	
	// If we pass our test, flip BTE on and return true
	HAL_setRegister(bte, TRUE);
	return TRUE;
}

void kthreads_isr(void) interrupt 5 using 3 { // Will use TIMER2
	byte desiredThreadWaitLo;
	byte desiredThreadWaitHi;
	byte tsegFromERAM;
	byte threadInQeue = NULLBYTE;
	
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
	//		WaitHi priority makes the thread wait until the threads in the MSB of threadmap are finished, as defined by TRSV
	intCount = decodeThreadPriority(tseg);
	if((*tseg == TSEG_HOLD)){// Do nothing and just exit
		return;
	}else if((*tseg == TSEG_HIGH) && (*nic < intCount)){// We aren't quite at 15 ticks
		*nic = (*nic) + 0x01;
		return;
	}else if((*tseg == TSEG_NORMAL) && (*nic < intCount)){// We aren't quite at 10 ticks
		*nic = (*nic) + 0x01;
		return;
	}else if((*tseg == TSEG_LOW) && (*nic < intCount)){// We aren't quite at 5 ticks
		*nic = (*nic) + 0x01;
		return;
	}
	
	// 6) If we passed step five, we should switch to the next thread
	desiredThreadWaitLo = ((unsigned char)threadmap) & *trsv;
	desiredThreadWaitHi = ((unsigned char)(threadmap >> 8)) & *trsv;
	
	// The thread IN qeue is the thread after the thread AT qeue
	if(*trid == topThread){// We're at the top of our qeue, so let's wrap around (like a thread stack.  cool, huh?)
		threadInQeue = NULLBYTE;
	}else{
		threadInQeue = *trid + 0x01;
	}
	
	// Make sure that the current thread ID is not the next one too (in case of one thread, or other threads waiting)
	if(threadInQeue == *trid){
		// Do nothing but reset NIC.  It's possible that this thread will spawn another at some point, or a waiting thread will activate
		*nic = NULLBYTE;
		return;
	}
	
	// Grab TSEG from the next thread's state memory in ERAM
	if((tsegFromERAM == TSEG_WAIT) && (desiredThreadWaitLo != *trsv)){// We have not reached our desired state
		// Skip this thread, and go to the next
		threadInQeue++;
	}else if((tsegFromERAM == TSEG_WAITHI) && (desiredThreadWaitHi != *trsv)){// We have not reached our desired state
		// Skip this thread, and go to the next
		threadInQeue++;
	}
	
	// Pop the return address off the stack
#pragma ASM
	pop #0x10	; -- ra0
	pop #0x11 ; -- ra1
#pragma ENDASM
	
	//1-- Copy the current stack into the current thread's memory page.
	//2-- Copy the current short stack into the current thread's memory page
	//3-- Move the return address into the current thread's program counter in memory page
	//4-- Move the current thread's register bank 1 into the current thread's memory page
	//5-- Move the current thread's thread descriptors into the current thread's memory page
	//6-- Leave the current thread's malloc map alone -- it's already in the current thread's memory page
	
	//1-- Move the next thread's thread descriptors from page to the current thread's descriptors
	//2-- Move the next thread's register bank 1 from page into the current thread's register bank 1
	//3-- Move the next thread's program counter from page into RA0 and RA1
	//4-- Move the next thread's short stack from page into the current thread's short stack
	//5-- Move the next thread's stack from page into the current thread's stack
	//6-- Push RA0 and RA1 onto the stack
#pragma ASM
	push #0x11 ; -- ra1
	push #0x10 ; -- ra0
#pragma ENDASM
}

byte decodeThreadPriority(byte *thread_priority){
	if(*thread_priority == TSEG_HIGH)
		return 0x0F;
	else if(*thread_priority == TSEG_NORMAL)
		return 0x0A;
	else if(*thread_priority == TSEG_LOW)
		return 0x05;
	
	return 0x00;
}

///--- Keep at bottom of file.
void kthreads_compile_init(void){ // Literally exists to satiate BL51's ruthless desire to make me unhappy
	// Literally NO code path will lead to execution of this, but BL51 freaks if this isn't here.
	
	enable_threads();
}