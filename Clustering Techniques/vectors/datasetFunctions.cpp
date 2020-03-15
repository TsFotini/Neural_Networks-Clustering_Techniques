#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "functions.h"
#include "initialize.h"
#include "assignment.h"
#include "Cluster.h"
#include "update.h"
#include "eval.h"
#include <ctime>
using namespace std;

void print(string message){
  cout<<endl;
  cout<<message<<endl;
  cout<<endl;
}

void PrintVectorPoints(vector<double> vec){
  for(int i=0; i< vec.size(); i++){
    cout<<vec[i]<<" ";
  }
  cout<<endl;
}

void PrintDocument(vector<vector<string>> vec){
	for(int i=0; i<vec.size(); i++){
		for(int j=0; j<vec[i].size(); j++){
			cout<<vec[i][j];
		}
		cout<<endl;
	}
}

bool fexists(string filename){
  ifstream ifile(filename.c_str());
  return (bool)ifile;
}

int countlines(string filename){
  int count =0;
  string line;
  if(fexists(filename) == true){
    ifstream file(filename);
    while (getline(file, line)){
      count++;
    }
  }
  else {
    count = -1;
  }
  return count -1;
}

vector<string> tokenizeLine(string line){
  vector<string> tokens;
  vector<char> delim;
  delim.push_back(',');
  delim.push_back(' ');
  stringstream check1(line);
  string intermediate;

  for(int i=0; i<delim.size(); i++){
	 while(getline(check1, intermediate, delim[i]))
	 {
		tokens.push_back(intermediate);
	 }
  }

  return tokens;

}

vector<string> tokenizeDoc(string line){
  vector<string> tokens;
  stringstream check1(line);
  string intermediate;

  while(getline(check1, intermediate, ' '))
  {
    tokens.push_back(intermediate);
  }
  return tokens;

}

vector<vector<string>> Documents(string filename){
	vector<vector<string>> AllParams;
	if(countlines(filename) == 0){
		print(" File is empty! ");
		exit(-1);
	}
	else{
		vector<string> tokens;
		ifstream file(filename);
		string str;
		while (getline(file, str)) {
			tokens = tokenizeDoc(str);
			AllParams.push_back(tokens);
		}
	}
	return AllParams;
}

int Parameter(string doc, vector<vector<string>> allDocs){
  int tmp = 2;
  for(int i=0; i< allDocs.size(); i++){
	   if(allDocs[i][0] == doc){
		     if(allDocs[i].size() == 2){
			        stringstream convert(allDocs[i][1]);
      	      convert >> tmp ;
		     }
	   }
  }
  return tmp;
}

string fileType(string filename){
  ifstream infile(filename);
  string line;
  getline(infile, line);
  return line;
}

VectorNode CreateVectorPoint(string line){
  vector<string> temp;
  double converter = 0;
  vector<double> points;
  VectorNode obj;
  temp = tokenizeLine(line);
  for(int i = 0; i < temp.size(); i++){
    if(i==0){
		obj.setID(temp[0]);
	}
	else{
		converter = atof(temp[i].c_str());
		points.push_back(converter);
	}
  }
  obj.setPoints(points);
  return obj;
}

VectorNode * CreateSearchEngine(string filename){
  string line;
  int i = 0;
  int count = 0;
  int countLines = countlines(filename);
  VectorNode *vectorToReturn = new VectorNode[countLines];
  if(fexists(filename) == true){
    ifstream file(filename);
    while (getline(file, line) && i < countLines){
	  count++;
	  if(count == 1){
		continue;
	  }
	  else{
		vectorToReturn[i] = CreateVectorPoint(line);
		i++;
	  }

    }
  }
  else{
    print("File does not exist!");
    exit(1);
  }
  return vectorToReturn;
}

