#include "Euler.h"
#include "Graph.h"


// find circle
ListNode* Euler::FindCircuitNonEff(int start)
{
    if (!graph) return nullptr;

    // ??? ????? (????? ?? start)
    ListNode* head = new ListNode(start);
    ListNode* tail = head;

    int v = start;

    while (true) {
        // ??? ??? ????? ?? ????? ?? v
        ListNode* node = graph->neighbors(v)->getHead();
        while (node) {
            if (!edgeAlreadyUsedNonEff(v, node)) {
                break; // ????? ??? ?? ?????
            }
            node = node->next;
        }

        if (!node) {
            // ??? ???? ????? ?? ??????? ???????? ?????? -> ??????
            break;
        }

        int u = node->value;

        // ???? ?? ???? (v,u) ??????? ??? ?????? ????
        node->visited = true;

        // ?????? ?? u ??????
        ListNode* newNode = new ListNode(u);
        tail->next = newNode;
        tail = newNode;

        // ?????? ???????? u
        v = u;

        // ?? ????? ?????? ?????? ???? ???? ????? ???? -> ?? ???? ???
        if (v == start) {
            ListNode* check = graph->neighbors(start)->getHead();
            bool hasUnused = false;
            while (check) {
                if (!edgeAlreadyUsedNonEff(start, check)) {
                    hasUnused = true;
                    break;
                }
                check = check->next;
            }
            if (!hasUnused) break;
        }
    }

    return head;

  /*  if (!graph)
  //      return nullptr;

  //  stack<int> S;
  //  ListNode* cycleHead = nullptr; // result list built by prepending

  //  S.push(start);

  //  while (!S.empty()) 
  //  {
  //      int v = S.top();

  //      // Pick an unused edge (v->u) by linear scans
  //      ListNode* node_vu = pickUnusedNeighborNodeNonEff(v);

  //      if (node_vu) {
  //          int u = node_vu->value;

  //          // Consume (v->u) on current side ONLY
  //          markCurrentSideVisitedNonEff(node_vu);

  //          // Continue walk
  //          S.push(u);
  //      }
  //      else {
  //          // No more unused edges from v: pop and prepend v to the circuit
  //          S.pop();
  //          ListNode* newNode = new ListNode(v);
  //          newNode->next = cycleHead;
  //          cycleHead = newNode;
  //      }
  //  }

  //  ////////////////////////////////// checking print
  //  // Print all nodes in a linked list starting from 'head'
  //      ListNode* current = cycleHead;
  //      while (current) {
  //          std::cout << current->value;
  //          if (current->next) {
  //              std::cout << " -> ";
  //          }
  //          current = current->next;
  //      }
  //      std::cout << std::endl;
		///////////////////////////////////

  //  return cycleHead;*/

}


ListNode* Euler::FindEulerCycle()
{
    if (!graph) return nullptr;

    // 1. Find a start vertex with degree > 0
    int n = graph->vertexCount(); // make sure Graph has this function
    int start = -1;
    for (int v = 1; v <= n; ++v) {
        LinkedList* L = graph->neighbors(v);
        if (L && L->getHead()) {
            start = v;
            break;
        }
    }
    if (start == -1) {
        // no edges in the graph ? empty cycle
        EulerHead = nullptr;
        return nullptr;
    }

    // 2. Build an initial local circuit from 'start'
    EulerHead = FindCircuitNonEff(start);

    // 3. While some vertex in the current tour still has unused edges
    ListNode* pivot = findVertexWithUnusedEdges(EulerHead);
    while (pivot) {
        // Build another circuit starting at this pivot vertex
        ListNode* newCycle = FindCircuitNonEff(pivot->value);
        // Splice the new cycle into the main Euler tour
        AddCircuit(newCycle);
        // Look again if there are more unused edges
        pivot = findVertexWithUnusedEdges(EulerHead);
    }

    // 4. Return the head of the full Eulerian cycle
    return EulerHead;
}

void Euler::PrintCycle()
{
    ListNode* current = EulerHead;
	std::cout << "Euler circuit: ";
    while (current) {
        std::cout << current->value;
        if (current->next) {
            std::cout << ", ";  // comma and space
        }
        current = current->next;
    }
    std::cout << std::endl;
}


// Return the first adjacency-list node (v->u) whose edge (v,u) is not used yet.
// Non-efficient: scans from the head every call.
ListNode* Euler::pickUnusedNeighborNodeNonEff(int v) {
    LinkedList* nbrs = graph->neighbors(v);
    if (!nbrs) return nullptr;

    ListNode* node = nbrs->getHead();
    while (node) {
        if (!edgeAlreadyUsedNonEff(v, node)) {
            return node; // (v->u) is available
        }
        node = node->next;
    }
    return nullptr;
}

// Decide whether edge (v,u) is already used by checking BOTH directions:
// 1) our side node_vu->visited
// 2) linear scan of u's list to find (u->v) and check its visited flag.
bool Euler::edgeAlreadyUsedNonEff(int v, ListNode* node_vu) {
    if (!node_vu) return true;
    if (node_vu->visited) return true; // our side already used

    int u = node_vu->value;
    LinkedList* uNbrs = graph->neighbors(u);
    if (!uNbrs) return false;

    ListNode* p = uNbrs->getHead();
    while (p) {
        if (p->value == v) {
            return p->visited; // counterpart visited -> edge considered used
        }
        p = p->next;
    }
    // If counterpart not found (shouldn't happen in a proper undirected build), treat as unused.
    return false;
}

// Consume edge on the current side only: mark (v->u) visited, do NOT mark (u->v).
void Euler::markCurrentSideVisitedNonEff(ListNode* node_vu) {
    if (node_vu) 
        node_vu->visited = true;
}

// find node with unused edges, non efficient
ListNode* Euler::findVertexWithUnusedEdges(ListNode* cycleHead) {
    ListNode* curr = cycleHead;
    while (curr) {
        // ?? ?? ????? ??? ?????? ???, ????? ?? ????? ???
        ListNode* node = pickUnusedNeighborNodeNonEff(curr->value);
        if (node != nullptr) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void Euler::AddCircuit(ListNode* newCycle) {
    if (!newCycle || !EulerHead) return;

    int startValue = newCycle->value;

    // Find the matching vertex in the main Euler cycle
    ListNode* insertAfter = EulerHead;
    while (insertAfter && insertAfter->value != startValue) {
        insertAfter = insertAfter->next;
    }

    if (!insertAfter) {
        std::cerr << "Error: pivot vertex not found in main cycle" << std::endl;
        return;
    }

    // Skip the first node of newCycle (it equals insertAfter->value)
    newCycle = newCycle->next;
    if (!newCycle) return; // nothing to splice

    // Find tail of the new cycle
    ListNode* tail = newCycle;
    while (tail->next) {
        tail = tail->next;
    }

    // Splice: insertAfter -> newCycle ... tail -> insertAfter->next
    tail->next = insertAfter->next;
    insertAfter->next = newCycle;
}