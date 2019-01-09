/*movies.hpp*/

//
// Netflix movie review analysis.
//
// << Jon-Michael Hoang >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 02
//

// the file that gets inherited from both reviews and main
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <chrono>
#include <numeric>
#include <functional>
#include <iomanip>

using namespace std;

class Movie
{
  private:
  
  	// variables independent of REVIEWS
    int movieID, pubYear;
    string movieName;
    
    // variables dependent on REVIEWS
    int reviewCount = 0;
    vector <int> starVector {0, 0, 0, 0, 0}; // {1*, 2*, 3*, 4*, 5*}
      
  public:
  	// constructor
  	Movie (int ID, string NAME, int YEAR) :
    movieID (ID), movieName (NAME), pubYear (YEAR)
    { }
    
    // getter
    string getName () const
    {
    	return movieName;
    }
    
    // getter
    int getMovieID () const
    {
    	return movieID;
    }
    
    // getter
    int getReviewCount () const
    {
    	return reviewCount;
    }
    
    // read carefully on how this works:
    // sets the rating by adding to the sum
    // to its respective index
    void setRating (int x)
    {
    	starVector.at(x-1) += x;
    	reviewCount++;
    }
    
    // returns the average rating by accumulating all the values and dividing by the
    // total reviewCount
    double getAvg () const
    {
    	if (reviewCount == 0)
    		return 0;
    	return accumulate(starVector.begin(), starVector.end(), 0.0) / reviewCount;
    }
    
    
    // prints movie info
    void printInfo () const
    {
    	cout << "Movie:       " << "'" << movieName << "'"<< endl;
    	cout << "Year:        " << pubYear << endl;
    	cout << "Avg rating:  " << getAvg() << endl;
    	cout << "Num reviews: " << reviewCount << endl;
    	cout << " 1 star:     " << starVector.at(0) << endl;
    	cout << " 2 stars:    " << starVector.at(1)/2 << endl;
    	cout << " 3 stars:    " << starVector.at(2)/3 << endl;
    	cout << " 4 stars:    " << starVector.at(3)/4 << endl;
    	cout << " 5 stars:    " << starVector.at(4)/5 << endl;
    	cout << endl;
    }
};


// take in a filename and parse and stringstream text into
// their respective varirable names
// and then return the multimap representation of it
multimap<int, Movie> streamMovie (const string& filename)
{
	// using multimap for that sexy O(1) runtime
	// because the movies have unique IDs ==> guarenteed I
	// can have insertions perform @ O(1) time
  multimap <int, Movie> movieMap;
  
  // counts the number of movies in the file
  int count = 0;
  
  // ss line
  string line;
  
  // strings streamed into
  string movieID, movieName, pubYear;
  
  ifstream file (filename);
  
  // ignore the first line of input in the .csv files
  getline (file, line);
  
  // start the timer
  auto start = chrono::system_clock::now();
  
  // dont need to close file because RAII handles it &
	// parses the .csv files into appropriate variables and
	// keeps track of movie things specifically
  if (file.is_open())
  {
    while (getline(file, line))
    {
      stringstream ss(line);
      
      // stream .csv text into these strings here
      getline (ss, movieID, ',');
      getline (ss, movieName, ',');
      getline (ss, pubYear, ',');
      
      // emplace into the movieMap Movies
      movieMap.emplace (stoi(movieID), Movie (stoi(movieID), movieName, stoi(pubYear)));
      
      count++;
    }
  }
  
  // end the timer and take the difference between start and end
  auto end = chrono::system_clock::now(); chrono::duration<double> runtime = end - start;

  // returns the number of movies read from the file and the time it took to parse it
  cout << ">> Reading movies... " << count << " [ time: " << chrono::duration<double, milli> (runtime).count() << " ms ] " << endl;
  
  // close the file just in case RAII doesn't work out
  file.close();
  
  // returns the multimap representation of movies.csv
  return movieMap;
}
// end streamMovie()


// take in a movieMap and returns a Movie vector that is
// ordered based on average ratings
vector <Movie> MVP (const multimap <int, Movie>& movieMap)
{
	vector <Movie> mvp;
	
	// iterate through the movieMap and push
	// the value of the map into the mvp
	// vector
	for (auto& iter : movieMap)
		mvp.push_back (iter.second);
	
	// lambda to sort the mvp vector based on
	// highest average rating
	auto lambda = [] (Movie& m1, Movie& m2)
	{
		return m1.getAvg() > m2.getAvg();
	};
	
	// use std::sort to sort mvp
	sort (mvp.begin(), mvp.end(), lambda);
	
	// return the sorted mvp vector
	return mvp;
}
// end MVP()


// take the mvp vector and prints out the top 10
// in the thing
void printMVP (const vector <Movie>& mvp)
{
	cout << "Rank    ID      Reviews Avg     Name" << endl;
	cout << "1.      " << mvp.at(0).getMovieID() << "      " << mvp.at(0).getReviewCount()
			 << "    " << mvp.at(0).getAvg() << " '" << mvp.at(0).getName() << "'" << endl;
	cout << "2.      " << mvp.at(1).getMovieID() << "      " << mvp.at(1).getReviewCount()
			 << "    " << mvp.at(1).getAvg() << " '" << mvp.at(1).getName() << "'" << endl;
	cout << "3.      " << mvp.at(2).getMovieID() << "      " << mvp.at(2).getReviewCount()
			 << "    " << mvp.at(2).getAvg() << " '" << mvp.at(2).getName() << "'" << endl;
	cout << "4.      " << mvp.at(3).getMovieID() << "      " << mvp.at(3).getReviewCount()
			 << "    " << mvp.at(3).getAvg() << " '" << mvp.at(3).getName() << "'" << endl;
	cout << "5.      " << mvp.at(4).getMovieID() << "      " << mvp.at(4).getReviewCount()
			 << "    " << mvp.at(4).getAvg() << " '" << mvp.at(4).getName() << "'" << endl;
	cout << "6.      " << mvp.at(5).getMovieID() << "      " << mvp.at(5).getReviewCount()
			 << "    " << mvp.at(5).getAvg() << " '" << mvp.at(5).getName() << "'" << endl;
	cout << "7.      " << mvp.at(6).getMovieID() << "      " << mvp.at(6).getReviewCount()
			 << "    " << mvp.at(6).getAvg() << " '" << mvp.at(6).getName() << "'" << endl;
	cout << "8.      " << mvp.at(7).getMovieID() << "      " << mvp.at(7).getReviewCount()
			 << "    " << mvp.at(7).getAvg() << " '" << mvp.at(7).getName() << "'" << endl;
	cout << "9.      " << mvp.at(8).getMovieID() << "      " << mvp.at(8).getReviewCount()
			 << "    " << mvp.at(8).getAvg() << " '" << mvp.at(8).getName() << "'" << endl;
	cout << "10.     " << mvp.at(9).getMovieID() << "      " << mvp.at(9).getReviewCount()
			 << "    " << mvp.at(9).getAvg() << " '" << mvp.at(9).getName() << "'" << endl << endl;
}
// end printMVP()
