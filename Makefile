CC=g++
FLAGS = -Wall -g

analysis: main.o instruction.o driver.o
	$(CC) $(FLAGS) -o analysis main.o instruction.o driver.o

main.o: main.cpp driver.hpp
	$(CC) $(FLAGS) -c main.cpp

instruction.o: instruction.hpp instruction.cpp
	$(CC) $(FLAGS) -c instruction.cpp

driver.o: driver.hpp driver.cpp
	$(CC) $(FLAGS) -c driver.cpp

clean:
	rm *.o analysis