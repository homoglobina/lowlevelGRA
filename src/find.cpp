#include <iostream>
#include <vector>
#include <algorithm>
#include "graphs.h"

using namespace std;

int find(vector<Edge> graph, int from, int to) {
    for (const Edge& edge : graph) {
        if (edge.from == from && edge.to == to) {
            return 1;
        }
    }
    return 0;
}