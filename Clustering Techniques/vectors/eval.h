#ifndef EVAL_H
#define EVAL_H
#include <vector>
#include "Cluster.h"
using namespace std;

int FindClosest(vector<Cluster> ,Cluster );
vector<double> evalSilhouette(vector<Cluster> );
double AverageSilhouette(vector<double> );

#endif
