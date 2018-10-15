// Matt Rienzo, eram_map.h 10/14/2018
// Last modified 10/14/2018

/*************************************************************************
*	This header file describes the ERAM memory space for each of the ten   *
* possible threads in the R51 thread pool.                               *
*                                                                        *
*-------POOL DESCRIPTION-------------------------------------------------*
*Variables used in description:                                          *
*     # -> The number/id of any thread                                   *
* At XDATA offset 0x00CC*# is the base memory address of each thread's   *
* memory space.  Within the bounds of 0x00CC*# through 0x00CC*#+79 is    *
* the space used to preserve and swap each thread's stack space.  Within *
* 0x00CC*#+79 through 0x00CC*#+89 are ten bytes used to preserve and     *
* swap each thread's short stack space (which is an artificial software  *
* defined stack I wrote so that assembly routines can avoid messing up   *
* C stack data or return addresses).  At 0x00CC*#+89 are two bytes which *
* are used to store the program counter for each thread every time the   *
* R51 kernel decides to switch to another thread of execution.  At the   *
* address at 0x00CC*#+91 are eight bytes used to preserve and swap       *
* register bank 0 for each thread.  At 0x00CC*#+99 are eight more bytes  *
* used to preserve and swap register bank 1, which are used to describe  *
* the thread (things like thread state, priority, messages, etc.).  At   *
* 0x00CC*#+107 are 96 bytes which are used by kmalloc() as a map to      *
* control memory access to the EEPROM for each thread.                   *
*                                                                        *
*-------MEMORY SUMMARY---------------------------------------------------*
*Variables used in description:                                          *
*     # -> The number/id of any thread                                   *
* Offset       Short description                                         *
* 0x00CC*#     Base offset of thread memory, also start of stack memory  *
* 0x00CC*#+79  Base offset of short stack memory                         *
* 0x00CC*#+89  Program counter swap bytes                                *
* 0x00CC*#+91  Register bank 0 swap spots                                *
* 0x00CC*#+99  Register bank 1 swap spots, used to describe each thread  *
* 0x00CC*#+107 Memory map for use in memory allocation by kmalloc()      *
*************************************************************************/

#ifndef __ERAM_MAP_H__
#define __ERAM_MAP_H__



#endif //__ERAM_MAP_H__