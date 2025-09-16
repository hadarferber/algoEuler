#include "edge.h"
#include "node.h"


void Edge::set(Node* i, Node* j)
{
	this->i = i;
	this->j = j;
}
void Edge::setCopy(Edge* edge)
{
	this->copy = edge;
}
Edge* Edge::getCopy() {
	return this->copy;
}

Node* Edge::getNeighbor() {
	return this->j;
}

bool Edge::isVisited() {
	return this->visited;
}


void Edge::markAsVisited(bool isUsed)
{
	this->visited = isUsed;
}
