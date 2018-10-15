// Matt Rienzo, LockedRegs.c 10/14/2018
// Last modified 10/14/2018

#include "include/c/Types.h"
#include "include/c/Registers.h"

//
// Function prototypes
boolean HIL_isRegisterLocked(char);
//
//

// This function returns FALSE if a register is open for access, or TRUE if it needs to be protected
// (like the stack pointer)
boolean HIL_isRegisterLocked(char reg){
	if(reg == sp)
		return TRUE;
	else if(reg == ss)
		return TRUE;
	else if(reg == ssz)
		return TRUE;
	else if(reg == msz)
		return TRUE;

	return FALSE;
}