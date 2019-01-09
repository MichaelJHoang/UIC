lab14a: lab14a.o Point2d.o Point3d.o
	g++ -o lab14a lab14a.o Point2d.o Point3d.o

lab14a.o: lab14a.cpp Point2d.h Point3d.h
	g++ -c lab14a.cpp

Point2d.o: Point2d.cpp Point2d.h
	g++ -c Point2d.cpp

Point3d.o: Point3d.cpp Point3d.h
	g++ -c Point3d.cpp

clean:
	rm lab14a.o Point2d.o Point3d lab14a
