; Matt Rienzo, MacroLang.inc 8/25/2018

;-- Language macros

#define xadd(x,y) \
    mov     a,      x   \
    add     a,      y   \
    mov     x,      a   

#define xsubb(x,y)   \
    mov     a,      x   \
    subb    a,      y   \
    mov     x,      a   \

#define xcjne(x,y,L)   \
    mov     a,      x       \
    cjne    a,      y,  L   
