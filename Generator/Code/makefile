CC = g++
CPPFLAGS = -std=c++11

all:
	$(CC) $(CPPFLAGS) -o ../Generator main.o generator.o
	
generator.o: generator.cpp generator.h
	$(CC) $(CPPFLAGS) -o generator.o generator.cpp

main.o: main.cpp generator.h
	$(CC) $(CPPFLAGS) -o main.o main.cpp
	
clean:
	rm -f *.o ../Generator