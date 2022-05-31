#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Edge
{
	int src, dest;
};

class Graph
{
private: 
	vector<vector<int>> adjList;
	int N;
	vector<vector<string>> keywords;
	vector<int> impressions;
	vector<int> NumberOfPointers;
	vector<vector<int>> pointingNodes;
	vector<double> Pagerank;
	vector<int> CTR;
	vector<double> PageScore;
	


public:
	
	
	Graph(vector<vector<int>> adj_Listvector, vector<vector<string>> keys, vector<int> imp, vector<int> ctr);
	void start();
	void set_adjlist(vector<vector<int>> adj);
	void set_keywordlist(vector<vector<string>> keys);
	void set_impresssions(vector<int> imp);
	void set_CTR(vector<int> ctr);
	void numpointingnodes();
	void pageranking();
	void pagescoring();
	int oneWordSearch(string word);
	int orSearch(string word, string word2);
	int andSearch(string word, string word2);
	void printGraph();
	
	
};

