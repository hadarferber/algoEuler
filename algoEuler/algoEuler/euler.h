#ifndef __EULER_H
#define __EULER_H

#include "graph.h"
#include <vector>

class Euler {
    Graph& graph;                 // was: Graph graph;
public:
    explicit Euler(Graph& g);     // was: Euler(const Graph& g);
    void runEfficientAlgorithm();
    void runInefficientAlgorithm();

    bool checkEulerian();
private:
    void dfs(int u, std::vector<bool>& visited);
};
#endif
