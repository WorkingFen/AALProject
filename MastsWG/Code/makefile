CC = g++
CPPFLAGS = -std=c++11

all:
	$(CC) $(CPPFLAGS) -o ../MastsWG main.o algorithms.o files.o
	
algorithms.o: algorithms.cpp algorithms.h vertex.h
	$(CC) $(CPPFLAGS) -o algorithms.o algorithms.cpp

files.o: files.cpp files.h vertex.h
	$(CC) $(CPPFLAGS) -o files.o files.cpp
	
main.o: main.cpp windows.h files.h algorithms.h
	$(CC) $(CPPFLAGS) -o main.o main.cpp
	
clean:
	rm -f *.o ../MastsWG