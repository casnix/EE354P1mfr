// Matt Rienzo, Registers.c 9/28/2018
// Last modified 9/28/2018

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
#define asp  0x81

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

// Thread available registers
// bank 0
unsigned char* a0 = (unsigned char*)aa0;
unsigned char* a1 = (unsigned char*)aa1;
unsigned char* a2 = (unsigned char*)aa2;
unsigned char* a3 = (unsigned char*)aa3;
unsigned char* a4 = (unsigned char*)aa4;
unsigned char* a5 = (unsigned char*)aa5;
unsigned char* a6 = (unsigned char*)aa6;
unsigned char* a7 = (unsigned char*)aa7;

// Thread descriptor registers
// bank 1
unsigned char* trid = (unsigned char*)ab0;
unsigned char* trps = (unsigned char*)ab1;
unsigned char* trml = (unsigned char*)ab2;
unsigned char* tseg = (unsigned char*)ab3;
unsigned char* trpp = (unsigned char*)ab4;
unsigned char* tsup = (unsigned char*)ab5;
unsigned char* trms = (unsigned char*)ab6;
unsigned char* trsv = (unsigned char*)ab7;

// R51 (Rienzo's 8051) asynchronous software thread engine state registers
// bank 2
unsigned char* ra0 = (unsigned char*)ac0;
unsigned char* ra1 = (unsigned char*)ac1;
unsigned char* bte = (unsigned char*)ac2;
unsigned char* btm = (unsigned char*)ac3;
unsigned char* nic = (unsigned char*)ac4;
unsigned char* bts = (unsigned char*)ac5;
unsigned char* ntsd = (unsigned char*)ac6;
unsigned char* ntsm = (unsigned char*)ac7;
// bank 3
unsigned char* rs0 = (unsigned char*)as0;
unsigned char* rs1 = (unsigned char*)as1;
unsigned char* rs2 = (unsigned char*)as2;
unsigned char* rs3 = (unsigned char*)as3;
unsigned char* rs4 = (unsigned char*)as4;
unsigned char* rs5 = (unsigned char*)as5;
unsigned char* rs6 = (unsigned char*)as6;
unsigned char* rs7 = (unsigned char*)as7;

// SFRs
unsigned char* acc = (unsigned char*)aacc;
unsigned char* psw = (unsigned char*)apsw;
unsigned char* bcc = (unsigned char*)abcc;

// Short stack regs
unsigned char* ss = (unsigned char*)ass;
unsigned char* ssz = (unsigned char*)assz;
unsigned char* msz = (unsigned char*)amsz;

// Stack pointer
unsigned char* sp = (unsigned char*)asp;
