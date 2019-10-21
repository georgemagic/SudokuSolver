CFLAGS = -g -O
CC = g++

SudokuSolver: SudokuSolver.o MyClasses.o
	$(CC) $(CFLAGS) -o SudokuSolver MyClasses.o SudokuSolver.o
SudokuSolver.o: SudokuSolver.cpp
	$(CC) $(CFLAGS) -c SudokuSolver.cpp
MyClasses.o: MyClasses.cpp
	$(CC) $(CFLAGS) -c MyClasses.cpp
clean:
	rm -f core *.o
	rm -f SudokuSolver
