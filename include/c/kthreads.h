// Matt Rienzo, kthreads.h 9/28/2018
// Last modified 10/10/2018

#ifndef __KTHREADS_H__
#define __KTHREADS_H__

#include "./include/c/Types.h"

extern byte enable_threads(void);
extern void kthreads_compile_init(void);
extern byte decodeThreadPriority(byte*);

#endif // __KTHREADS_H__