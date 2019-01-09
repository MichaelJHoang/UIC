/*reviews.hpp*/

//
// Netflix movie review analysis.
//
// << Jon-Michael Hoang >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 02
//

// reviews is dependent on movies
// a review cannot exist without the movie
// it is reviewing
#include "movies.hpp"

class Review
{
  private:
  	
  	// private variables
    int reviewID, movieID, userID, rating;
    string reviewDate;
      
  public:
  	
  	// constructor
    Review (int RID, int MID, int UID, int RATE, string RDATE) :
    reviewID (RID), movieID (MID), userID (UID), rating (RATE), reviewDate (RDATE)
    { }
    
    // take in a movie map and the user's input for the userID and
    // print out its respective information
  	void printInfo (multimap <int, Movie>& movieMap, int userInput)
  	{
  		// iterate through the movieMap to find the movieID
  		auto movieIter = movieMap.find (movieID);
  		
  		// print the info
  		cout << "Movie: " << movieID << " (" << (&*movieIter) -> second.getName() << ")" << endl; // derefernce the movieIter and get the goodies
  		cout << "Num stars: " << rating << endl;
  		cout << "User id:   " << userID << endl;
  		cout << "Date:      " << reviewDate << endl << endl;
  		
  		return;
  	}
};


// take in both the movieMap and the filename and parse it - inputing information into
// both the reviewMap and the movieMap and returning both the reviewMap and the
// "pass by reference"'d movieMap
multimap <int, Review> streamReview (const string& filename, multimap <int, Movie>& movieMap)
{
  multimap <int, Review> reviewMap;
  
  // counts the number of movies in the file
  int count = 0;
  
  // ss line
  string line;
  
  // strings streamed into
  string reviewID ,movieID ,userID, rating, reviewDate;
  
  ifstream file (filename);
  
  // ignore the first line within the file
  getline (file, line);
  
  // start the timer
  auto start = chrono::system_clock::now();
  
  // ignore the first line of input in the .csv files
  //file.ignore('\n', 'e');
  if (file.is_open())
  {
  	while (getline(file, line))
  	{
  		stringstream ss(line);
  		
  		// stream into these strings here
  		getline (ss, reviewID, ',');
  		getline (ss, movieID, ',');
  		getline (ss, userID, ',');
  		getline (ss, rating, ',');
  		getline (ss, reviewDate, ',');
  		
  		// iterate through the movieMap to find where it is based on the given movieID
  		auto movieIter = movieMap.find(stoi(movieID));
  		
  		// derefernce the iterator and store the rating(s) into the movieMap
  		(&*movieIter) -> second.setRating (stoi(rating));
      
      // emplace into the reviewMap the new review
      reviewMap.emplace (stoi(reviewID), Review (stoi(reviewID), stoi(movieID), stoi(userID), stoi(rating), reviewDate));
  		
  		count++;
  	}
  }
  
  // end the timer and take the difference between start and end
  auto end = chrono::system_clock::now(); chrono::duration<double> runtime = end - start;
  
  // prints out the number of reviews read and the time it took to parse it
  cout << ">> Reading reviews... " << count << " [ time: " << chrono::duration<double, milli> (runtime).count() << " ms ] " << endl;
  
  // close the file just in case RAII does not work
  file.close();
  
  // returns the multimap representation of reviews.csv
  return reviewMap;
}
