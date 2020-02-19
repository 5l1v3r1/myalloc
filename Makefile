CC = gcc
CFLAGS = -W -Wall
SRC_DIR = ./src/
TEST_DIR = ./test/
all : test_prog

test_prog: main.o myalloc.o
	$(CC) $(CFLAGS) -o test_prog main.o myalloc.o

main.o:
	$(CC) $(CFLAGS) -c $(TEST_DIR)main.c -I$(SRC_DIR)

myalloc.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)myalloc.c

clean:
	rm *.o test_prog