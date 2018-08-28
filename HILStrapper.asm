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
    ; __HIL_init : initializes hardware components, and defines functions/callbacks for hardware
    ;   manipulate by the HAL.
    ; args: none
    ; rets: SS(#retval) -- Immediate byte off short stack to tell __entry whether or not we failed.
	__HIL_init:
        ; 1) Check battery voltage
        acall   __HIL_enable_ADC
        lowEA                               ; Disable interrupts for while we check devices on ADC
        sspushl(#0x00)                      ; Channel byte for ADC/Battery voltage
        acall   __HIL_select_ADCCh
        acall   __HIL_enable_ADCCollect     ; Enable ADC collection on the channel for the battery
        acall   __HIL_check_batt_voltage    ; Check battery voltage
        sspop(acc)
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
#ifdef  DEBUG
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
#ifdef      OPTIMIZE        ; We don't want to have a looping simulation because there's not an ADC in the simulator
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
        sspushl(#0x00)
        ret

    ; __HIL_disable_batterylo : Turns on BATT_LOW led, and red square.
    ; args: none
    ; rets: SS(#0xff)
    __HIL_disable_batterylo:
        ; Turn on battery low light
        ; Turn on red square
        sspushl(#0xff)
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
        sspushl(0x00)
  		ret
		
	main:
		; Order of operation:
		ret
		
		
end