void ShowMenu(){
  cout<<"\t\t\t\t\t\t MENU \t\t\t\t\t\t"<<endl;
  cout<<"Initialization\n";
  cout<<"1. Random Selection of K points/curves Kmeans  --> [Type kmeans]\n";
  cout<<"\t\t\t1.1 Random Selection Kmedoids --> [Type kmedoids]\n";
  cout<<"2. Kmeans++ --> [Type ++]\n";
  cout<<endl;
  cout<<"Assignment\n";
  cout<<"3. Lloyds Assignment --> [Type lloyds]\n";
  cout<<"4. Assignment by range --> [Type range]\n";
  cout<<endl;
  cout<<"Update\n";
  cout<<"5. PAM --> [Type PAM]\n";
  cout<<"6. MeanVector/DTW --> [Type Mean]\n";
  cout<<endl;
}

Results Algorithms(VectorNode *allInputs,int countLines,int K,int L,int k,string initial, string assign, string update){
    vector<VectorNode> centroids;
    vector<Cluster> clusters;
    vector<Cluster> final;

    clock_t begin, end, begin2, end2;
	begin = clock();
    if(initial == "kmeans" || initial =="kmeans\n"){
      centroids = RandomMeanCentroids_kmeans(allInputs[0],K);
    }
    else if(initial == "kmedoids" || initial == "kmedoids\n"){
      cout<<"kmedoids r";
      centroids = RandomDatasetCentroids_kmedoids(allInputs,countLines,K);
    }
    else{
      cout<<"++";
      centroids = InitializationPlus(allInputs,countLines,K);
    }
    //Assignment
    if(assign == "lloyds" || assign =="lloyds\n"){
      cout<<"lloyds";
      assign = "lloyds";
      clusters = LloydsAlgorithm(centroids,allInputs,countLines);
    }
    else{
      cout<<"range";
      clusters = AssignmentByRange(centroids,allInputs,countLines,K,L,k);
    }
    //update
    if(update == "PAM" || update == "PAM\n"){
      cout<<"pam\n";
      final = PAM(clusters);
    }
    else{
      cout<<"mean\n";
      final = meanUpdate(centroids,allInputs,countLines,allInputs[0].getPoints().size(),K,K,L,k,assign);

    }
	end = clock();
	vector<double> sil = evalSilhouette(final);
	double avg = AverageSilhouette(sil);
	double tm = (double)(end - begin) / CLOCKS_PER_SEC;

	Results res;
	res.avg_sil = avg;
	res.finalCluster = final;
	res.initial = initial;
	res.assign = assign;
	res.update = update;
	res.tm = tm;
	return res;
}

Results BestAlgorithm(vector<Results> res){
	double min = 9999999;
	int found ;
	for(int i=0; i< res.size(); i++){
		if(res[i].avg_sil < min){
			min = res[i].avg_sil;
			found = i;
		}
	}
	return res[found];
}

void ChooseMenu(const char* path,Results res,string complete){

  vector<Cluster> final = res.finalCluster;
  if(fexists(path) == true){
    print("File exists! It will be deleted and replaced!");
    remove(path);
  }
  ofstream file_(path);
  if (file_.is_open()){
    file_<<"Algorithm: "<<res.initial<<" x "<<res.assign<<" x "<<res.update<<"\n";
    //Initialization


    for(int i=0;i<final.size();i++){
      file_<<"Cluster "<<i+1<<" : ";
      file_<<"{ Clusters size : "<<final[i].getPoints().size()<<", ";
      file_<<"Centroid : ";
	  file_<<final[i].getCentroid().getID();
	  cout<<final[i].getCentroid().getID();
      vector<double> points = final[i].getCentroid().getPoints();
      for(int j=0;j<points.size();j++){
        file_<<points[j]<<" ";
      }
      file_<<" } \n";
      if(complete == "true" || complete == "true\n" || complete == "true "){

		file_<<"\n";
        vector<VectorNode> temp = final[i].getPoints();
        file_<<"\n";
        for(int j=0;j<temp.size();j++){
          file_<<temp[j].getID()<<" ";
        }
        file_<<"\n";
      }

    }
    file_<<"Clustering time : "<<res.tm<<" \n";
    file_<<"Silhouette : [ ";
    vector<double> sil = evalSilhouette(final);
    for(int j=0;j<sil.size();j++){
      file_<<sil[j]<<", ";
    }
    file_<<AverageSilhouette(sil)<<" ]";

  }
}
