# makfile configuration
COMMON_OBJECTS  = toyArrows.o switches.o wdt_handler.o
CPU            	= msp430g2553
CFLAGS         	= -mmcu=${CPU} -Os -I./h
LDFLAGS		= -L./lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc 
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:
	(cd timerLib; make install)
	(cd lcdLib; make install)
	(make toyArrows-c.elf)
	(make toyArrows-s.elf)

#rule
toyArrows-c.elf: ${COMMON_OBJECTS} screenChange-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

toyArrows-s.elf: ${COMMON_OBJECTS} screenChange-s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load-s: toyArrows-s.elf
	msp430loader.sh $^

load-c: toyArrows-c.elf
	msp430loader.sh $^

clean:
	(cd timerLib; make clean)
	(cd lcdLib; make clean)
	rm -rf lib h
	rm -f *.o *.elf


switches.c: switches.h
toyArrows.c: switches.h
screenChange-s.o: screenChange-s.s
