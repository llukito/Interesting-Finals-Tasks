#include <string>
#include "vector.h"


using namespace std;

struct edgeT {
	int from;
	int to;
	int weight;
};

int removeCycleMin(Vector<edgeT*>& graph);