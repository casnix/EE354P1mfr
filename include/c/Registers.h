// Matt Rienzo, Registers.h 8/28/2018
// Last modified 9/28/2018

#ifndef __REGISTERS_H__
#define __REGISTERS_H__

// Don't let the decimal numbers fool you.
//   These are absolute register addresses.
#define aa0	0
#define aa1	1
#define aa2	2
#define aa3	3
#define aa4	4
#define aa5	5
#define aa6	6
#define aa7	7
#define ab0	8
#define ab1	9
#define ab2	10
#define ab3	11
#define ab4	12
#define ab5	13
#define ab6	14
#define ab7	15
#define ac0	16
#define ac1	17
#define ac2	18
#define ac3	19
#define ac4	20
#define ac5	21
#define ac6	22
#define ac7	23

//-- SFRs
#define aacc	0xe0
#define apsw	0xd0
#define abcc	0xf0

//-- Special SFRs (lol)
#define as0	0x18
#define as1	0x19
#define as2	0x1a
#define as3	0x1b
#define as4	0x1c
#define as5	0x1d
#define as6	0x1e
#define as7	0x1f

// Short stack address "register" and short stack size "register"
#define ass	0x20
#define assz	0x21
#define amsz	0x22

#define asp  0x81

//-----register pointers
// Thread available registers
char* a0 = (char*)aa0;
char* a1 = (char*)aa1;
char* a2 = (char*)aa2;
char* a3 = (char*)aa3;
char* a4 = (char*)aa4;
char* a5 = (char*)aa5;
char* a6 = (char*)aa6;
char* a7 = (char*)aa7;

// Thread descriptor registers
char* t0 = (char*)ab0;
char* t1 = (char*)ab1;
char* t2 = (char*)ab2;
char* t3 = (char*)ab3;
char* t4 = (char*)ab4;
char* t5 = (char*)ab5;
char* t6 = (char*)ab6;
char* t7 = (char*)ab7;

// R51 (Rienzo's 8051) asynchronous software thread engine state registers
char* ra0 = (char*)ac0;
char* ra1 = (char*)ac1;
char* bte = (char*)ac2;
char* btm = (char*)ac3;
char* rsrv0 = (char*)ac4;
char* ltl = (char*)ac5;
char* bts = (char*)ac6;
char* ntsd = (char*)ac7;
char* ntsm = (char*)as0;
char* nic = (char*)as1;
char* rs0 = (char*)as2;
char* rs1 = (char*)as3;
char* rs2 = (char*)as4;
char* rs3 = (char*)as5;
char* rs4 = (char*)as6;
char* rs5 = (char*)as7;

// SFRs
char* acc = (char*)aacc;
char* psw = (char*)apsw;
char* bcc = (char*)abcc;

// Short stack regs
char* ss = (char*)ass;
char* ssz = (char*)assz;
char* msz = (char*)amsz;

// Stack pointer
char* sp = (char*)asp;

#endif // __REGISTERS_H__