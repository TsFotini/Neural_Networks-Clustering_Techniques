#ifndef VECTORNODE_H
#define VECTORNODE_H
#include <vector>
#include <string>
using namespace std;
class VectorNode{
  string id;
  vector<double> points;
  char pointsType = 'p';
public:
  void setID(string i){ id = i;}
  void setPoints(vector<double> vec) { points = vec;}
  void setPointsType(char type){pointsType = type;}
  char getPointsType(){ return pointsType;}
  string getID() { return id; }
  vector<double> getPoints() { return points; }
  int getDimension(){ return points.size();}
};

class NN{
	VectorNode query;
	VectorNode neighbors;
	double distance;
public:
	void setQuery(VectorNode vec) { query = vec; }
	void setNeighbours(VectorNode vec) { neighbors = vec; }
	void setDistance(double dis) { distance = dis;}
	VectorNode getQuery(){ return query;}
	VectorNode getNeighbors(){ return neighbors;}
	double getDistance(){ return distance;}
};
#endif
