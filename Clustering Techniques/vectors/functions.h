#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <vector>
#include "VectorNode.h"
#include "Results.h"
using namespace std;
void PrintDocument(vector<vector<string>>);
void PrintVectorPoints(vector<double>);
void print(string);
bool fexists(string);
int countlines(string);
vector<string> tokenizeLine(string);
vector<vector<string>> Documents(string);
int Parameter(string , vector<vector<string>> );
VectorNode CreateVectorPoint(string );
VectorNode * CreateSearchEngine(string);
string fileType(string);
vector<string> tokenizeDoc(string);
void ShowMenu();
Results BestAlgorithm(vector<Results> );
Results Algorithms(VectorNode *,int ,int ,int ,int,string , string , string );
void ChooseMenu(const char* ,Results ,string);

#endif
