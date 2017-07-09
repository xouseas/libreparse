CCOPTS =

default: printavg

recordparse.o: recordparse.c recordparse.h records.h
	$(CC) $(CCOPTS) -c recordparse.c

librecordparse.a: recordparse.o
	$(AR) rcs librecordparse.a recordparse.o

printavg: printavg.c librecordparse.a
	$(CC) $(CCOPTS) -Wall -o printavg printavg.c -L. -lrecordparse

clean:
	$(RM) recordparse.o librecordparse.a printavg

.PHONY: clean

