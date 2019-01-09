proj5: jhoang6Proj5.o proj5Tokens.o proj5Stack.o
	g++ -o proj5 jhoang6Proj5.o proj5Tokens.o proj5Stack.o

jhoang6Proj5.o: jhoang6Proj5.cpp proj5Tokens.h
	g++ -c jhoang6Proj5.cpp

proj5Tokens.o: proj5Tokens.cpp proj5Tokens.h
	g++ -c proj5Tokens.cpp
	
proj5Stack.o: proj5Stack.cpp proj5Tokens.h
	g++ -c proj5Stack.cpp

clean:
	rm proj5 jhoang6Proj5.o proj5Tokens.o proj5Stack.o
