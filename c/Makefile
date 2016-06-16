CFLAGS = -Wall -Werror -pedantic -Weverything -Wextra -g -std=c11
LDFLAGS = -g
TESTCOUNT=13

main: main.o nes.o instructions.o
main.o: main.c
nes.o: nes.c nes.h
instructions.o: instructions.c instructions.h

.PHONY: run clean test
run: main
	./main ../test/nestest.nes

clean:
	rm -f main *.o

test: main
	fish -c 'diff -C5 (./main ../test/nestest.nes | head -n$(TESTCOUNT) | psub) (head -n$(TESTCOUNT) ../test/nestest.log | psub)'
