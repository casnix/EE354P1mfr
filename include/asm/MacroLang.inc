; Matt Rienzo, MacroLang.inc 8/25/2018
sspush		macro	x
	push	x
	lcall	__sspush
endm

sspop		macro	x
	lcall	__sspop
	pop		x
endm

sspushl		macro	N
	mov		s0,		N
	push	s0
	lcall	__sspush
endm