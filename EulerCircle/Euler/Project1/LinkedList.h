#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H


struct ListNode {
    int value;
    ListNode* next;
    ListNode* twin;
    bool visited;

    ListNode(int v) : value(v), next(nullptr), twin(nullptr), visited(false) {}
};


class LinkedList
{
    int startNode;
	ListNode* head = nullptr;

private:


public:
    LinkedList(int startNode) : head(nullptr), startNode(startNode) {}
    ListNode* getHead() { return head; }
	void insertLexicographically(int v);
    ListNode* findCopyInList(int v, LinkedList* list);

};

#endif

