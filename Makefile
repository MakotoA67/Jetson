#MAKEFILE

CC	= gcc
RM	= rm -f

CFLAGS	= -g -Wall -O2
LDFLAGS	= -lgpiod

TARGET	= gpio_input gpio_output

.c.o:
	${CC} -c ${CFLAGS} $<

all:	$(TARGET)

gpio_input: gpio_input.c
	${CC} -o $@ $< ${CFLAGS} ${LDFLAGS}

gpio_output: gpio_output.c
	${CC} -o $@ $< ${CFLAGS} ${LDFLAGS}

clean:
	${RM} ${TARGET} *.o *~

