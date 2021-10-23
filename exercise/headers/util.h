#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <time.h>
#include <bitset>

using namespace std;

#include "items.h"
#include "Hash.h"

double dist(item,item);
int32_t module(int,int);
void readDataset(string,Hash*);
vector<double>* produceNdistVector(int,int,int);
int32_t H(item*,int,int);
int32_t G(item*,int,int,int);
int countItems(string);
void answerQueries(Hash,string,int,int);

// double mean = 0.0;
// double stddev = 1.0;

#endif