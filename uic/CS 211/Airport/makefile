project6: jhoang6proj6.o airportFiles.o
	g++ -o project6 jhoang6proj6.o airportFiles.o

jhoang6proj6.o: jhoang6proj6.cpp airportFiles.h
	g++ -c jhoang6proj6.cpp
	
airportFiles.o: airportFiles.cpp airportFiles.h
	g++ -c airportFiles.cpp

clean:
	rm project6 jhoang6proj6.o airportFiles.o
