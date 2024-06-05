#include "graphs.h"
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

Edge::Edge(int u, int v) : from(u), to(v) {}




vector<Edge> generateHamilton(int nodes, int saturation) {
    vector<Edge> edges;
    vector<vector<bool>> matrix(nodes, vector<bool>(nodes, false));
    vector<int> hamiltonianCycle(nodes);

    srand(time(nullptr));

    // Generowanie cyklu Hamiltona
    for (int i = 0; i < nodes; ++i) {
        hamiltonianCycle[i] = i;
    }
    random_shuffle(hamiltonianCycle.begin(), hamiltonianCycle.end());

    for (int i = 0; i < nodes; ++i) {
        int from = hamiltonianCycle[i];
        int to = hamiltonianCycle[(i + 1) % nodes];
        edges.emplace_back(from, to);
        matrix[from][to] = true;
        matrix[to][from] = true;
    }

    // Dodawanie dodatkowych krawędzi zgodnie ze współczynnikiem nasycenia
    for (int i = 0; i < nodes; ++i) {
        int currentEdges = 0;
        for (int j = 0; j < nodes; ++j) {
            if (matrix[i][j]) {
                ++currentEdges;
            }
        }
        
        while (currentEdges < saturation) {
            int to = rand() % nodes;
            if (i != to && !matrix[i][to]) {
                edges.emplace_back(i, to);
                matrix[i][to] = true;
                matrix[to][i] = true;
                currentEdges++;
            }
        }
    }

    // Upewnianie się, że stopień każdego wierzchołka jest parzysty
    for (int i = 0; i < nodes; ++i) {
        int degree = 0;
        for (int j = 0; j < nodes; ++j) {
            if (matrix[i][j]) {
                degree++;
            }
        }

        if (degree % 2 != 0) {
            int to = rand() % nodes;
            while (i == to || matrix[i][to]) {
                to = rand() % nodes;
            }
            edges.emplace_back(i, to);
            matrix[i][to] = true;
            matrix[to][i] = true;
        }
    }

    return edges;
}

vector<Edge> generateNonHamilton(int nodes, int saturation) {
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



