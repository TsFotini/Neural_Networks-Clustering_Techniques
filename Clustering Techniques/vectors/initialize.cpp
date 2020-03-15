#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include "initialize.h"
#include "lshFunctions.h"
#include "functions.h"

vector<VectorNode> RandomMeanCentroids_kmeans(VectorNode sampleElement, int K){
	vector<VectorNode> centroids;
	vector<double> pointsOfCentroid;

	int dimension = sampleElement.getDimension();
	for(int i=0; i<K; i++){
			VectorNode sampleVec;
			pointsOfCentroid = normalDistribution(dimension,9,0);
			sampleVec.setPoints(pointsOfCentroid);
			sampleVec.setID(to_string(i));
			sampleVec.setPointsType('c');
			centroids.push_back(sampleVec);
	}
	return centroids;
}

vector<VectorNode> RandomDatasetCentroids_kmedoids(VectorNode * allInputs, int countLines, int &K){
  vector<VectorNode> centroids, keepTrack;
  int rand;
  for(int i=0;  i< countLines; i++){
    keepTrack.push_back(allInputs[i]);
  }
  if(K >= countLines){
    K = countLines;
  }
  if(sizeof(allInputs) > 0){
    for(int i=0; i<K; i++){
      if(keepTrack.size() == 0)
        continue;
      else{
        rand = Fate(keepTrack.size());
   		keepTrack[rand].setPointsType('c');
        centroids.push_back(keepTrack[rand]);
        keepTrack.erase(keepTrack.begin() + rand);
      }
    }
  }
  return centroids;
}

int findPossOfNum(vector<double> sums,double randNum){
	vector<double>::iterator upper1;
	upper1 = std::upper_bound(sums.begin(), sums.end(), randNum );
	return upper1 - sums.begin();
}

vector<VectorNode> InitializationPlus (VectorNode * allInputs,int countlines,int K){
	//Choose random center
	int randIndex = Fate(countlines);
	vector<VectorNode> C;
	allInputs[randIndex].setPointsType('c');
	C.push_back(allInputs[randIndex]);

	//Copy Inputs to a vector
	vector<VectorNode> copyEngine;
	for(int i=0; i<countlines;i++){
		copyEngine.push_back(allInputs[i]);
	}

	//Delete first centroid selected;
	copyEngine.erase(copyEngine.begin() + randIndex);
	vector<double> sums;

	int keepPos;

	for(int i=0; i<copyEngine.size(); i++){
		if(K != C.size()){
			for(int j=0; j<C.size(); j++){
				double minDist = ManhattanDistance(allInputs[i].getPoints(),C[j].getPoints());
				sums.push_back(minDist*minDist);
			}
			double maxElement = *max_element(sums.begin(),sums.end());
			for(int n=0; n<sums.size(); n++){
				sums[i] = sums[i] / maxElement;
			}
			vector<double> randNum = normalDistribution(1,copyEngine.size(),1);
			keepPos = findPossOfNum(sums,randNum[0]);
			VectorNode centroid = copyEngine[findPossOfNum(sums,randNum[0])];
			centroid.setPointsType('c');
			C.push_back(centroid);
		}
		copyEngine.erase(copyEngine.begin() + keepPos);
	}
	return C;
}
