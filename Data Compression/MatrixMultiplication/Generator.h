#ifndef GENERATE_H 
#define GENERATE_H

#include "Generator.h"
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;

void showArr (vector<vector<int>>& arr);
void showArr (vector<vector<vector<int>>>& arr);
vector<vector<int>> generate(int n, double p);
vector<vector<vector<int>>> generateMany(int l, int n, double p);
pair<vector<vector<int>>, vector<vector<int>>> generatePair(int n, double p);
pair<vector<vector<int>>, vector<vector<int>>> generatePair(int n1, double p1, int n2, double p2);
vector<pair<vector<vector<int>>, vector<vector<int>>>> generateManyPairs(int l, int n, double p);
vector<pair<vector<vector<int>>, vector<vector<int>>>> generateManyPairs(int l, int n1, double p1, int n2, double p2);

#endif
