// Matt Rienzo, HAL.h 10/14/2018
// Last modified 10/14/2018

// This header file provides the exports for HAL functions

#ifndef __HAL_H__
#define __HAL_H__

#include "./include/c/Types.h"

extern boolean HAL_setRegister(char, byte); // Returns true if successful, returns false if the register is protected
																						// by the HIL upon compile.  For example, HIL adds SP to the list of locked
																						// registers, so a call like HAL_setRegister(sp, 0xAC) would do nothing but
																						// return false.
extern byte HAL_getRegister(char);

#endif //__HAL_H__