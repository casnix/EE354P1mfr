; Matt Rienzo, HALStrapper.asm 8/27/2018

#include "./include/asm/Registers.inc"
#include "./include/asm/ShortStack.inc"
#include "./include/asm/MacroLang.inc"

;#define OPTIMIZE
#define DEBUG

HAL     segment     code

    public  __HAL_init
rseg    HAL
    extrn  code    (__sspush)
    extrn  code    (__sspop)
    __HAL_init:
        ; 1) Setup array in memory for the 128 LED array.
        ; 2) Setup handlers in ISR for the power/reset button
        ; 3) Setup callback function for main loop/accelerometer
        ; 4) return success
        
        sspushl	#0x00
        ret
end
