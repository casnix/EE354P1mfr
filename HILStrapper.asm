; Matt Rienzo, HILStrapper.inc 8/25/2018

#include "../include/asm/Registers.inc"
#include "../include/asm/ShortStack.inc"
#include <ADC.inc>
#include <InterruptController.inc>

#define sspush(x)   push    x   \
    lcall   __sspush
#define sspop(x)    lcall   __sspop \
    pop     x
#define sspushl(N)  mov     s0,     #N  \
    push    s0      \
    lcall   __sspush

;#define OPTIMIZE
#define DEBUG

HIL		segment	code
	
public	__HIL_init
public	main
rseg	HIL
    extern  code    __sspop
    extern  code    __sspush
	__HIL_init:
        ; 1) Turn on ADC.
        mov     adcf,       #0x01
        mov     adcon,      #0x20
        mov     adclk,      #0x00
#ifdef  DEBUG
        mov     c7,         adcf
        mov     c6,         adcon
        mov     c5,         adclk
#endif
        
        ; Disable interrupts for while we check devices on ADC
        lowEA
        ; 2) Check battery voltage.  Too low? Turn on red square and battery low LEDs.
        ; battery voltage/division will be routed to ADC channel 0
        anl     adcon,      #0xf8
        orl     adcon,      #0x00
        orl     adcon,      #0x20

        ; Start the ADC collection
        orl     adcon,      #0x08
        push    acc
    hsWdbADCON:
        mov     a,          adcon
        anl     a,          0x10
        cjne    a,          0x10,   hsWdbADCON

        ; Voltage check
#define     MINIMUM_BATT_VOLTAGEh   0x0f    ; will change
#define     MINIMUM_BATT_VOLTAGEl   0xFF
        push    bcc
#ifdef      DEBUG
        mov     a,          #0xff
        mov     a,          #0x00
        mov     a,          #0xff
    dbgloop:    
        clr     c
        mov     a,          0x0f
        subb    a,          #MINIMUM_BATT_VOLTAGEh
       ; mov     a,          c


    dbgdo:
        sjmp    dbgloop
#endif

        
        ; 3) Turn on accelerometer
        ; 4) Switch interrupts?
        ; 5) Return success
        ; Handler for turning on LEDs
        ; Handler for LED array
        ; Handler for power touch button
        ; Handler for battery power measuring
        ; Handler for accelerometer
        ; Handler for vibration motor
        sspushl(0x00)
  		ret
		
	main:
		; Order of operation:
		ret
		
		
end
