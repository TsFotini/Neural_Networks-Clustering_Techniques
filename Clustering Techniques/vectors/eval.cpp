#include <iostream>
#include "eval.h"
#include "lshFunctions.h"
using namespace std;

int FindClosest(vector<Cluster> clusters,Cluster c){
	double bigVal = 999999999;
	int position ;
	for(int i=0;i<clusters.size();i++){
		if(c.getCentroid().getID() != clusters[i].getCentroid().getID()){
			double dis = ManhattanDistance(c.getCentroid().getPoints(),clusters[i].getCentroid().getPoints());
			if(dis < bigVal){
				bigVal = dis;
				position  = i;
			}
		}
	}
	return position;
}

vector<double> evalSilhouette(vector<Cluster> clusters){
  vector<double> insideSilhouette;

	for(int i=0;i<clusters.size();i++){
		double s_i = 0;
		vector<VectorNode> points = clusters[i].getPoints();
		for(int j=0;j<points.size();j++){
			VectorNode current = points[j];
			double sum = 0,a_i,b_i;
			for(int n=0; n<points.size();n++){
				if(current.getID() != points[n].getID()){
					double dis = ManhattanDistance(current.getPoints(),points[n].getPoints());
					sum = sum + dis;
				}
			}
			a_i = sum/points.size();
			int pos = FindClosest(clusters,clusters[i]);
			vector<VectorNode> next = clusters[pos].getPoints();
			double summ = 0;
			for(int n=0; n<next.size();n++){
				if(current.getID() != next[n].getID()){
					double dis = ManhattanDistance(current.getPoints(),next[n].getPoints());
					summ = summ + dis;
				}
			}
			b_i = summ/next.size();
			if(a_i < b_i){
				s_i = (b_i - a_i)/b_i + s_i;
			}
			else{
				s_i = (b_i - a_i)/a_i + s_i;
			}
		}

		insideSilhouette.push_back(s_i/points.size());
		cout<<insideSilhouette[i]<<endl;
	}
	return insideSilhouette;
}

double AverageSilhouette(vector<double> sil){
	double sum = 0;
	for(int i=0;i<sil.size();i++){
		sum = sum + sil[i];
	}
	sum = sum/sil.size();
	return sum;
}
