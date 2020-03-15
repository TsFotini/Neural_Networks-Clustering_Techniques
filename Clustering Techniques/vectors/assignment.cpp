#include "assignment.h"
#include "lshFunctions.h"
#include "HashTable.h"
#include "MapCentroid.h"
#include<algorithm>
#include <iterator>
#include <ctime>
#include <iostream>

vector<Cluster> LloydsAlgorithm(vector<VectorNode> centroids, VectorNode *allInputs,int countlines){
  vector<Cluster> clusters;

  for(int i=0; i<centroids.size(); i++){
    Cluster clst;
    clst.setCentroid(centroids[i]);
    clusters.push_back(clst);
  }

  for(int i=0; i<countlines; i++){
    vector<double> dataPoint = allInputs[i].getPoints();
    vector<double> distances;
    for(int c=0; c<centroids.size(); c++){
      vector<double> centroidPoint = centroids[c].getPoints();
      double distance = ManhattanDistance(dataPoint,centroidPoint);
      distances.push_back(distance);
    }
    double dis = *min_element(distances.begin(), distances.end());
    int clusterNum = min_element(distances.begin(),distances.end()) - distances.begin();
    clusters[clusterNum].pushInCluster(allInputs[i]);
  }
  return clusters;
}

void PrintClusters(vector<Cluster> clusters){
  for(int i=0; i<clusters.size(); i++){
    cout<<"Centroid "<<clusters[i].getCentroid().getID()<<endl;
    vector<VectorNode> samples = clusters[i].getPoints();
    for(int j=0; j<samples.size(); j++){
      cout<<" DataPoints "<<samples[j].getID()<< " " ;
    }
    cout<<endl;
  }
}

vector<VectorNode> ProcessedInputs(vector<VectorNode> centroids, VectorNode * allInputs,int countlines){
  vector<VectorNode> allInputsCopy;
  for(int i=0; i< countlines; i++){
  	  allInputsCopy.push_back(allInputs[i]);
  }
  for(int i=0;i<centroids.size();i++){
    for(int j=0; j<allInputsCopy.size(); j++){
      if(centroids[i].getID() == allInputsCopy[j].getID()){
        //Then allInputs[j] is a centoid
        allInputsCopy.erase(allInputsCopy.begin()+j);
      }
    }
  }
  return allInputsCopy;
}

double Find_Distance(vector<VectorNode> centroids, string max_or_min){
  double dis = 0;
  vector<double> distances;
  for(int i=0;i<centroids.size();i++){
    VectorNode keep = centroids[i];
    centroids.erase(centroids.begin() + i);
    for(int j=0; j<centroids.size(); j++){
      double dist = ManhattanDistance(keep.getPoints(),centroids[j].getPoints());
      distances.push_back(dist);
    }
  }
  if(max_or_min == "min"){
     dis = *min_element(distances.begin(),distances.end());
  }
  else{
     dis = *max_element(distances.begin(),distances.end());
  }
  return dis;
}

int GetCentroid(vector<MyMap> mapMyCentroids,int bucket){
	int vec;
	for(int i=0; i<mapMyCentroids.size(); i++){
		if(mapMyCentroids[i].getBucket() == bucket){
			vec = i;
		}
	}
	return vec;
}

VectorNode GetCentroidI(vector<MyMap> mapMyCentroids,int bucket){
	VectorNode vec;
	for(int i=0; i<mapMyCentroids.size(); i++){
		if(mapMyCentroids[i].getBucket() == bucket){
			vec = mapMyCentroids[i].getCentroid();
		}
	}
	return vec;
}

void PrintHashTable(vector<vector<VectorNode>> temp){
	for(int z=0; z< temp.size(); z++){
		temp[z].erase(temp[z].begin());
		cout<<" Bucket is : "<<z<<endl;
		for(int b=0; b<temp[z].size(); b++){
			cout<<temp[z][b].getID()<<endl;
		}
	}
}


vector<Cluster> AssignmentByRange(vector<VectorNode> centroids, VectorNode * allInputs,int countlines,int K, int L, int k){

  vector<VectorNode> searchEngine = ProcessedInputs(centroids,allInputs,countlines);
  vector<NN> pairs = CreateListOfPairs(centroids.size(),centroids,allInputs);
  vector<Cluster> clusters;
  int r = Compute_r(pairs);
  int M = K/8 + 1;
  HashTable  AllHashTables[L];
  vector<MyMap> mapMyCentroids;
  vector<int> keepTrack;

  double minDis = Find_Distance(centroids,"min");
  double maxDis = Find_Distance(centroids,"max");

  //To keep track of buckets of insertion
  for(int i=0; i<K;i++){
  	  keepTrack.push_back(i);
  }

  if(searchEngine.size() == 0){
  	  cout<<" All Points are Centroids "<<endl;
	  exit(-2);
  }

  int count = 0;

  //Inserting all points to hashtables
  for(int i=0; i<L; i++){
    int g = g_Function(r,searchEngine,k,searchEngine.size());
  	AllHashTables[i].HashTableInitialize(K,g);
	//After the insertion to one HashTable is done
    for(int j=0; j<centroids.size(); j++){
       AllHashTables[i].InsertCentroids(centroids[j],M,K,mapMyCentroids,keepTrack);
    }
  	for(int n=0; n<searchEngine.size(); n++){
  		AllHashTables[i].Insert(searchEngine[n],M);
  	}

  }
  //Insert your centroids with the help of the map
  for(int i=0; i<mapMyCentroids.size();i++){
  	Cluster c;
  	c.setCentroid(mapMyCentroids[i].getCentroid());
  	clusters.push_back(c);
  }
  do{
    for(int j=0;j<searchEngine.size();j++){
       cout<<searchEngine[j].getID()<<endl;
       vector<int> buckets;
       int bucket;
       int flag =0;
       for(int i=0;i<L;i++){
           bucket = AllHashTables[i].BucketFound(searchEngine[j]);
           buckets.push_back(bucket);
       }
       for(int i=0;i<buckets.size();i++){
           VectorNode centroid = GetCentroidI(mapMyCentroids,buckets[i]);
           double dis = ManhattanDistance(searchEngine[j].getPoints(),centroid.getPoints());
           if(dis <= minDis){
             if(searchEngine[j].getPointsType() != 'x'){
               searchEngine[j].setPointsType('x');
               int pos = GetCentroid(mapMyCentroids,buckets[i]);
               clusters[pos].pushInCluster(searchEngine[j]);
             }

           }
       }

    }
    minDis = minDis * 2;
  }while(minDis <= maxDis);


  return clusters;
}
