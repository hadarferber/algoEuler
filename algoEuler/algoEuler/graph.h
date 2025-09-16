#ifndef __GRAPH_H
#define __GRAPH_H

#include <vector>
#include "edge.h"
#include "node.h"

class Graph {
    int n;
    std::vector<Node> nodes;
    std::vector<Edge*> edges;

public:
    // constructor
    Graph(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            Node newNode = Node(i + 1);
            nodes.push_back(newNode);
        }
    }

    void addEdge(int i, int j);
    void sortAdjacency();
    int getN();
    std::vector<Node>& getNodes();

    // destructor
    ~Graph();
};

#endif
