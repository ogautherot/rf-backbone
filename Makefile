
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
AS=arm-none-eabi-as

ASFLAGS=-mthumb -mcpu=cortex-m0plus -g
OPT=-Os
CFLAGS=-g ${OPT} -Iinclude -Iinclude/usbd \
		-mthumb -mcpu=cortex-m0plus -Wall -Wextra -flto
CXXFLAGS=${CFLAGS} -fno-exceptions
LDFLAGS=-nostdlib -g -flto -Wl,-Map=${TARGET}.map -Wl,--cref \
		-Wl,--gc-sections \
        -Wl,-print-memory-usage -mcpu=cortex-m0plus -mthumb \
        -T ld/lpc11u67.ld -flto
LIBS=-lgcc -lc

OBJS=obj/bootstrap_lpc11u6x.o  obj/aeabi_romdiv_patch.o \
	obj/crp.o \
	obj/at25df641.o obj/enc28j60.o obj/mrf49xa.o \
	obj/lpc_ssp.o obj/lpc_ct32.o \
	obj/sysinit_lpc11u6x.o obj/main.o obj/event.o obj/systick.o \

#	obj/irq_stubs.o 
#	obj/cdc_desc.o obj/cdc_main.o obj/cdc_vcom.o \

TARGET=rf-backbone.elf

.PHONY: all debug clean

all: ${TARGET}

${TARGET}:	${OBJS}
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o $@ ${OBJS} ${LIBS} -Wl,-Map,${TARGET}.map 

obj/%.o:	src/%.c
	${CC} ${CFLAGS} -c -o $@ $<

obj/%.o:	src/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

obj/%.o:	src/%.s
	${AS} ${ASFLAGS} -c -o $@ $<

clean:
	rm -f obj/* ${TARGET} ${TARGET}.map

debug:
	gdb-multiarch -ix gdbinit ${TARGET}

