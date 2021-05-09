#Makefile for the checkers game

#run "make checkers" to get the executable

$(CC) = gcc

checkers: Checkers.o Print_Board.o main.o
	$(CC) Checkers.o Print_Board.o main.o -o checkers
Checkers.o: Checkers.c 
	$(CC) -c Checkers.c
Print_Board.o: Print_Board.c
	$(CC) -c Print_Board.c
main.o: main.c
	$(CC) -c main.c
clean:
	rm *.o checkers