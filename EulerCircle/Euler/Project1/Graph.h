#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <sstream> 
#include <stdlib.h>
#include <vector>
#include "LinkedList.h"
#include "Euler.h"

class Euler;

using namespace std;

class Graph
{
	std::vector<LinkedList*> adjList;

private:


	 
public:
	Graph() : adjList() {}
	void buildGraph();
	void getVertexAmount();
	void dfsVisit(int v, vector<bool>& visited);
	bool checkEulerian();
	bool allEvenDegrees();
	bool areAllVisited(vector<bool>& visited);
	LinkedList* neighbors(int v) const;
	int vertexCount();






};

#endif