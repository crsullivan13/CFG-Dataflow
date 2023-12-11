CC=g++
FLAGS = -Wall -g

analysis: main.o instruction.o driver.o cfg.o parser.o bbl.o factset.o
	$(CC) $(FLAGS) -o analysis main.o instruction.o driver.o cfg.o parser.o bbl.o factset.o

main.o: main.cpp driver.hpp
	$(CC) $(FLAGS) -c main.cpp

instruction.o: instruction.hpp instruction.cpp
	$(CC) $(FLAGS) -c instruction.cpp

driver.o: cfg.hpp parser.hpp driver.hpp driver.cpp
	$(CC) $(FLAGS) -c driver.cpp

cfg.o: bbl.hpp cfg.hpp cfg.cpp 
	$(CC) $(FLAGS) -c cfg.cpp

parser.o: instruction.hpp parser.hpp parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

bbl.o: factset.hpp bbl.hpp bbl.cpp
	$(CC) $(FLAGS) -c bbl.cpp

factset.o: factset.hpp factset.cpp
	$(CC) $(FLAGS) -c factset.cpp

clean:
	rm *.o analysis