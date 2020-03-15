#ifndef MAPCENTROID_H
#define MAPCENTROID_H
#include "VectorNode.h"
#include <vector>
#include <string>
using namespace std;

class MyMap{
	VectorNode centroid;
	int bucket;
public : 
	VectorNode getCentroid(){ return centroid;}
	int getBucket(){ return bucket;}
	void setBucket(int buck){ bucket = buck;}
	void setCentroid(VectorNode v) { centroid = v;}
};

#endif