CC=g++
FLAGS = -Wall -g

analysis: main.o instruction.o driver.o
	$(CC) $(FLAGS) -o analysis main.o instruction.o driver.o

main.o: main.cpp driver.hpp
	$(CC) $(FLAGS) -c main.cpp

instruction.o: instruction.hpp instruction.cpp
	$(CC) $(FLAGS) -c instruction.cpp

driver.o: cfg.hpp driver.hpp driver.cpp
	$(CC) $(FLAGS) -c driver.cpp

cfg.o: bbl.hpp cfg.hpp cfg.cpp 
	$(CC) $(FLAGS) -c cfg.cpp

bbl.o: bbl.hpp bbl.cpp
	$(CC) $(FLAGS) -c bbl.hpp

clean:
	rm *.o analysis