CC = g++
CPPFLAGS = -std=c++11

all: main.o algorithms.o files.o 
	$(CC) $(CPPFLAGS) -o ../MastsWG main.o algorithms.o files.o

main.o: main.cpp files.h algorithms.h
	$(CC) $(CPPFLAGS) -c main.cpp 
	
algorithms.o: algorithms.cpp algorithms.h vertex.h
	$(CC) $(CPPFLAGS) -c algorithms.cpp

files.o: files.cpp files.h vertex.h
	$(CC) $(CPPFLAGS) -c files.cpp
	
clean:
	rm -f *.o ../MastsWG
