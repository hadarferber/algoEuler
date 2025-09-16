#include "node.h"
#include "edge.h"

Node::Node(int i)
{
    this->i = i;
    positionInEdgesList = 0;
}

int Node::getIndex() {
    return this->i;
}

void Node::setIndex(int index) {
    this->i = index;
}

int Node::getPositionInEdgesList() {
    return positionInEdgesList;
}

void Node::setPositionInEdgesList(int position) {
    positionInEdgesList = position;
}

std::vector<Edge*>& Node::getEdges() {
    return this->edges;
}
