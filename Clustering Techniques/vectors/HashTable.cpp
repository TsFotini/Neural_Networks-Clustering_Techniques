#include "HashTable.h"
#include "MapCentroid.h"
#include <iostream>
#include <algorithm>

HashTable::HashTable(){
	g = 0;
	tableSize = -1;
}

void HashTable::HashTableInitialize(int size,unsigned long gfunc)
{
	tableSize = size;
	g = gfunc;
	VectorNode buckets;
	buckets.setID(" ");
	vector <VectorNode> tableOfHash;
	for(int i=0; i<size; i++){
		tableOfHash.push_back(buckets);
		listofPoints.push_back(tableOfHash);
		tableOfHash.clear();
	}

}

HashTable::~HashTable()
{

}

int HashTable::Insert(VectorNode vec, int M){
	int rnd = (rand()%(tableSize-1));
	int bucket = g % M + rnd;
	if(g % M > 0){
		bucket = g % M;
	}
	listofPoints[bucket].push_back(vec);
	return bucket;
}

int HashTable::InsertCentroids(VectorNode vec, int M,int numCentroids, vector<MyMap> &mapCentroids,vector<int> &keepTrack){
	int bucket = g % M ;
	int m = 0;
	cout<<" Here "<<endl;
	if(mapCentroids.size() == 0){
		bucket = g % M;
		listofPoints[bucket].push_back(vec);
		MyMap m;
		m.setCentroid(vec);
		m.setBucket(bucket);
		mapCentroids.push_back(m);
		vector<int>::iterator it = std::find(keepTrack.begin(), keepTrack.end(), bucket);
		int index = std::distance(keepTrack.begin(), it);
		keepTrack.erase(keepTrack.begin() + index);
	}
	else{
		//If you find the bucket in map
		for(int i=0; i<mapCentroids.size(); i++){
			if(mapCentroids[i].getBucket() == bucket ){
				if(keepTrack.size() != 0){
					bucket = keepTrack[0];
					listofPoints[bucket].push_back(vec);
					MyMap m;
					m.setCentroid(vec);
					m.setBucket(bucket);
					mapCentroids.push_back(m);
					keepTrack.erase(keepTrack.begin());
				}
			}
			else{
				if(keepTrack.size() != 0){
					bucket = g % M;
					listofPoints[bucket].push_back(vec);
					MyMap m;
					m.setCentroid(vec);
					m.setBucket(bucket);
					mapCentroids.push_back(m);
					vector<int>::iterator it = std::find(keepTrack.begin(), keepTrack.end(), bucket);
					int index = std::distance(keepTrack.begin(), it);
					keepTrack.erase(keepTrack.begin() + index);
				}
			}
			break;
		}
	}

	return bucket;
}

int HashTable::CentroidsFound(int bucket){
	int c=0;
	for(int i=0; i< listofPoints[bucket].size();i++){
		if(listofPoints[bucket][i].getPointsType() == 'c'){
			c++;
		}
	}
	return c;
}

int HashTable :: BucketFound(VectorNode vec){
	int bucket;

	for(int i=0; i<listofPoints.size(); i++){
		for(int j=0; j<listofPoints[i].size(); j++){
			if(listofPoints[i][j].getID() == vec.getID()){
				bucket = i;
			}
		}
	}

	return bucket;
}
