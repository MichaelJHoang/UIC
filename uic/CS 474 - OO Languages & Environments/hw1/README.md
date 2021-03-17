IMPORTANT NOTE TO THE INSTRUCTORS:

Hey there guys,

	If you're running this program, please contact me if there are any problems.
	I can guarentee that this works.
	The reason being so is that there's an API rate limit, which limits the amount
	of requests I can make to a server in a given time frame. Therefore, the code would not work
	if the rate limit is punishing me.
	
	This is problematic for me because I have stress tests that stress my implementation's
	ability to receive numerous responses, but the API rate limit prevents me from making
	more stress tests.


-------------------------------------------------------------
How to install this program:

Simply install it, unzipping if necessary.

-------------------------------------------------------------

How to run this program:

If the project is opened in something like IntelliJ, simply run it.

As for gradle, if you're using some kind of terminal or command line,
just run [gradle run].

When the program is running, you are initially prompted with 3 choices:

1. pull my information
2. pull information of another user's repository given user input
0. quit

after making either choices 1 or 2, choice

3. Show all previous queries

would appear, which lists the the name and id of the repositories accessed.
In addition to that, choice 

4. Save previous input

which simply saves the user's previous input. Through which choice

5. Run from saved inputs

would be available, which allows the user to re run previous inputs,
provided that they are saved.

NOTE: When the user enters [ 2 ] after the choice list appears,
MAKE SURE TO INPUT A [ USERNAME/LOGIN ] AND THEN THEIR [ REPO NAME ]
AFTERWARDS.

Reason being so is that running with gradle may or may not print
out the user input prompts accurately.
The problem doesn't exist if you run it on command line with [Gradle run], though

ANOTHER NOTE: MAY CRASH WHEN USING SPECIAL CHARACTERS
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
	- it's so simple that you can only do a couple queries - not a whole lot is available.
	- it's a console application, so the interface is non-existant and staring at the
	  terminal will be super boring.
	- it's so simple that it is not able to process special character.
	
Design Patterns
---------------
The design patterns used within this implementation are:

	Memento - to save user user input to prevent excessive and redundant user typing
			  by allowing them to save previous inputs to later re-run them again if
			  needed.
			  
				Pros:
				- produces "snapshots" of the user's input
				- allows the user to revert to previous actions
				
				Cons:
				- can be a memory hog if the user makes too many mementos
				- obselete mementos can't be destroyed easily
	
	Singleton - I used the singleton design pattern on the Scanner to make sure there aren't
				many instances of scanners floating about.
				
				Pros:
				- Ensures that there is only a limited amount of instances
				- Initialized only when necessary
				
				Cons:
				- Can be problematic when implementing multi-threading
				- limited instances means less freedom of inputs

-------------------------------------------------------------

Results of the run:

user requests produces a repository's name, id, owner, total number of commits, and its collaborators

saving allows the user to run previous inputs if needed. Successful saves will be indicated
by the console output.

-------------------------------------------------------------

Memory:

The program initially consumes little amounts of memory. However,
the more queries the user makes and the more saves they make as well,
the more storage is going to be taken because the program
stores the query objects and mementos within an array - which can't be
wiped until the end of the program.

-------------------------------------------------------------
