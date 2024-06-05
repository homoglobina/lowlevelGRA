#include "graphs.h"
#include <algorithm>
#include <ctime>
#include <vector>

using namespace std;

Edge::Edge(int u, int v) : from(u), to(v) {}





// krawędzie

vector<Edge> generateDAG(int nodes, int saturation) {
    vector<Edge> edges;
    vector<vector<bool>> matrix(nodes, vector<bool>(nodes, false));

    srand(time(nullptr));
    

    for (int i = 0; i < nodes; ++i) {
        // Określamy, ile krawędzi wychodzi z bieżącego wierzchołka
        int edgesFromVertex = min(saturation, nodes - i - 1);
        for (int j = 0; j < edgesFromVertex; ++j) {
            // Losowy wierzchołek docelowy
            int to = i + 1 + rand() % (nodes - i - 1);
            // Sprawdzamy, czy krawędź już nie istnieje i czy nie tworzy cyklu
            if (to != i && !matrix[i][to]) {
                matrix[i][to] = true; // Mark edge from i to to
                edges.emplace_back(i, to); // Add edge to the edge list
            }
        }
    }

    return edges;
}



