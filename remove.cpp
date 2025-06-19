#include "remove.h"

#include "vector"

ListNode* reverseList(ListNode* head) {
	ListNode* prev = nullptr;
	ListNode* curr = head;
	while (curr) {
		ListNode* tmp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = tmp;
	}
	return prev;
}

ListNode* removeNodes(ListNode* head) {
	head = reverseList(head);
	ListNode* temp = nullptr;
	ListNode* curr = head;
	int maxValue = -1;
	while (curr) {
		maxValue = max(maxValue, curr->val);
		if (maxValue > curr->val) {
			if (!temp) {
				head = head->next;
			}
			else {
				temp->next = curr->next;
				curr = curr->next;
			}
		}
		else {
			temp = curr;
			curr = curr->next;
		}
	}
	head = reverseList(head);
	return head;
}