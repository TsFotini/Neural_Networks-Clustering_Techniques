#ifndef INITIALIZE_H
#define INITIALIZE_H
#include <vector>
#include "lshFunctions.h"

vector<VectorNode> RandomMeanCentroids_kmeans(VectorNode , int );
vector<VectorNode> RandomDatasetCentroids_kmedoids(VectorNode * allInputs, int countLines, int &K);
int findPossOfNum(vector<double>,double);
vector<VectorNode> InitializationPlus (VectorNode * ,int ,int );

#endif
