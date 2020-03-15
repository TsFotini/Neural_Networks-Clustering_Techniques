#include <iostream>
#include "lshFunctions.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <math.h>
#include <time.h>
#include <algorithm>

vector<double> normalDistribution(int dimension,double range, int normal){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  vector<double> s_vector;
  normal_distribution<double> distribution (0.0,range);
  if(normal == 1){
    for (int i=0; i<dimension; i++){
        s_vector.push_back(distribution(generator));
    }
  }
  else{
    for (int i=0; i<dimension; i++){
      double myDis = distribution(generator);
      if(myDis < 0){
        myDis = myDis * (-1) * Fate(3);
      }
      s_vector.push_back(myDis);
    }
  }
  return s_vector;
}

int Fate(int range){
  return rand() % range;
}

double roundLower(double num)
{
  return floor(num - 0.5);
}

double ManhattanDistance (vector<double> x_vector, vector<double> y_vector ){
  double distance = 0;
  double difference = 0;
  int dimension = x_vector.size();
  if(x_vector.size() != y_vector.size()){
    cout<<"Warning!Vectors with different dimension!"<<endl;
  }
  for(int i =0; i < dimension; i++){
	difference = x_vector[i] - y_vector[i];
	if(difference < 0)
		difference = difference * (-1);
		distance = difference + distance;
	}
  return distance;
}

NN BruteForce_NN_InputData(int numOfPoints,vector<VectorNode> allInputs, VectorNode query){
  double currentDistance = 9999999999, nextDistance = 0;
  int copycat_j = 0;
  NN PairNeighbours;
  for(int j=0; j < numOfPoints; j++){
	nextDistance = ManhattanDistance(query.getPoints(),allInputs[j].getPoints());
		if(nextDistance < currentDistance && allInputs[j].getID() != query.getID()){		//So that we do not count the same point as a neighbour
			currentDistance = nextDistance;
			copycat_j = j;
		}

  }
  PairNeighbours.setQuery(query);
  PairNeighbours.setNeighbours(allInputs[copycat_j]);
  PairNeighbours.setDistance(currentDistance);
  return PairNeighbours;
}

vector<NN> CreateListOfPairs(int pointsDataset,vector<VectorNode> allInputs, VectorNode * query){
	vector<NN> BruteForcePairs;
	for(int i=0; i<pointsDataset; i++){
		NN temp = BruteForce_NN_InputData(pointsDataset,allInputs,allInputs[i]);
		BruteForcePairs.push_back(temp);
	}
	return BruteForcePairs;
}

int Compute_r (vector<NN> allPairs){
    double sumOfDistances = 0;
	for(int i=0; i < allPairs.size(); i++){
		sumOfDistances = allPairs[i].getDistance() + sumOfDistances;
	}
	return (int) sumOfDistances/allPairs.size();
}

int Create_hFunction(int r,VectorNode currentPoint, int k){
  //Declarations
  double a_i = 0;
  int h, h_temp;
  double m = pow(2,32) - 5;
  int M = pow(2,32/k);
  int dimension = currentPoint.getPoints().size();
  vector<double> points = currentPoint.getPoints();
  vector<double> s_vector = normalDistribution(dimension,1,1);

  int w = 10 * r;

  for(int i = 0 ; i < dimension; i++){
    a_i = floor((points[i] - s_vector[i])/w);
    if(i == 0){
      h = (int)a_i % M ;
    } else {
      h_temp = (int)(a_i * pow(m,i)) % M;
      h += h_temp; 
    }
  }
  return h;
}

unsigned long g_Function(int r,vector <VectorNode> allInputs,int k,int pointsDataset){
  unsigned long g = 0;
  for(int i=0; i<k; i++){
    int xRan=rand()%pointsDataset;
    int h = Create_hFunction(r,allInputs[xRan],k);
    g = h << (32/k) + g;
  }
  return g;
}
