#ifndef __EDGE_H
#define __EDGE_H

class Node;

class Edge {

	Node* i;
	Node* j;
	bool visited = false;
	Edge* copy;

public:	

	// Constructor
	Edge(Node* i, Node* j) {
		set(i, j);
	}

	// Functions
	void set(Node* i,Node* j);
	void setCopy(Edge* edge);
	void markAsVisited(bool isUsed);
	Edge* getCopy();
	Node* getNeighbor();
	bool isVisited();

};
#endif