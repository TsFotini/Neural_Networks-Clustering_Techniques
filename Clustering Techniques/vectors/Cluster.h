#ifndef CLUSTER_H
#define CLUSTER_H
#include <vector>
#include "VectorNode.h"
using namespace std;

class Cluster{
  VectorNode centroid;
  vector<VectorNode> inClusterPoints;
public:
  VectorNode getCentroid(){ return centroid;}
  void setCentroid(VectorNode v){ centroid = v;}
  vector<VectorNode> getPoints(){ return inClusterPoints; }
  void setPoints(vector<VectorNode> vec){ inClusterPoints = vec; }
  void pushInCluster(VectorNode element){ inClusterPoints.push_back(element);}
};

class Cost{
  VectorNode centroid;
  double sum;
public:
  VectorNode getCentroid(){ return centroid;}
  void setCentroid(VectorNode v){ centroid = v;}
  double getsum(){ return sum; }
  void setsum(double s) { sum = s; }
};

#endif
