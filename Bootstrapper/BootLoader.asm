; ------------- READS51 generated header -------------- 
; module  : Y:\Development\8051\Bootstrapper\Bootstrapper\BootLoader.asm
; created : 17:04:29, Saturday, August 25, 2018
; ----------------------------------------------------- 
;-- Matt Rienzo, BootLoader.asm 8/25/2018
#include "../include/asm/Registers.inc"
#include "../include/asm/ShortStack.inc"

;#define OPTIMIZE
#define DEBUG

#define sspush(x)   push    x   \
    lcall   __sspush
#define sspop(x)    lcall   __sspop \
    pop     x
#define sspushl(N)  mov     s0,     #N  \
    push    s0      \
    lcall   __sspush

;-- Segment declaration
setup	segment	code
boot	segment	code
exit	segment	code
memory	segment	code

;-- Segment definition
    public  __sspush
    public  __sspop
rseg	memory
	__sspush:  ; Takes a byte off the top of the stack and moves it to the short stack
		; Increment our short stack index
		; if([msz]-[ssz] == 0) [ssz] = 0;
#ifdef      OPTIMIZE
        mov     a,      ssz
#endif
#ifdef      DEBUG
        mov     s7,     ssz
        mov     a,      s7
#endif
        add     a,      #0x01
#ifdef      DEBUG
        mov     s6,     msz
        subb    a,      s6
#endif
#ifdef      OPTIMIZE
        subb    a,      msz
#endif
        
        cjne    a,      #0x00,  __sspush_continue
		
		; Reset our ssz, wrapping our stack
		mov		ssz,	#0x00
	
	__sspush_continue:
		; Set our offset
		; &s7 = ss+[ssz]
#ifdef      OPTIMIZE
        mov     a,      #ss
#endif
#ifdef      DEBUG
        mov     s7,     #ss
        mov     a,      s7
#endif
        add     a,      ssz
#ifdef      DEBUG
        mov     s7,     a
#endif
		
        ; Preserve our callback/ret address
        pop     s7
        pop     s6
        
        ; Argument
        pop     s5
        mov     r0,     a
        mov     @r0,    s5

        push    s6
        push    s7
		ret
		
	__sspop:   ; Takes a byte off the top of the short stack and moves it to the stack
#ifdef      OPTIMIZE
        mov     a,      #ss
#endif
#ifdef      DEBUG
		mov		s7,		#ss
		mov		s6,		ssz
        mov     a,      s7
#endif
        add     a,      ssz

        ; Preserve callback/ret address
        pop     s1
        pop     s2

        mov     r0,     a
        mov     s3,     @r0
        push    s3 ; Return byte
		
		; Check if our offset is 0

        mov     a,      ssz
        cjne    a,      #0x00,  __sspop_continue
        add     a,      #0x01
#ifdef      DEBUG
        mov     ssz,    a
#endif
		
	__sspop_continue:
        subb    a,      #0x01
#ifdef      DEBUG
        mov     ssz,    a
#endif
		
        ; Callback/ret address
        push    s2
        push    s1
		ret
		
    public  __setup		
rseg	setup
	__setup:
		;---SHORT STACK
		mov		ss,		#0x23
		mov		ssz,	#0x00
		mov		msz,	#0x20
		; The last slot in the short stack will be #([ss]+[msz])
		
		;---STACK
		; Set SP to after the last slot in short stack
		mov		a,		ss
		add		a,		msz
		inc		a
		mov		sp,		a
		
		; enter our program
		ljmp	__entry
		
		
rseg	boot
	extern		code	__HIL_init
	extern		code	__HAL_init
	extern		code	_Cmain
	__entry:
	; Do three things:	(1) tell the Hardware Interaction Layer to initialize
	;					(2) tell the Hardware Abstration Layer to initialize
	;					(3) jump into the main program
		lcall	__HIL_init	; pushes return code onto ss
		sspop(acc)
		cjne	a,		#0x00,	__entry_HIL_error
		
		lcall	__HAL_init
		sspop(acc)
		cjne	a,		#0x00,	__entry_HAL_error
		
        mov     a,      #0xe4
		lcall	_Cmain
		sspop(acc)
		cjne	a,		#0x00,	__entry_main_error
		
		ljmp	__shutdown
		
	__entry_HIL_error:	; Turn on ERR LED
	__entry_HAL_error:	; Turn on ERR LED and batt_too_low square
	__entry_main_error:	; Turn on ERR LED and white square
		
		
rseg	exit
	__shutdown:
		; Endless looooooop
		ajmp	__shutdown
end
