// Winter'22
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>
#include "movies.h"
using namespace std;

struct movieData{
  double movieRating;
  string movieName;
  string movieLine;
  bool operator<(const movieData& rhs){
    if(movieRating == rhs.movieRating){
      return movieName < rhs.movieName;
    }
    else{
      return movieRating > rhs.movieRating;
    }
  }
};

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
  if(argc < 2){
    cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
    cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
    exit(1);
  }


  ifstream movieFile (argv[1]);
 

  if (movieFile.fail()){
    cerr << "Could not open file " << argv[1];
    exit(1);
  }
  
//Create an object of a STL data-structure to store all the movies

string line, movieName;
double movieRating;
vector<string> vAlphabet;
vector<movieData> vRating;
// Read each file and store the name and rating
while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
  // Use std::string movieName and double movieRating
  // to construct your Movie objects
  // cout << movieName << " has rating " << movieRating << endl;
  // insert elements into your data structure
  string newLineName = line;
  string newMovieName = movieName;
  double newMovieRating = movieRating;
  string newMovieRatingString = line.substr(line.length() - 3, line.length() - 1);
  
  if(newMovieRatingString.at(1) == ','){
    newLineName = newLineName + ".0";
    newMovieRating = stod(newLineName.substr(movieName.length() + 3, line.length()));
  }

  if(line[0] == '"'){
    newMovieName = movieName.substr(0, movieName.length() + 1);
    newMovieRating = stod(line.substr(movieName.length() + 3, line.length()));
    newLineName = newMovieName + "," + to_string(newMovieRating);
    newLineName = newLineName.substr(0, newLineName.length() - 5);
  }

  if(argc == 2){
    vAlphabet.push_back(newLineName);
  }
  
  else{
    struct movieData md = {newMovieRating, newMovieName, newLineName};
    vRating.push_back(md);
  }
}

movieFile.close();

if(argc == 2){
  //print all the movies in ascending alphabetical order of movie names
  sort(vAlphabet.begin(), vAlphabet.end());
  for(int i = 0; i < vAlphabet.size(); i++){
    cout<<vAlphabet[i].substr(0, vAlphabet[i].length() - 4)<<", "<<vAlphabet[i].substr(vAlphabet[i].length() - 3, vAlphabet[i].length())<<endl;
  }
  return 0;
}

if(argc > 2){
  sort(vRating.begin(), vRating.end());
  vector<movieData> bestMovie;
  int numOfPrefix = argc - 2;
  int pre = 2;
  while(numOfPrefix != 0){
    vector<movieData> vMatching;
    for(int i = 0; i < vRating.size(); i++){
      if(argv[pre] == vRating[i].movieName.substr(0, strlen(argv[pre]))){
        vMatching.push_back(vRating[i]);
      }
    }
    
    if(vMatching.size() == 0){
      struct movieData nomd = {-1.0, "None"};
      bestMovie.push_back(nomd);
      cout<<"No movies found with prefix "<<argv[pre]<<endl;
    }
    else{
      struct movieData matchingmd = {vMatching[0].movieRating, vMatching[0].movieName, vMatching[0].movieLine};
      bestMovie.push_back(matchingmd);
      for(int i = 0; i < vMatching.size(); i++){
        cout<<vMatching[i].movieName<<", "<<vMatching[i].movieLine.substr(vMatching[i].movieLine.length() - 3, vMatching[i].movieLine.length())<<endl;
      }
    }
    cout<<endl;
    pre++;
    numOfPrefix--;
  }
  numOfPrefix = argc - 2;
  pre = 2;
  for(int i = 0; i < numOfPrefix; i++){
    if((bestMovie[i].movieName != "None") && (bestMovie[i].movieRating != -1.0)){
      cout<<"Best movie with prefix "<<argv[pre]<<" is: "<<bestMovie[i].movieName<<" with rating "<<std::fixed<<std::setprecision(1)<<bestMovie[i].movieRating<<endl;
    }
    pre++;
  }
}


return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/



bool parseLine(string &line, string &movieName, double &movieRating) {
  if(line.length() <= 0) return false;
  string tempRating = "";

  bool flag = false;
  movieName = tempRating = "", movieRating = 0.0, flag = false;

  for (int i = 0; i < line.length(); i++){
    if(flag) tempRating += line[i];
    else if(line[i]==','&& line[0]!='"') flag = true;
    else {
		  if(i==0 && line[0]=='"') continue;
		  if(line[i]=='"'){ i++; flag=true; continue;}
		  movieName += line[i];
	  }
  }
  
  movieRating = stod(tempRating);
  return true;
}