try: bc.o
	cc bc.o -o bc
	clear
bc.o: bc.c bc.h
	cc -Wall -c bc.c -o bc.o
