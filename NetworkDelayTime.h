#ifndef NetworkDelayTime_Included
#define NetworkDelayTime_Included

#include "console.h"
#include "error.h"
#include "vector.h"
#include "HashMap.h"
using namespace std;

struct Edge {
	int from;
	int to;
	int time;
};

int networkDelayTime(HashMap<int, Vector<Edge> >& graph, int n, int k);

#endif