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

struct movieDataAlphabet{
  string movieName;
  double movieRating;
  bool operator<(const movieDataAlphabet& rhs){
    return movieName < rhs.movieName;
  }
};

struct movieDataRating{
  double movieRating;
  string movieName;
  bool operator<(const movieDataRating& rhs){
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

string line, movieName;
double movieRating;
vector<movieDataAlphabet> vAlphabet;
vector<movieDataRating> vRating;
while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
  if(argc == 2){
    struct movieDataAlphabet mda = {movieName, movieRating};
    vAlphabet.push_back(mda);
  }
  else{
    struct movieDataRating mdr = {movieRating, movieName};
    vRating.push_back(mdr);
  }
}
movieFile.close();

if(argc == 2){
  sort(vAlphabet.begin(), vAlphabet.end());
  for(int i = 0; i < vAlphabet.size(); i++){
    cout<<vAlphabet[i].movieName<<", "<<std::fixed<<std::setprecision(1)<<vAlphabet[i].movieRating<<endl;
  }
  return 0;
}

if(argc > 2){
  sort(vRating.begin(), vRating.end());
  vector<movieDataRating> bestMovie;
  int numOfPrefix = argc - 2;
  int pre = 2;
  while(numOfPrefix != 0){
    vector<movieDataRating> vMatching;
    for(int i = 0; i < vRating.size(); i++){
      if(argv[pre] == vRating[i].movieName.substr(0, strlen(argv[pre]))){
        vMatching.push_back(vRating[i]);
      }
    }
    if(vMatching.size() == 0){
      struct movieDataRating nomd = {-1.0, "None"};
      bestMovie.push_back(nomd);
      cout<<"No movies found with prefix "<<argv[pre]<<endl;
    }
    else{
      struct movieDataRating matchingmd = {vMatching[0].movieRating, vMatching[0].movieName};
      bestMovie.push_back(matchingmd);
      for(int i = 0; i < vMatching.size(); i++){
        cout<<vMatching[i].movieName<<", "<<std::fixed<<std::setprecision(1)<<vMatching[i].movieRating<<endl;
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

/* 
Overall time complexity: O((n) + (nlog^2(n)) + (m * n(nlog^2(n))) + (k * nlog^2(n)) + m)

Big-O time complexity: O(m * n(nlog^2(n)))
*/



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