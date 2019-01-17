/*main.cpp*/

//
// Grade Analysis program in modern C++.
//
// << Jon-Michael Hoang >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 01
//

// default libraries set by instructor
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


// class Course to conatin classes and majors/depts
class Course
{
	private:
		string instructor, dept, num, title; // num is the course number, e.g. the 341 in CS 341
		int numStudents = 0, courseCount = 1;
		double A = 0, B = 0, C = 0, D = 0, F = 0, I = 0, NR = 0, S = 0, U = 0, W = 0; // variables to track grades
	
	public:
	
		// constructor to be utilized by the classes in UIC
		Course (string INSTRUCTOR, string DEPT, 
						string NUM, string TITLE,  
						double a, double b, double c, 
						double d, double f, double i, 
						double nr, double s, double u, 
						double w) :
						instructor(INSTRUCTOR), dept(DEPT), 
						num(NUM), title(TITLE), 
						A(a), B(b), C(c), 
						D(d), F(f), I(i), 
						NR(nr), S(s), U(u), 
						W(w)
						{ }
		
		// constructor specified for College of Engineering
		Course (string DEPT, 
						double a, double b, double c, 
						double d, double f) :
						dept(DEPT), 
						A(a), B(b), C(c), 
						D(d), F(f)
						{ I = 0; NR = 0; S = 0; U = 0; W = 0; 
							numStudents = A + B + C + D + F; }
		
		// returns the name of the instructor
		string getInst () const
		{
			return instructor;
		}
		
		
		// returns the department
		string getDept () const
		{
			return dept;
		}
		
		// returns the course number
		string getNum () const
		{
			return num;
		}
		
		// returns the number of students within a class
		int getNumStudents () const
		{
			return A + B + C + D + F + I + NR + S + U + W;
		}
		
		// returns the number of students who got A -> F, specified for listing
		// the majors and the COE
		int getNumStudentsAlt () const
		{
			return A + B + C + D + F;
		}
		
		// prints out the DFW rate of a certain class
		void percentageDFW () const
		{
			cout << "   DFW rate: " << ((D + F + W) / getNumStudents()) * 100 << "%" << endl;
			return;
		}
		
		// whenever the stringstream parses a line of classes, this function also
		// gets called so that it keeps track of the grades in the departments.
		void add (double a, double b, double c,
							double d, double f, double i,
							double nr, double s, double u,
							double w)
		{
			courseCount++;
			A += a; B += b; C += c; D += d; F += f;
			I += i; NR += nr; S += s; U += u; W += w;
		}
		
		// returns the number of courses that exist
		int getCourseCount ()
		{
			return courseCount;
		}
		
		// prints out the grade distribution for A -> Fs
		void getDist () const
		{
			int total = A + B + C + D + F;
			cout << "   Distribution: " << (A/total)*100 << "%, "
																	<< (B/total)*100 << "%, "
																	<< (C/total)*100 << "%, "
																	<< (D/total)*100 << "%, "
																	<< (F/total)*100 << "%" << endl;
			return;
		}
};
// end class Course

int main()
{
  string  filename;

  cin >> filename;
  cout << filename << endl;
  cout << endl;

  cout << std::fixed;
  cout << std::setprecision(2);
  
  ifstream file(filename);
	
	// ss line
	string line;
	
	// strings to stream into
	string dept, num, title, a, b, c, d, f, i, nr, s, u, w, inst;
	
	// variable(s) to keep track of number of courses and grades in the COE
	int COEnumCourse = 0;
	int deptCount = 0;
	double coeA = 0, coeB = 0, coeC = 0, coeD = 0, coeF = 0;
	
	// vector containing specific courses taught at UIC
	vector <Course> courseList;
	// vector containing the different departments/majors under UIC
	vector <Course> majorList;
	
	string userInput;
	
	// ignore the first line of input in the .csv files
	file.ignore('r', '\n');
	
	// dont need to close file because RAII handles it
	// parses the .csv files into appropriate variables and
	// keeps track of COE things specifically
	if (file.is_open())
	{
		while (getline(file, line))
		{
			stringstream ss(line);
			
			getline(ss, dept, ',');
			
			getline(ss, num, ',');
			COEnumCourse++;
				
			getline(ss, title, ','); 
			
			// all the stod() commands here converts the strings to doubles
			getline(ss, a, ',');
				coeA += stod(a);
				
			getline(ss, b, ',');
				coeB += stod(b);
				
			getline(ss, c, ',');
				coeC += stod(c);
				
			getline(ss, d, ',');
				coeD += stod(d);
				
			getline(ss, f, ',');
				coeF += stod(f);
				
			getline(ss, i, ',');
			
			getline(ss, nr, ',');
			
			getline(ss, s, ',');
			
			getline(ss, u, ',');
			
			getline(ss, w, ',');
			
			getline(ss, inst, ',');
			
			// iterates through the list of majors and sees if there are any existing classes for that
			// specific major/dept
			auto iter = find_if(majorList.begin(), majorList.end(),
									[=] (const Course& mL)
									{
										if (mL.getDept() == dept)
											return true;
										else
											return false;
									});
			
			// if none existing, create a new one
			if (iter == majorList.end())
				majorList.push_back(Course (dept, stod(a), stod(b), stod(c), stod(d), stod(f)));
			// if there exists one, take the location of the vector and push data into it via
			// dereferencing.
			// README README README README README README README README README README README README README README README README README README README README README README README README 
			// NOTE: I AM NOT USING POINTERS PER SAY. I AM ONLY DEREFERENCING IT. IF THERE EXISTS
			//       A PROBLEM WITH USING (&*iter), I WOULD LIKE TO ARGUE TO DEFEND MY POSITION.
			// README README README README README README README README README README README README README README README README README README README README README README README README
			else
			{
				(&*iter) -> add(stod(a), stod(b), stod(c), 
												stod(d), stod(f), stod(i), 
												stod(nr), stod(s), stod(u), stod(w));
			}
			
			// create a new course onto the courseList
			courseList.push_back(Course (inst, dept, num, title,  
																	 stod(a), stod(b), stod(c), 
																	 stod(d), stod(f), stod(i), 
																	 stod(nr), stod(s), stod(u), stod(w)));
		}
	}
	
	// printing out basic COE stuff
	Course COE ("College of Engineering", coeA, coeB, coeC, coeD, coeF);
	cout << COE.getDept() << ": " << endl;
	cout << "   Num courses:  " << COEnumCourse << endl;
	cout << "   Num grades:   " << COE.getNumStudents() << endl;
	COE.getDist();
	cout << endl;
	
	// printing out information within the majorList with a foreach loop
	for (auto& x : majorList)
	{
		cout << x.getDept() <<": " << endl;
		cout << "   Num courses:  " << x.getCourseCount() << endl;
		cout << "   Num grades:   " << x.getNumStudentsAlt() << endl;
		x.getDist();
	}
	
	cout << endl;
	
	// ask for userInput to look up specific professors' classes
	while (userInput != "#")
	{
		cout << "Please enter instructor's name (or prefix or #)>";
		cin >> userInput;
		
		// iterates the courseList in search of any professor who matches the userInput's
		// be it a partial or full name
		for (auto& tracker : courseList)
			// if statement that allows the use of partial lookups
			if (tracker.getInst().find(userInput) != string::npos)
			{
				cout << tracker.getDept() << " " << tracker.getNum() 
						 << " (" << tracker.getInst() << "): " << endl 
						 << "   Num students: " << tracker.getNumStudents() << endl;
				tracker.getDist();
				tracker.percentageDFW();
			}
			
		cout << endl;
	}
}
// end main
