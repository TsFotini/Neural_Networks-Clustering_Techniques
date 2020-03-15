#ifndef RESULTS_H
#define RESULTS_H
#include <vector>
#include "Cluster.h"
using namespace std;

class Results{
  
public:
  vector<Cluster> finalCluster;
  string initial;
  string assign;
  string update;
  double avg_sil;
  double tm;
};

#endif