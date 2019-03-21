all: client server

client: client.o writingImplementation.o
	g++ client.o writingImplementation.o -o client

server: server.o writingImplementation.o
	g++ server.o writingImplementation.o -o server

client.o: client.cpp
	g++ -c client.cpp

server.o: server.cpp
	g++ -c server.cpp

writingImplementation.o: writingImplementation.cpp writingClass.h
	g++ -c writingImplementation.cpp

clean:
	rm *.o client server
