#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "Cluster.h"
#include "MapCentroid.h"
using namespace std;

vector<Cluster> LloydsAlgorithm(vector<VectorNode> , VectorNode *, int );
void PrintClusters(vector<Cluster> );
vector<VectorNode> ProcessedInputs(vector<VectorNode>, VectorNode *,int);
vector<Cluster> AssignmentByRange(vector<VectorNode> , VectorNode * ,int ,int , int , int);
void PrintHashTable(vector<vector<VectorNode>> );
VectorNode GetCentroidI(vector<MyMap>,int);
int GetCentroid(vector<MyMap> ,int );
double Find_Distance(vector<VectorNode> , string );
#endif
