#include "Browser.h"
const int startSize = 10;

Browser::Browser() {
	capacity = startSize;
	array = new Node * [capacity];
	for (int i = 0; i < capacity; i++) {
		array[i] = nullptr;
	}
	loglen = 0;
}

void Browser::grow() {
	capacity *= 2;
	Node** newArray = new Node*[capacity];
	for (int i = capacity/2; i < capacity; i++) {
		newArray[i] = nullptr;
	}
	for (int i = 0; i < capacity / 2; i++) {
		newArray[i] = array[i];
	}
	delete[] array;
	array = newArray;
}

void Browser::NewTab() {
	if (loglen == capacity) {
		grow();
	}
	array[loglen] = new Node();
	array[loglen]->head = new nd();
	array[loglen]->tail = new nd();
	array[loglen]->head->next = array[loglen]->tail;
	array[loglen]->tail->prev = array[loglen]->head;
	array[loglen]->head->prev = array[loglen]->tail->next = nullptr;
	array[loglen]->curr = array[loglen]->head;
	loglen++;
}

void Browser::CloseTab(int tabIndex) {
	nd* n = array[tabIndex]->head;
	while (n) {
		nd* temp = n->next;
		delete n;
		n = temp;
	}
	delete array[tabIndex];
	array[tabIndex] = nullptr;
	for (int i = tabIndex; i < capacity; i++) {
		array[i] = array[i+1];
	}
	loglen--;
}

int Browser::Size() {
	return loglen;
}

void Browser::GoToPage(int tabIndex, string url) {
	nd* t = array[tabIndex]->tail;
	nd* curr = array[tabIndex]->curr;
	nd* addable = new nd();
	addable->value = url;
	t->prev = addable;
	addable->next = t;
	addable->prev = curr;
	curr->next = addable;

	array[tabIndex]->curr = addable;
}

string Browser::GetUrl(int tabIndex) {
	if (array[tabIndex]->curr == array[tabIndex]->head) {
		return "";
	}
	return array[tabIndex]->curr->value;
}

void Browser::GoBack(int tabIndex) {
	if (array[tabIndex]->curr != array[tabIndex]->head) {
		array[tabIndex]->curr = array[tabIndex]->curr->prev;
	}
}

void Browser::GoForward(int tabIndex) {
	if (array[tabIndex]->curr->next != array[tabIndex]->tail) {
		array[tabIndex]->curr = array[tabIndex]->curr->next;
	}
}
