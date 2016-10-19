try: bc.o
	cc bc.o -o try
bc.o: bc.c bc.h
	cc -Wall -c bc.c
