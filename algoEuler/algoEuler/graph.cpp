#include "graph.h"
#include "node.h"
#include "edge.h"

void Graph::addEdge(int i, int j) {
    Edge* edge1 = new Edge(&nodes[i], &nodes[j]);
    Edge* edge2 = new Edge(&nodes[j], &nodes[i]);
    edge1->setCopy(edge2);
    edge2->setCopy(edge1);
    edges.push_back(edge1);
    edges.push_back(edge2);
    nodes[i].getEdges().push_back(edge1);
    nodes[j].getEdges().push_back(edge2);
}

void Graph::sortAdjacency() {
}

std::vector<Node>& Graph::getNodes() {
    return this->nodes;
}

int Graph::getN() {
    return this->n;
}

Graph::~Graph() {
    for (Edge* edge : edges) {
        delete edge;
    }
}
