#ifndef __EULER_H
#define __EULER_H

#include <stdlib.h>
#include <iostream>
#include <stack>
#include "LinkedList.h"

class Graph;

using namespace std;

class Euler
{
	ListNode* EulerHead;
	ListNode* current;
	Graph* graph;

private:
	

public:
	Euler(Graph* graph) : EulerHead(nullptr), current(nullptr), graph(graph) {} ////// for testing
	ListNode* FindCircuitNonEff(int start);
	void AddCircuit(ListNode* cycleHead);
	void AddNode(ListNode* newNode);
	ListNode* FindEulerCycle();
	void PrintCycle();
	ListNode* pickUnusedNeighborNodeNonEff(int v);
	bool edgeAlreadyUsedNonEff(int v, ListNode* node_vu);
	void markCurrentSideVisitedNonEff(ListNode* node_vu);
	ListNode* findVertexWithUnusedEdges(ListNode* cycleHead);



};

#endif

