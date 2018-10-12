// Matt Rienzo, ThreadStates.h 10/12/2018
// Last modified 10/12/2018

#ifndef __THREADSTATES_H__
#define __THREADSTATES_H__

// `Magic numbers are bad, mkay?' -- Except that all states are magic numbers at some point
#define TR_FINISH		0x00
#define TSEG_HIGH		0xFF
#define	TSEG_HOLD		0xEE
#define TSEG_NORMAL	0xCC
#define TSEG_LOW		0xBB
#define TSEG_WAIT		0xAA
#define TSEG_WAITHI	0xDD

#endif
