set architecture armv6-m
target remote localhost:3333

mon adapter speed 1000
mon reset halt
mon mww 0x40048000 2
 mon lpc11xx.cpu configure -work-area-size 1024
mon flash write_image erase rf-backbone.elf
#mon flash verify_image rf-backbone.elf 0
file rf-backbone.elf
b main
#mon reset halt
#mon mww 0x40048000 2

