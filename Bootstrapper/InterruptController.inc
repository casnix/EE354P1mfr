; ------------- READS51 generated header -------------- 
; module  : Y:\Development\8051\Bootstrapper\Bootstrapper\InterruptController.inc
; created : 11:26:26, Monday, August 27, 2018
; ----------------------------------------------------- 

; Matt Rienzo, InterruptController.inc

ien0    equ 0xa8
ien1    equ 0xe8
ipl0    equ 0xb8
iph0    equ 0xb7
ipl1    equ 0xf8
iph1    equ 0xf7

#define raisEA  orl     ien0,   #0x80
#define lowEA   anl     ien0,   #0x7f
