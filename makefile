# Extremely simple make file

CC=gcc

cypress: test.h 
	$(CC) mem_move.c -o mem_move

clean:
	rm -f mem_move.o mem_move

