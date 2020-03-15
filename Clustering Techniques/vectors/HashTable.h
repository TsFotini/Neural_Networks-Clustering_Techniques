#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "VectorNode.h"
#include "MapCentroid.h"
#include <string>
#include <vector>
using namespace std;
class HashTable{
	unsigned long g;
	int tableSize;
	vector<vector<VectorNode>> listofPoints;
public:
	HashTable();
	void HashTableInitialize(int size,unsigned long gfunc);
	~HashTable();
	int Insert(VectorNode vec, int M);
	unsigned long getGFunction() {return g;}
	vector<vector<VectorNode>> getHashTable (){return listofPoints;}
	vector<VectorNode> getBucketPoints(int mybucket) {return listofPoints[mybucket];}
	int CentroidsFound(int bucket);
	int InsertCentroids(VectorNode vec, int M,int numCentroids, vector<MyMap> &mapCentroids, vector<int> &keepTrack);
	int BucketFound(VectorNode vec);
};

#endif
