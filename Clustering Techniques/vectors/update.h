#ifndef UPDATE_H
#define UPDATE_H
#include "Cluster.h"
#include <vector>
using namespace std;

vector<VectorNode> meanVectors(vector<Cluster>, int,int);
vector<double> sumOfVectors(vector<double> , vector<double> );
int CompareCEntroids(vector<VectorNode> , vector<VectorNode> );
vector<Cluster> meanUpdate(vector<VectorNode>,VectorNode *,int ,int,int ,int ,int , int ,string );
vector<Cluster> PAM(vector<Cluster>&);
VectorNode bestCenter(vector<Cost>);

#endif
