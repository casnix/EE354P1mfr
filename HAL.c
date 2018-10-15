// Matt Rienzo, HAL.c 10/14/2018
// Last modified 10/14/2018

#include "./include/c/Registers.h"
#include "./include/c/Types.h"
#include "./include/HIL/LockedRegs.h"

//
// Function prototypes
boolean HAL_setRegister(char, byte); // Returns true if successful, returns false if the register is protected
																						// by the HIL upon compile.  For example, HIL adds SP to the list of locked
																						// registers, so a call like HAL_setRegister(sp, 0xAC) would do nothing but
																						// return false.
byte HAL_getRegister(char);
//
//

// HAL_setRegister(char, byte) -- Sets a register's value if it's an unlocked register
//-- args: char register, byte value
//rr rets: TRUE if successful, FALSE if locked.
boolean HAL_setRegister(char reg, byte val){
	boolean stateOnSet;
	
	stateOnSet = HIL_isRegisterLocked(reg);
	if(stateOnSet) // if stateOnSet == TRUE, then the register is locked and we won't write to it
		return FALSE;
	
	*(reg) = val;
	return TRUE;
}