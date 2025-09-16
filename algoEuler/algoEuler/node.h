#ifndef __NODE_H
#define __NODE_H

#include <vector>

class Edge;
class Node {
    std::vector<Edge*> edges;
    int i;
    int positionInEdgesList = 0;

public:
    // constructor
    Node(int i);

    // functions
    int getIndex();
    void setIndex(int index);

    int getPositionInEdgesList();
    void setPositionInEdgesList(int position);

    std::vector<Edge*>& getEdges();
};

#endif
