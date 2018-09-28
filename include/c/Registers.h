// Matt Rienzo, Registers.h 8/28/2018
// Last modified 9/28/2018

#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#define a0	0
#define a1	1
#define a2	2
#define a3	3
#define a4	4
#define a5	5
#define a6	6
#define a7	7
#define b0	8
#define b1	9
#define b2	10
#define b3	11
#define b4	12
#define b5	13
#define b6	14
#define b7	15
#define c0	16
#define c1	17
#define c2	18
#define c3	19
#define c4	20
#define c5	21
#define c6	22
#define c7	23

//-- SFRs
#define acc	0xe0
#define psw	0xd0
#define bcc	0xf0

//-- Special SFRs (lol)
#define s0	0x18
#define s1	0x19
#define s2	0x1a
#define s3	0x1b
#define s4	0x1c
#define s5	0x1d
#define s6	0x1e
#define s7	0x1f

// Short stack address "register" and short stack size "register"
#define ss	0x20
#define ssz	0x21
#define msz	0x22

#define sp  0x81

#endif // __REGISTERS_H__