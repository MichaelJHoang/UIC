jhoang6_proj7:  jhoang6_proj7.cpp GridDisplay.o Creature.o Environment.o Ant.o Doodlebug.o
	g++ -g -o jhoang6_proj7 jhoang6_proj7.cpp GridDisplay.o Creature.o Environment.o Ant.o Doodlebug.o

gddemo: gddemo.cpp GridDisplay.o
	g++ -o gddemo gddemo.cpp GridDisplay.o

GridDisplay.o: GridDisplay.cpp GridDisplay.h
	g++ -c GridDisplay.cpp

Environment.o: Environment.cpp Environment.h Creature.h GridDisplay.h
	g++ -c Environment.cpp 
	
Creature.o: Creature.cpp Creature.h Ant.h Doodlebug.h Environment.h
	g++ -g -c Creature.cpp

Ant.o: Ant.cpp Ant.h Creature.h
	g++ -c Ant.cpp
	
Doodlebug.o: Doodlebug.cpp Doodlebug.h Creature.h
	g++ -c Doodlebug.cpp

clean:
	rm -f *.o GridMain
