/*main.cpp*/

//
// Netflix movie review analysis.
//
// << Jon-Michael Hoang >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 02
//

// main.cpp is dependent on both movies and reviews .cpp
#include "reviews.hpp"

// main driver for the program
int main ()
{
	// userInput variables for respective file inputs
  string movieFileName, reviewFileName;
  // default to -1 just for compatability
  int userInput = -1;
  
  cout << "** Netflix Movie Review Analysis **\n" << endl;
  
  // get the movies file first and then the reviews because reviews is dependent on movies
  cin >> movieFileName;
  cin >> reviewFileName;
  
  cout << endl;
  
  // parse the files and receive the multimap representation of the
  // .csv files
  multimap <int, Movie> movieMap = streamMovie (movieFileName);
  multimap <int, Review> reviewMap = streamReview (reviewFileName, movieMap);	// reviews is dependent on movies,
  																																						// so movieMap has to be passed int												// so that reviews can be pushed
  																																						// into the appropriate movie
  // create a Movie vector and store all the Movies in the movieMap
  // in it and receive the sorted (by average rating) vector
  vector <Movie> mvp = MVP(movieMap);
  
  cout << endl;
  
  cout << ">> Top-10 Movies <<\n" << endl;
  printMVP (mvp); // print the top 10 in mvp
  
  cout << ">> Movie and Review Information <<\n" << endl;
  
  // ask for userInput until they want to quit by pressing zero (0)
  while (userInput != 0)
  {
    cout << "Please enter a movie ID (< 10,000), a review ID (> 99,999), 0 to stop>";
    cin >> userInput;
    cout << endl;
    
    // quit
    if (userInput == 0)
    {
    	cout <<"** DONE! **\n" << endl;
    	return 0; // end
    }
    // user wants to look at reviews
    else if (userInput > 99999)
    {
    	// iterate through the reviewMap to find the userID
	    auto iter = reviewMap.find (userInput);
	    
	    // make sure to account if not found
	    if (iter == reviewMap.end())
    		cout << "review not found...\n" << endl;
	    else
	    {
	    	// found
	    	// dereference the iterator and access the Movie and print out its info
	    	// refer to the README on why I use the &*
	    	(&*iter) -> second.printInfo(movieMap, userInput);
	    }
    }
    else if (userInput < 10000 && userInput > -1)
    {
    	// iterate through the movieMap and find the movieID
    	auto iter = movieMap.find(userInput);
    	
    	// make sure to account if not found
    	if (iter == movieMap.end())
    		cout << "movie not found...\n" << endl;
    	else
    	{
    		// found
    		// dereference the iterator and access the Review and print out its info
	    	// refer to the README on why I use the &*
    		(&*iter) -> second.printInfo();
    	}
    }
  }
}
// end main
