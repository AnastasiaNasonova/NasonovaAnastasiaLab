#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>


using namespace std;

class Sort
{
	vector <vector<int>> arc;

public:

	Sort(const vector<vector<int>>& x);
	void TopSort(const unordered_map<int, int>& numVertex);
};

