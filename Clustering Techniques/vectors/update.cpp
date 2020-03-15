#include "update.h"
#include "lshFunctions.h"
#include "assignment.h"
#include <iostream>
#include <algorithm>
#include <iterator>

vector<double> sumOfVectors(vector<double> Point1, vector<double> Point2){
  vector<double> results;
  if(Point1.size() != Point2.size()){
    cout<<" Different Dimensions! "<<endl;
    exit(-1);
  }
  else{
    for(int i=0; i<Point1.size(); i++){
      double temp = Point1[i] + Point2[i];
      results.push_back(temp);
    }
  }
  return results;
}

vector<VectorNode> meanVectors(vector<Cluster> clusters, int T, int dim){
  double mean;
  vector<VectorNode> newCentroids;

  //Find dimension
  vector<VectorNode> temp= clusters[0].getPoints();
  int dimension = -1;
  if(temp.size() != 0){
    dimension = temp[0].getPoints().size();
  }
  else{
    dimension = dim;
  }
  temp.clear();

  vector<double> meanCalc;

  for(int i=0; i<clusters.size(); i++){
    for(int i=0; i< dimension; i++){
      meanCalc.push_back(0.0);
    }
    temp = clusters[i].getPoints();
    for(int j=0; j<temp.size(); j++){
      vector<double> tempPoints = temp[j].getPoints();
      meanCalc = sumOfVectors(meanCalc, tempPoints);
    }
    for(int p=0; p<meanCalc.size(); p++){
      meanCalc[p] = meanCalc[p]/T;
    }
    VectorNode v;
    v.setID(to_string(i));
    v.setPoints(meanCalc);
    v.setPointsType('c');
    newCentroids.push_back(v);
    meanCalc.clear();
  }

  return newCentroids;
}

int CompareCentroids(vector<VectorNode> curr, vector<VectorNode> prev){
  int count = 0;
  for(int i=0; i<curr.size(); i++){
    if(ManhattanDistance(curr[i].getPoints(),prev[i].getPoints()) <= 10){
      count++;
    }
  }
  return count; // How many centroids do we wish to be the same before stoping
}

vector<Cluster> meanUpdate(vector<VectorNode> initialCentroids,VectorNode * allInputs,int T,int dim,int iterations,int K,int L, int k,string method){
  vector<VectorNode> prev = initialCentroids;
  vector<VectorNode> current;
  for(int i=0; i<prev.size(); i++)
  {
    VectorNode c;
    c.setID(to_string(-1));
    vector<double> points;
    for(int i=0; i< dim; i++){
      points.push_back(0.0);
    }
    c.setPoints(points);
    current.push_back(c);
  }
  vector<Cluster> clusters;
  int similarCentroids = initialCentroids.size();
  int loops = 0;

  while( loops != iterations){
    loops++;
    if(method == "lloyd")
      clusters = LloydsAlgorithm(prev,allInputs,T);
	else{
		clusters = AssignmentByRange(prev, allInputs,T,K,L,k);
	}
    current = meanVectors(clusters,T,dim);
    if(CompareCentroids(prev,current) == similarCentroids)
      break;
  }
  for(int i=0;i<clusters.size();i++){
    if(clusters[i].getPoints().size() == 0){
      clusters[i].pushInCluster(clusters[i].getCentroid());
    }
  }
  return clusters;
}

VectorNode bestCenter(vector<Cost> sums){
  vector<double> calc;
  for(int i=0;i<sums.size();i++){
    calc.push_back(sums[i].getsum());
  }
  vector<double>::iterator result = min_element(calc.begin(), calc.end());
  return sums[distance(calc.begin(), result)].getCentroid();
}

vector<Cluster> PAM(vector<Cluster> &clusters){
  for(int i=0;i<clusters.size();i++){
  	  vector<VectorNode> temp = clusters[i].getPoints();
	  if(temp.size() == 0){
	  	  clusters[i].pushInCluster(clusters[i].getCentroid());
	  }
  }
  for(int c=0;c<clusters.size();c++){
    vector<VectorNode> pointsInside = clusters[c].getPoints();
    vector<Cost> sums;
    for(int i=0;i<pointsInside.size();i++){
      //Swap Procedure
      VectorNode temp;
      temp = clusters[c].getCentroid();
      clusters[c].setCentroid(pointsInside[i]);
      pointsInside[i] = temp;
      double sum = 0;
      for(int t=0;t<pointsInside.size(); t++){
        sum = sum + ManhattanDistance(pointsInside[t].getPoints(),clusters[c].getCentroid().getPoints());
      }
      Cost costCluster;
      costCluster.setCentroid(clusters[c].getCentroid());
      costCluster.setsum(sum);
      sums.push_back(costCluster);
    }
    VectorNode newCenter = bestCenter(sums);
    clusters[c].setCentroid(newCenter);
  }
  return clusters;
}
