/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <iostream>

struct ListNode {
	int val;
	struct ListNode* next;
}ListNode;


struct ListNode* Stackhead;
struct ListNode* Stacktail;


struct ListNode* reverseList(struct ListNode* head) {
	struct ListNode* pTemp;
	struct ListNode* pNode;
	Stackhead = (struct ListNode*)malloc(sizeof(struct ListNode));
	Stacktail = Stackhead;
	for (pTemp = head->next; pTemp != NULL; pTemp = pTemp->next) {
		pNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		pNode->val = pTemp->val;
		pNode->next = Stackhead->next;
		Stackhead->next = pNode;
	}
	return Stackhead;
}

struct ListNode* createList(int capacity) {
	struct ListNode* pTemp;
	struct ListNode* Stackhead1 = (struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode* Stacktail1 = Stackhead1;
	for (int i = 0; i < capacity; i++) {
		pTemp = (struct ListNode*)malloc(sizeof(struct ListNode));
		pTemp->val = i;
		Stacktail1->next = pTemp;
		Stacktail1 = Stacktail1->next;
		pTemp->next = NULL;
	}
	return Stackhead1;
}

int main() {
	struct ListNode* test = createList(10);
	reverseList(test);
	return 0;
}