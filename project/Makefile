# makfile configuration
COMMON_OBJECTS  = moveball.o switches.o wdt_handler.o
CPU            	= msp430g2553
CFLAGS         	= -mmcu=${CPU} -Os -I./h
LDFLAGS		= -L./lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:
	(cd timerLib; make install)
	(cd lcdLib; make install)
	(make moveball.elf)

#rule
moveball.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: moveball.elf
	msp430loader.sh  $^

clean:
	(cd timerLib; make clean)
	(cd lcdLib; make clean)
	rm -rf lib h
	rm -f *.o *.elf


switches.c: switches.h
makeball.c: switches.h