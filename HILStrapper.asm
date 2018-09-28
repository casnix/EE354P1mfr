; Matt Rienzo, HILStrapper.inc 8/25/2018

#include "./include/asm/Registers.inc"
#include "./include/asm/ShortStack.inc"
#include "./include/asm/ADC.inc"
#include "./include/asm/InterruptController.inc"
#include "./include/asm/MacroLang.inc"

#define OPTIMIZE
;#define DEBUG
#define	DEBUGGER

HIL		segment	code
	
public	__HIL_init
#ifdef      DEBUG
public	__HIL_C_test
#endif
rseg	HIL
    extrn  code    (__sspop)
    extrn  code    (__sspush)
    ; __HIL_init : initializes hardware components, and defines functions/callbacks for hardware
    ;   manipulate by the HAL.
    ; args: none
    ; rets: SS(#retval) -- Immediate byte off short stack to tell __entry whether or not we failed.
	__HIL_init:
        ; 1) Check battery voltage
#ifdef		DEBUGGER
		push	acc
		mov		a,		#0xEE
		mov		a,		#0x00
		mov		a,		#0xEE
		mov		a,		#0x00
		mov		a,		#0xEE
		mov		a,		#0x00
		pop		acc
#endif
        acall   __HIL_enable_ADC
        lowEA                               ; Disable interrupts for while we check devices on ADC
        sspushl	#0x00                      ; Channel byte for ADC/Battery voltage
        acall   __HIL_select_ADCCh
        acall   __HIL_enable_ADCCollect     ; Enable ADC collection on the channel for the battery
        acall   __HIL_check_batt_voltage    ; Check battery voltage
        sspop	acc
        cjne    a,          #0x00,  HIL_init_fail
        
        ; 2) Turn on accelerometer



    ; __HIL_enable_ADC : Turns on and resets ADC
    ; args: none
    ; rets: none
    __HIL_enable_ADC:
        ; 1) Turn on ADC.
        mov     adcf,       #0x00   ; reset
        mov     adcf,       #0x01
        mov     adcon,      #0x20
        mov     adclk,      #0x00
#ifdef      DEBUG
        mov     c7,         adcf
        mov     c6,         adcon
        mov     c5,         adclk
#endif
        ret

    ; __HIL_select_ADCCh : Selects the active ADC channel
    ; args: SS(#channel)    -- byte on short stack
    ; rets: none
    __HIL_select_ADCCh:
        ; battery voltage/division will be routed to ADC channel 0
        anl     adcon,      #0xf8   ; Reset ADC channel selection
        orl     adcon,      #0x00   ; Select channel 0
        orl     adcon,      #0x20   ; Select standard mode
        ret

    ; __HIL_enable_ADCCollect : Enables ADC collection on selected channel
    ; args: none
    ; rets: none
    __HIL_enable_ADCCollect:
        ; Start the ADC collection
        orl     adcon,      #0x08   ; Enable ADC collectors
        ret

    ; __HIL_check_batt_voltage : Checks the battery voltage
    ; args: none
    ; rets: SS(#retval)     -- byte 0x00 for success, 0xff for fail
    __HIL_check_batt_voltage:
        push    acc
    hsWdbADCON:
        mov     a,          adcon
        anl     a,          0x10
        cjne    a,          0x10,   hsWdbADCON

        ; Voltage check
#define     MINIMUM_BATT_VOLTAGEh   0x0f    ; will change
#define     MINIMUM_BATT_VOLTAGEl   0xFF    ; will change
        push    bcc
#ifdef      DEBUG
        mov     a,          #0xff
        mov     a,          #0x00
        mov     a,          #0xff
#endif
#ifdef      OPTIMIZE        
		; We don't want to have a looping simulation because there's not an ADC in the simulator
        ; For #n > a, subb a, #n sets the carry flag
        ; For #n < a, subb a, #n clears the carry flag
        ; For #n == a, subb a, #n clears the carry flag

        ; For HIL, we only check if the battery is too low to operate and then we shut down
        mov     a,          #MINIMUM_BATT_VOLTAGEh      ; Check the upper 8 MSB
        cjne    a,          addh,   hsWdbBATT
        sjmp    __HIL_disable_batterylo                 ; addh == MINIMUM_BATT_VOLTAGEh, so we're on the line
    hsWdbBATT:
        clr     c
        subb    a,          addh                        ; Try to set C
        mov     a,          psw
        anl     a,          0x80                        ; Check if the carry bit is set
        cjne    a,          0x80,   __HIL_disable_batterylo
        ; If we get here we're fine.
        clr     c
#endif        
        pop     bcc
        pop     acc
        sspushl	#0x00
        ret

    ; __HIL_disable_batterylo : Turns on BATT_LOW led, and red square.
    ; args: none
    ; rets: SS(#0xff)
    __HIL_disable_batterylo:
#ifdef		DEBUGGER
		; Spell out `BATTERY LO' in hex for the debugger
		mov		s7,			#0xBA
		mov		s6,			#0x11
		mov		s5,			#0xE5
		mov		s4,			#0x70
		mov		s3,			#0x00
		mov		s2,			#0x10
#endif

		; Move RETADDR to top of stack again
		pop		bcc
		pop		acc
        ; Turn on battery low light
        ; Turn on red square
        sspushl	#0xff
        ret


        
        ; 3) Turn on accelerometer
        ; 4) Switch interrupts?
        ; 5) Return success
        ; Handler for turning on LEDs
        ; Handler for LED array
        ; Handler for power touch button
        ; Handler for battery power measuring
        ; Handler for accelerometer
        ; Handler for vibration motor
	
	HIL_init_fail:
#ifdef		DEBUGGER
		; Spell out `INIT FAIL' in hex for the debugger
		mov		s7,			#0x14
		mov		s6,			#0x17
		mov		s5,			#0x00
		mov		s4,			#0xFA
		mov		s3,			#0x11
		mov		s2,			#0x00
#endif

        sspushl	#0xff
#ifdef		DEBUGGER
		; Spell out `RETURN' in hex for the debugger
		mov		s7,			#0x2E
		mov		s6,			#0x73
		mov		s5,			#0x27
		mov		s4,			#0xEE
		mov		s3,			#0xEE
		mov		s2,			#0xEE
#endif
		
        ret
	
#ifdef      DEBUG        
__HIL_C_test:
        mov		a7,		#0xe4
		; Order of operation:
		ret
#endif
		
		
end
