#include "LinkedList.h"

void LinkedList::insertLexicographically(int v)
{
	ListNode* newNode = new ListNode(v);

	if (!head) 
	{
		newNode->next = head;
		head = newNode;
		return;
	}

	ListNode* current = head;

	while (current->next && current->next->value < v) {
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
}

ListNode* LinkedList::findCopyInList(int v, LinkedList* list)
{
	ListNode* current = list->head;

	while (current) 
	{
		if (current->value == startNode) 
		{
			return current;
		}
		current = current->next;
	}

	return nullptr;
}


