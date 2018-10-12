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
extern unsigned char* a0;
extern unsigned char* a1;
extern unsigned char* a2;
extern unsigned char* a3;
extern unsigned char* a4;
extern unsigned char* a5;
extern unsigned char* a6;
extern unsigned char* a7;

// Thread descriptor registers
extern unsigned char* trid;
extern unsigned char* trps;
extern unsigned char* trml;
extern unsigned char* tseg;
extern unsigned char* trpp;
extern unsigned char* tsup;
extern unsigned char* trms;
extern unsigned char* trsv;

// R51 (Rienzo's 8051) asynchronous software thread engine state registers
extern unsigned char* ra0;
extern unsigned char* ra1;
extern unsigned char* bte;
extern unsigned char* btm;
extern unsigned char* bts;
extern unsigned char* ntsd;
extern unsigned char* ntsm;
extern unsigned char* nic;
extern unsigned char* rs0;
extern unsigned char* rs1;
extern unsigned char* rs2;
extern unsigned char* rs3;
extern unsigned char* rs4;
extern unsigned char* rs5;
extern unsigned char* rs6;
extern unsigned char* rs7;

// SFRs
extern unsigned char* acc;
extern unsigned char* psw;
extern unsigned char* bcc;

// Short stack regs
extern unsigned char* ss;
extern unsigned char* ssz;
extern unsigned char* msz;

// Stack pointer
extern unsigned char* sp;

#endif // __REGISTERS_H__