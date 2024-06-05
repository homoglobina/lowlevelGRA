#ifndef GRAPHS_H
#define GRAPHS_H

#include <string>
#include <vector>



struct Edge {
    int from;
    int to;

    Edge(int u, int v);
};

std::vector<Edge> generateDAG(int nodes, int saturation);
std::vector<Edge> user();  

void printGraph(std::string action, std::vector<Edge> graph);
void printMatrix(const std::vector<Edge>& edges);

int find(std::vector<Edge> graph, int from, int to);

void bfs(std::vector<Edge> graph, int start);
void dfs(std::vector<Edge> graph, int start);

void kahnSort(std::vector<Edge> graph);
void tarjanSort(std::vector<Edge> graph);

#endif // GRAPHS_H
