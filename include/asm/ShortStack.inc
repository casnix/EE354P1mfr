; Matt Rienzo, ShortStack.inc 8/25/2018

; The following registers I am reserving for short stack operations
s0	equ	0x18
s1	equ	0x19
s2	equ	0x1a
s3	equ 0x1b
s4	equ	0x1c
s5	equ	0x1d
s6	equ	0x1e
s7	equ	0x1f


; SHORT STACK -- see the Short Stack section after the END instruction for an explanation
;  of what this is
; Short stack address "register" and short stack size "register"
ss	equ	0x20	; short stack 0 address
ssz	equ 0x21	; short stack size (index)
msz	equ	0x22	; short stack max size (to avoid overflow, but with stack wrapping/overwrites)
