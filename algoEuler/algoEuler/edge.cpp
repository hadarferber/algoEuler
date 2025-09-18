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
	return this->visited || (this->copy && this->copy->visited);
}

bool Edge::isVisitedInefficient() 
{
    if (this->visited) 
        return true;

    if (!this->j) 
        return false;

    std::vector<Edge*>& jEdges = this->j->getEdges();

    for (Edge* e : jEdges) 
    {
        if (e->getNeighbor() == this->i) 
        {
            return e->visited;
        }
    }
    return false;
}

void Edge::markAsVisited()
{
	this->visited = true;
}
