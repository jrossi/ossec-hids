# Makefile for sha2
# Jeremy Rossi <jeremy@jeremyrossi.com>
# http://www.ossec.net/hids/

PT=../../



all: sha2 sha2speed


sha2.o: sha2.c

sha2: sha2.o sha2prog.c
		gcc sha2.o sha2prog.c -o sha2

sha2speed: sha2.o sha2speed.c
		gcc sha2.o sha2speed.c -o sha2speed

clean:
		rm  *.o sha2 sha2speed

check: sha2 
		perl sha2test.pl
