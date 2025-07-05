#ifndef Browser_Included
#define Browser_Included

#include "console.h"
using namespace std;

class Browser {
public:
	Browser();
	void NewTab();
	void CloseTab(int tabIndex);
	int Size();
	void GoToPage(int tabIndex, string url);
	string GetUrl(int tabIndex);
	void GoBack(int tabIndex);
	void GoForward(int tabIndex);

private:
	struct nd {
		string value;
		nd* next;
		nd* prev;
	};
	struct Node {
		nd* curr;
		nd* head;
		nd* tail;
	};
	Node** array;
	int loglen;
	int capacity;
	void grow();
};

#endif;