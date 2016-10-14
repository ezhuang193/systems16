COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: mymalloc Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 
.PHONY: all
.PHONY: clean

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(CFLAGS) -c mymalloc.c

main.o: main.c mymalloc.h
	$(COMPILER) $(CFLAGS2) -c main.c
	
mymalloc: mymalloc.o main.o
	$(COMPILER) $(CFLAGS) -o mymalloc main.o mymalloc.o


Test1.o: Test1.c
	$(COMPILER) $(CFLAGS2) -c Test1.c

Test1: mymalloc.o Test1.o
	$(COMPILER) $(CFLAGS) -o Test1 Test1.o mymalloc.o


Test2.o: Test2.c
	$(COMPILER) $(CFLAGS2) -c Test2.c

Test2: mymalloc.o Test2.o
	$(COMPILER) $(CFLAGS) -o Test2 Test2.o mymalloc.o


Test3.o: Test3.c
	$(COMPILER) $(CFLAGS2) -c Test3.c

Test3: mymalloc.o Test3.o
	$(COMPILER) $(CFLAGS) -o Test3 Test3.o mymalloc.o


Test4.o: Test4.c
	$(COMPILER) $(CFLAGS2) -c Test4.c

Test4: mymalloc.o Test4.o
	$(COMPILER) $(CFLAGS) -o Test4 Test4.o mymalloc.o


Test5.o: Test5.c
	$(COMPILER) $(CFLAGS2) -c Test5.c

Test5: mymalloc.o Test5.o
	$(COMPILER) $(CFLAGS) -o Test5 Test5.o mymalloc.o


Test6.o: Test6.c
	$(COMPILER) $(CFLAGS2) -c Test6.c

Test6: mymalloc.o Test6.o
	$(COMPILER) $(CFLAGS) -o Test6 Test6.o mymalloc.o


Test7.o: Test7.c
	$(COMPILER) $(CFLAGS2) -c Test7.c

Test7: mymalloc.o Test7.o
	$(COMPILER) $(CFLAGS) -o Test7 Test7.o mymalloc.o


Test8.o: Test8.c
	$(COMPILER) $(CFLAGS2) -c Test8.c

Test8: mymalloc.o Test7.o
	$(COMPILER) $(CFLAGS) -o Test8 Test8.o mymalloc.o


clean:
	rm -f *.o mymalloc Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8

CC = gcc
CCFLAGS = -Wall -g

all: runfile

runfile: mymalloc.o memgrind.o
	$(CC) $(CCFLAGS) -o runfile mymalloc.o memgrind.o

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CCFLAGS) -c mymalloc.c

memgrind.o: memgrind.c
	$(CC) $(CCFLAGS) -c memgrind.c

clean:
	rm -f runfile mymalloc.o memgrind.o