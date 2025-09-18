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
        std::vector<Node*> cycle; // stores the final cycle

        Node* currentNode = &graph.getNodes()[0]; // start from first node
        currPath.push_back(currentNode);

        while (!currPath.empty()) 
        {
            currentNode = currPath.back(); // take last node in path

            if (currentNode->getPositionInEdgesList() < currentNode->getEdges().size()) 
            {
                Edge* currentEdge = currentNode->getEdges()[currentNode->getPositionInEdgesList()]; // next edge

                currentNode->setPositionInEdgesList(currentNode->getPositionInEdgesList() + 1); // move pointer to know the next edge

                if (currentEdge->isVisited()) 
                    continue; // skip if already used

                currentEdge->markAsVisited(); // mark edge visited

                currPath.push_back(currentEdge->getNeighbor()); // move to neighbor
            }
            else 
            {
                cycle.push_back(currentNode); // add node to final cycle
                currPath.pop_back(); // backtrack
            }
        }   

        reverse(cycle.begin(), cycle.end()); // reverse cycle order

        cout << "Eulerian cycle: ";
        for (auto* node : cycle) {
            cout << node->getIndex() << " ";
        }
        cout << endl;
    }

    void Euler::runInefficientAlgorithm() 
    {
        std::vector<Node*> currPath; // current path (stack)
        std::vector<Node*> cycle; // final Eulerian cycle

        Node* currentNode = &graph.getNodes()[0]; // start from the first node
        currPath.push_back(currentNode);

        while (!currPath.empty()) 
        {
            currentNode = currPath.back(); // take the last node in the current path

            std::vector<Edge*>& edges = currentNode->getEdges();
            Edge* currentEdge = nullptr;

            for (int idx = 0; idx < (int)edges.size(); ++idx) {
                Edge* candidate = edges[idx];

                if (!candidate->isVisitedInefficient()) {
                    currentEdge = candidate;
                    break;
                }
            }

            if (currentEdge != nullptr) {

                currentEdge->markAsVisited();

                currPath.push_back(currentEdge->getNeighbor());
            }
            else {
                // no more usable edges from this node, close partial circuit and backtrack
                cycle.push_back(currentNode);
                currPath.pop_back();
            }
        }

        // reverse to get the correct order
        std::reverse(cycle.begin(), cycle.end());

        // print the Eulerian cycle
        std::cout << "Eulerian cycle: ";
        for (std::size_t i = 0; i < cycle.size(); ++i) {
            std::cout << cycle[i]->getIndex() << " ";
        }
        std::cout << std::endl;
    }
    
bool Euler::checkEulerian() {
    for (int u = 0; u < graph.getN(); ++u) 
    {
        Node& node = graph.getNodes()[u];
        if (node.getEdges().size() % 2 != 0) 
        {
            return false;
        }
    }

    std::vector<bool> visited(graph.getN(), false);
    dfs(0, visited);

    for (bool v : visited) 
    {
        if (!v) 
            return false;
    }
    return true;
}

void Euler::dfs(int u, std::vector<bool>& visited) {
    if (visited[u]) 
        return;

    visited[u] = true;

    Node& node = graph.getNodes()[u];

    for (Edge* edge : node.getEdges()) 
    {
        Node* neighbor = edge->getNeighbor();
        int v = neighbor->getIndex() - 1;
        dfs(v, visited);
    }
}


