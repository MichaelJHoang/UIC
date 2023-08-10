/*
 * File: README.cpp
 * Author: Jon-Michael Hoang
 *
 * Date: September 26th, 2018
 *
 * OS: Windows 10 64-bit
 * Compiler: Visual Studio 2017
 *
 * README file to help the reader understand the code
 */

How much of the project did I finish?

	I managed to draw my name in page 1, draw the unfilled image in page 2, 
	and partially filled it in in page 3.

Why are you referring to them as "pages"?

	When the user cycles through the pages with the [a] and [w] keys,
	there is a global variable called [page] which increments and
	decrements based on the user's input be it [a] to decrement or
	[w] to increment. If the page is == to what's supposed to be
	drawn, e.g. drawPicture (which is == 1), it will draw it and not
	the other pictures. There is also if statements to make sure the user
	does not go out of bounds on the pages.

How did you draw the objects for the assignment?

	Using the functions described below and hard coding them in.

How did you write your name?

	Using the drawLine() function described below and
	using graph geometry to draw (hard-code) my name.

How did you implement the drawLine() function?

	Take in 4 float values representing the x and y of the
	first vertex and of the second such that there are 4 parameters.
	Create temp variables, variables to contain the delta x and y,
	and the decision variable.
	Invert delta if needed so that it can be drawn omni-directionally.
	Draw the first point and render the line towards the end point
	utilizing Bresenham's algorithm (based on the algorithm provided
	in the textbook).

How did you implement the drawCircle() function?

	By reading and following the algorithm given in the textbook:

	[Computer Graphics: Principles and Practice SECOND EDITION IN C] by Foley et. al.
	Pages 82-85.

	I was able to partition the circle into eight pieces and then draw only
	an eight of the circle and follow suit on the rest via symmetry. I then
	have a flag parameter and if it is "true" (or "1"), fill in the circle 
	by scanning and coloring it from the center of the circle towards the edge
	of it.

	I also used Bresenham's midpoint circle algorithm to make the circle look
	clean.

How did you implement the drawRectangle() function?

	By receiving the top left and bottom right vertices via the parameter,
	utilize the drawLine function to draw the rectangle via geometry
	and using the right-hand rule to keep consistency with how it is drawn:

		drawLine(x1, y0, x0, y0);	// top-right to top-left
		drawLine(x0, y0, x0, y1);	// top-left to bottom-left
		drawLine(x0, y1, x1, y1);	// bottom-left to bottom-right
		drawLine(x1, y1, x1, y0);	// bottom-right to top-right

How did you implement the drawTriangle() function?

	By receiving the x and y values of the 3 vertices of a triagle,
	use the drawLine() function to "connect the dots" via symmetry:

		drawLine(x0, y0, x1, y1); // top tip to bottom left tip
		drawLine(x1, y1, x2, y2); // bottom left to bottom right
		drawLine(x2, y2, x0, y0); // bottom right to top tip

	I also have another variation of the function where it draw the same triangle
	but also attempts to fill it in by scanlining from the top to the base and filling it
	...more of it though...

How did you implement the drawEllipse() function?

	Using a variation of Bresenham's midpoint algorithm to render a circle,
	I used it to render an ellipse by drawing it using the given arm lengths and
	center x and y.

	Pretty much partition it and draw the rest with symmetry - except in fourths.

What of the detectEdge() and scanFill() functions?

	They are attempts at scanning the buffer to find edges.
	Starting at (x0, y0), increase x by the slope mx and
	round it to the nearest point inside the object
	at that scanline, insert the value of x into either
	the leftEdge or the rightEdge based on what's needed
	keep it inside the polygon.

	**See if scanline is inside the polygon by referring leftEdge and rightEdge
	if so, draw in the point**
