#include "Graph.h"

void Graph::buildGraph(){

    std::string line;
    if (!std::getline(std::cin, line) || line.empty())
        return; // no edges line provided

    std::istringstream iss(line);
    int u, v;

    auto edgeExists = [&](int a, int b) -> bool {
        if (!adjList[a]) return false;
        ListNode* p = adjList[a]->getHead();
        while (p) {
            if (p->value == b) return true;
            p = p->next;
        }
        return false;
        };

    while (iss >> u >> v) {
        if (u <= 0 || u >= (int)adjList.size() ||
            v <= 0 || v >= (int)adjList.size()) {
            std::cout << "Invalid input." << std::endl;
            exit(1);
        }
        if (u == v) continue; // skip self-loop

        // duplicate edge check (undirected): (u,v) or (v,u) already present
        if (edgeExists(u, v) || edgeExists(v, u)) {
            std::cout << "Invalid input." << std::endl;
            exit(1);
        }

        // add edge both ways (undirected graph)
        adjList[u]->insertLexicographically(v);
        adjList[v]->insertLexicographically(u);
    }
   // std::string line;
   // if (!std::getline(std::cin, line) || line.empty())
   //     return; // no edges line provided

   // std::istringstream iss(line);
   // int index, value;
   // while (iss >> index >> value) {
   //     if (index <= 0 || index >= adjList.size() ||
   //         value <= 0 || value >= adjList.size()) {
   //         std::cout << "invalid input" << std::endl;
			//exit(1);
   //         //std::cerr << "Index out of bounds: " << index << " " << value << std::endl;
   //         //continue;
   //     }
   //     if (index == value) continue; // skip self-loop

   //     // add edge both ways (undirected graph)
   //     adjList[index]->insertLexicographically(value);
   //     adjList[value]->insertLexicographically(index);
   // }
}

void Graph::getVertexAmount()
{
	int vertexAmount;

	cin >> vertexAmount;
    cin.ignore();
	if (vertexAmount <= 0)
	{
        std::cout << "invalid input" << std::endl;
        exit(1);
		//cerr << "Number of vertices must be positive." << endl;
		//return;
	}

	adjList.resize(vertexAmount + 1); // we start from index 1

	for (int i = 0; i < vertexAmount + 1; ++i)
	{
		adjList[i] = new LinkedList(i);
	}
}

bool Graph::checkEulerian()
{
	vector<bool> visited = vector<bool>(adjList.size(), false);
	dfsVisit(1, visited); // Start DFS from vertex 1
    return allEvenDegrees() && areAllVisited(visited);
}

void Graph::dfsVisit(int v, vector<bool>& visited)
{
    visited[v] = true;

    ListNode* curr = adjList[v]->getHead();

    while (curr) // Traverse all neighbors of v through the linked list
    {
        int u = curr->value;
        if (!visited[u])
        {
            dfsVisit(u, visited);
        }
        curr = curr->next;
    }
}


bool Graph::allEvenDegrees()
{
    for (int i = 0; i < (int)adjList.size(); i++) // Iterate over all vertices
    {
        if (adjList[i] == nullptr) 
            continue;

        int degree = 0;
        ListNode* curr = adjList[i]->getHead();

        while (curr) // Count the number of neighbors of vertex i
        {
            degree++;
            curr = curr->next;
        }

        if (degree % 2 != 0) 
        {
            return false;
        }
    }
    return true;  // All vertices have even degree

}

bool Graph::areAllVisited(vector<bool>& visited)
{
    for (int i = 1; i < (int)adjList.size(); ++i) {           // start at 1
        if (!adjList[i]) continue;
        bool hasEdge = (adjList[i]->getHead() != nullptr);     // degree > 0
        if (hasEdge && !visited[i]) return false;
    }
    return true;
}

LinkedList* Graph::neighbors(int v) const {
    if (v <= 0 || v >= static_cast<int>(adjList.size())) {
        return nullptr; // out of bounds
    }
    return adjList[v];
}

int Graph::vertexCount() {
    return (int)adjList.size() - 1;
}