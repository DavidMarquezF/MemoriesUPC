# generic flags
CC=avr-gcc
CPPFLAGS=-DF_CPU=16000000UL
CFLAGS=-Wall -std=c99 -Ofast -mmcu=atmega328p -fshort-enums 
LDFLAGS=-std=c99 -mmcu=atmega328p

# joining flags
FLAGS=$(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

# target device
DEVICE=/dev/ttyACM0

# sources
SRC_c:=$(wildcard *.c)
SRC:=$(wildcard *.c *.h)
SRC+=Makefile

# directives
.PHONY : all load_% picocom veryclean clean touch 

all: load_main size clean

%.s: %.c
	$(CC) $(CFLAGS) -S $<

main: $(SRC)
	$(CC) $(FLAGS) $(SRC_c) -o main

%.hex: %
	avr-objcopy -Oihex $< $@

load_%: %.hex
	avrdude -c arduino -p atmega328p -P $(DEVICE) -U $<

clean:
	rm -f *~ *.hex *.s *.o main

picocom:
	picocom -b115200 $(DEVICE)

size: main
	avr-size -C --mcu=atmega328p main

touch:
	touch $(SRC)

veryclean: clean
	rm -f README.tex README.pdf



