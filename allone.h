#include <string>
#include <unordered_map>

using namespace std;

#ifndef ALL_ONE_INCL
#define ALL_ONE_INCL
#include <cstdio>

class AllOne {
public:
    AllOne();
    void inc(string key);
    void dec(string key);
    string getMaxKey();
    string getMinKey();

private:
    struct nd {
        string value;
        nd* next;
        nd* prev;
    };
    struct Node {
        int freq;
        nd* h;
        nd* t;
        unordered_map<string, nd*> mp;

        Node* prev;
        Node* next;
    };
    Node* head;
    Node* tail;
    unordered_map<string, Node*> map;
};

#endif
