-------------------------------------------------------------
How to install this program:

Simply install it, unzipping if necessary.

-------------------------------------------------------------

How to run this program:

If the project is opened in something like IntelliJ, simply run it.

As for gradle, if you're using some kind of terminal or command line,
just run [gradle run].

To run the tests, run with [gradle test]

When the program is running, you are prompt with 4 choices:

1. Coordinate Facade
2. Shape Facade 
3. Media Facade
0. Quit

This is practically the only place where the user is able to input anything
as that is the design of the facade design pattern.

-------------------------------------------------------------

Design and modeling:

General
-------
How I designed this is that I pretty much made a simple console application that modelled 
a simple menu list whose numerical choices are ascending as one goes down the list.

The pros:
	- it serves as a simple interface for the user to interact with.
	- saves previous user inputs to prevent redundant typing.
	- fast, as it does not require intense calculations.

The cons:
	- it's so simple that you can only do several inputs - not a whole lot is available.
	- it's a console application, so the interface is non-existant and staring at the
	  terminal will be super boring.
	- it's so simple.
	
Design Patterns
---------------
The design patterns used within this implementation is:

Facade is a structural design pattern that provides a simplified (but limited) 
interface to a complex system of classes, library or framework.

Pro: Isolation of the code from the complexity of its subsystems

Con: A facade can become a god object coupled to all classes of an app.
A god object is an object that knows too much or does too much - in which
the facade design pattern is very prone to.

In implementing the annotations, I just did a simple check whether or not 
the annotated object is a client or facade and if it's a client, it can only access
the facades and not its subsystems.

-------------------------------------------------------------

Not much - just normal output with respect to the facade the user chose.

-------------------------------------------------------------

Memory:

N/A - since it's not dealing with big data.