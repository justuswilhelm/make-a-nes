CFLAGS = -Wall -Werror -pedantic -Weverything -Wextra -g
LDFLAGS = -g

main: main.o nes.o instructions.o
main.o: main.c
nes.o: nes.c nes.h
instructions.o: instructions.c instructions.h

.PHONY: run clean
run: main
	./main ../test/nestest.nes

clean:
	rm -f main *.o
