CC = g++
CPPFLAGS = -std=c++11

all: main.o generator.o
	$(CC) $(CPPFLAGS) -o ../Generator main.o generator.o
	
generator.o: generator.cpp generator.h
	$(CC) $(CPPFLAGS) -c generator.cpp

main.o: main.cpp generator.h
	$(CC) $(CPPFLAGS) -c main.cpp
	
clean:
	rm -f *.o ../Generator
