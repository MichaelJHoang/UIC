//
//  database.cpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/14/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//

#include "database.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Database::Database() {
	window = { -40, 40, -40, 40 };
	frontPlane = 10;
	backPlane = -150;

	int horizonDistance = -120;
	int runwayLength = 90;

	/*
	   -------------
	 /_|__________/ |
	 | |          | |
	 | +----------|-/
	 |/___________|/
	 */

	terminal = Box(35, 45, 2);
	terminal.transform(Translate4(0, 7.5, -runwayLength - 5));

	/*
		 B____C
		 / / /
		/   /
	   / / /
	  /   /
	A/_/_/D
	 */

	runway = Model({
		Point(-5, 0, 0),    // A - 0
		Point(-5, 0, -runwayLength + 12),  // B - 1
		Point(5, 0, -runwayLength + 12),   // C - 2
		Point(5, 0, 0)      // D - 3
		}, {
			{ 0, 1, 2, 3 }
		});

	// add center line
	for (int i = 1; i < 6; ++i) {
		Model centerline({
			Point(0, 0, -runwayLength / 6 * i),
			Point(0, 0, -runwayLength / 6 * i + 5)
			}, {
				{ 0, 1 }
			});

		runway.addModel(centerline);
	}

	/*
		A_B E_F
		/ / | |
	   / C__D |
	   J____I |
			| |
		   H|_|G
	 */
	number2 = Model({
		//Point(-2, 0, -5),   // A - 0
		//Point(-1, 0, -5),   // B - 1
		//Point(-1, 0, -3), // C - 2
		//Point(1, 0, -3),    // D - 3
		//Point(1, 0, -3),    // E - 4
		//Point(2, 0, -3),    // F - 5
		//Point(2, 0, 0),     // G - 6
		//Point(1, 0, 0),     // H - 7
		//Point(1, 0, -2),    // I - 8
		//Point(-2, 0, -2)  
		Point(0, -5, 0), // J - 9
		Point(-4, -5, 0),    // F - 5
		Point(-4, -2, 0),		
		Point(-1, -2, 0),
		Point(-1, -1, 0),
		Point(-4, -1, 0),
		Point(-4, 0, 0),
		Point(0, 0, 0),
		Point(0, -3, 0),
		Point(-3, -3, 0),
		Point(-3, -4, 0),
		Point(0, -4, 0),

		//Point(6, -5, 0), // J - 9
		//Point(2, -5, 0),    // F - 5
		//Point(2, -2, 0),
		//Point(3, -2, 0),
		//Point(3, -1, 0),
		//Point(2, -1, 0),
		//Point(2, 0, 0),
		//Point(6, 0, 0),
		//Point(6, -3, 0),
		//Point(3, -3, 0),
		//Point(3, -4, 0),
		//Point(6, -4, 0)


		}, {
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
		});

	number2.transform(Translate4(-5, 47, -runwayLength + 10));
	number2.transform(Translate4(5, 25, -runwayLength + 10));
	//runway.addModel(number2);
	//number2.transform(Translate4(0, 15, 0));
	//runway.addModel(number2);
	//number2.transform(Translate4(0, 0, -runwayLength + 10));
	//runway.addModel(number2);

	/*
	 (...hexagonal face)
	 _____
	<_____>
	\\ __//
	 <___>
	 |||||
	 |||||
	 ||_||
	 <|_|>
	 */

	atct = Prism(6, 1, 1, 10);
	Prism atctTop(6, 1, 2, 10);
	atctTop.transform(Translate4(0, 10, 0));
	atct.addModel(atctTop);
	atct.transform(Translate4(-15, 0, -runwayLength / 3));

	atct2 = Prism(6, 1, 1, 10);
	//Prism atctTop(6, 4, 8, 10);
	atctTop.transform(Translate4(0, 0, 0));
	atct2.addModel(atctTop);
	atct2.transform(Translate4(15, 0, -runwayLength / 3));

	/*
		  ___
		/___/|
		| || |
		| || |
		| L|_|
		|/_|/
	 */


	radarTower = Box(20, 20, 20);
	radarTower.transform(Translate4(0, 0, -runwayLength - 10));

	/*
		 ________
		 \_\_\_\_\
		  |_|_|_|_|
		 /_/_/_/_/
	 */
	Model radarSquare({
		Point(-1, -1, 0),
		Point(-1, 1, 0),
		Point(1, 1, 0),
		//Point(1, 0.5, 0),
		Point(1, -1, 0),
		//Point(1, -0.5, 0)
		//Point(-2, -1,0),
		}, {
			{ 0, 1, 2, 3 }
		});

	Matrix4 nextRow = Translate4(-8, -1.7, 0) * Rotate4(M_PI / 6, 'X');
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 4; ++j) {
			radarSquare.transform(Translate4(2, 0, 0));
			radarDish.addModel(radarSquare);
		}
		radarSquare.transform(nextRow);
	}
	radarDish.setOrigin(0, -1, 0);
	radarDish.transform(Translate4(0, 3, -runwayLength - 10));

	background = Model({
		Point(-100, 0, horizonDistance),
		Point(100, 0, horizonDistance),
		Point(-75, 0, horizonDistance),
		Point(-75, 80, horizonDistance),
		Point(75, 80, horizonDistance),
		Point(75, 0, horizonDistance),
		Point(-10, 15, horizonDistance),
		Point(-10, 30, horizonDistance),
		Point(10, 30, horizonDistance),
		Point(10, 15, horizonDistance),
		Point(-10, 15, horizonDistance),
		Point(-7, 25, horizonDistance),
		Point(8, 15, horizonDistance),
		Point(-8, 15, horizonDistance),
		Point(4, 28, horizonDistance),
		Point(10, 15, horizonDistance)


		//Point(20, 40, horizonDistance),
		//Point(85, 0, horizonDistance)
		}, {
			{ 0, 1 },
			{ 2, 3, 4,5 },
			{6,7,8,9},
			{10, 11, 12},
			{13, 14, 15}
			//{ 5, 6, 7 }
		});
}

Model * Database::radarPtr() {
	return &radarDish;
}

vector<Model *> Database::objects() {
	return vector<Model *>({
		&terminal,
		&runway,
		&atct,
		&atct2,
		&radarTower,
		&radarDish,
		&background,
		&number2
		});
}
Point Database::horizonMidpt() {
	return Point(0, 0, -120);
}

Point Database::initialPlanePosition() {
	return Point(0, 10, 40);
}
Point Database::vup() {
	return Point(0, 1, 0);
}

Point Database::prp() {
	return Point(0, 0, 40);
}
int Database::left() {
	return window[0];
}
int Database::right() {
	return window[1];
}
int Database::bottom() {
	return window[2];
}
int Database::top() {
	return window[3];
}
int Database::front() {
	return frontPlane;
}
int Database::back() {
	return backPlane;
}

int Database::screenWidth() {
	return 500;
}
int Database::screenHeight() {
	return 500;
}
