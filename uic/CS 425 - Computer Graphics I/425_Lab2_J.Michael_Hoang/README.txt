/*
 * File: README.cpp
 * Author: Jon-Michael Hoang
 *
 * Date: November 2nd, 2018
 *
 * OS: Windows 10 64-bit
 * Compiler: Visual Studio 2017
 *
 * README file to help the reader understand the code
 */

 How much of the project did I finish?

	I managed to only have the matrix and point classes done along with
	identifying some items necessary for both the view volume and the scene.
	Other than that, I was not able to do much as it was confusing on where
	and how to go about from there - even with the resources available to me.

How did you create your classes and their functions?

	I created a class called [ Point ] which allowed me to have a well defined
	point that can be convert from cartesian to homogenous, vice versa.
	
	I also had a [ Matrix ] class that had a vector of [ Point ]s and that
	data members could be easily accessed via setters and getters and
	operator overload functions.

	I also created functions to convert the matrix into things such as
	rotation, scale, translate, (and perspective in the main.cpp file) to allow
	easy conversions and overloading the operator* to allow much easier matrix
	multiplications.

	I also tried to create some objects and tried to "3D"-ify them with the help
	of CS 425/488 course notes and the textbook but that still did not get me 
	to complete the project...