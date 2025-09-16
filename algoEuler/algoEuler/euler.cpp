#include "euler.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

Euler::Euler(Graph& g) : graph(g) {}


void Euler::runEfficientAlgorithm() {
    std::vector<Node*> currPath;
    std::vector<Node*> cycle;

    Node* currentNode = &graph.getNodes()[0];
    currPath.push_back(currentNode);

    while (!currPath.empty()) {
        currentNode = currPath.back();

        if (currentNode->getPositionInEdgesList() < currentNode->getEdges().size()) {
            Edge* currentEdge = currentNode->getEdges()[currentNode->getPositionInEdgesList()];
            currentNode->setPositionInEdgesList(currentNode->getPositionInEdgesList() + 1);

            if (currentEdge->isVisited()) continue;

            currentEdge->markAsVisited(true);
            currentEdge->getCopy()->markAsVisited(true);

            currPath.push_back(currentEdge->getNeighbor());
        }
        else {
            cycle.push_back(currentNode);
            currPath.pop_back();
        }
    }

    reverse(cycle.begin(), cycle.end());

    cout << "Eulerian cycle: ";
    for (auto* node : cycle) {
        cout << node->getIndex() << " ";
    }
    cout << endl;
}

bool Euler::checkEulerian() {
    for (int u = 0; u < graph.getN(); ++u) {
        Node& node = graph.getNodes()[u];
        if (node.getEdges().size() % 2 != 0) {
            return false;
        }
    }

    std::vector<bool> visited(graph.getN(), false);
    dfs(0, visited);

    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

void Euler::dfs(int u, std::vector<bool>& visited) {
    if (visited[u]) return;
    visited[u] = true;

    Node& node = graph.getNodes()[u];
    for (Edge* edge : node.getEdges()) {
        Node* neighbor = edge->getNeighbor();
        int v = neighbor->getIndex() - 1;
        dfs(v, visited);
    }
}
