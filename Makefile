CC=gcc
CF=-Wall
PROG_NAME=ih-calendar

build: main.o calutil.o data.o file.o
	$(CC) $(CF) -o $(PROG_NAME) main.o calutil.o data.o file.o

test: test.o calutil.o data.o file.o
	$(CC) $(CF) -o testprog test.o calutil.o data.o file.o

main.o: main.c calendar.h
	$(CC) $(CF) -c main.c

test.o: test.c calendar.h
	$(CC) $(CF) -c test.c

calutil.o: calutil.c calendar.h
	$(CC) $(CF) -c calutil.c

data.o: data.c calendar.h
	$(CC) $(CF) -c data.c

file.o: file.c calendar.h
	$(CC) $(CF) -c file.c

clean:
	rm -f *.o
