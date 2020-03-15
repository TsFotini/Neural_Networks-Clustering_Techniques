#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include "vectors/functions.h"
using namespace std;


int main(int argc, char const *argv[]){
    while(1){

      print("Welcome!");

      //Declarations
      string usersAnswer;
      string datasetPath;
      string confPath;
      string outputPath;
      string complete;
	    int K, k, grids, L;
      //No arguments given case
      if(argc == 1){
        print("Enter the path of the file you want : ");
        cin>>datasetPath;
        if(fexists(datasetPath) == false){
          print("Wrong Path Given! Try again!");
          continue;
        }
        print("Enter the configuration path: ");
        cin>>confPath;
        if(fexists(confPath) == false){
          print("Wrong Path Given! Try again!");
          continue;
        }
        print("Enter the path of the output file: ");
        cin>>outputPath;

      }
      else{
        if(argc == 8){
          print("Not enough arguments given!");
          break;
        }
        else{
          datasetPath = argv[2];
          confPath = argv[4];
          outputPath = argv[6];
          complete = argv[8];

          if(fexists(datasetPath) == false || fexists(confPath) == false){
            print("Wrong Path Given!");
            break;
          }
        }
      }

	  //For the configuration file
	  vector<vector<string>> configurations = Documents(confPath);
	  PrintDocument(configurations);
      K = Parameter("number_of_clusters:",configurations);
      k = Parameter("number_of_vector_hash_functions:",configurations);
      grids = Parameter("number_of_grids:",configurations);
      if(grids == 1)
        grids = 2;
      L = Parameter("number_of_vector_hash_tables:",configurations);
      if(L == 1 || L==2)
        L = 2;
	  ShowMenu();
      string file_choosed = fileType(datasetPath);
      if(file_choosed.find("vectors\n")){
		  VectorNode *allInputs = CreateSearchEngine(datasetPath);
		  int countLines = countlines(datasetPath);
		  const char *out = outputPath.c_str();
		  vector<Results> res;
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"kmedoids","lloyds","PAM"));
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"kmedoids","lloyds","Mean"));
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"kmedoids","range","Mean"));
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"kmedoids","range","PAM"));
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"++","lloyds","Mean"));
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"++","range","Mean"));
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"++","range","PAM"));
		  res.push_back( Algorithms(allInputs,countLines,K,L,k,"++","lloyds","PAM"));
		  Results temp = BestAlgorithm(res);
		  ChooseMenu(out,temp,complete);
      }
	  //Choose to quit or not
      print("Would you like to continue with a new dataset? Press 'n' in case you want to quit the program!");
      cin>>usersAnswer;
      if(usersAnswer == "n" || usersAnswer == "no" || usersAnswer == "quit")
          break;
      else{
          continue;
      }

    }

}
