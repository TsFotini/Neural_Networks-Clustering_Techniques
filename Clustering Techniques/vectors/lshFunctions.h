#ifndef LSHFUNCTIONS_H
#define LSHFUNCTIONS_H
#include "VectorNode.h"

using namespace std;

vector<double> normalDistribution(int ,double ,int);
int Fate(int);
double roundLower(double num);
double ManhattanDistance (vector<double>, vector<double>);
int Create_hFunction(int ,VectorNode , int );
unsigned long g_Function(int , vector<VectorNode> ,int ,int );
int Compute_r (vector<NN> );
vector<NN> CreateListOfPairs(int,vector<VectorNode>, VectorNode *);
NN BruteForce_NN_InputData(int ,vector<VectorNode> , VectorNode );

#endif
