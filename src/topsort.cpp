#include <iostream>
#include <vector>
#include <algorithm>
#include "graphs.h"

using namespace std;

void kahnSort(vector<Edge> graph) {

    int numVertices = 0; 
    for (const Edge& edge : graph) {
        numVertices = max(numVertices, max(edge.from, edge.to) + 1);
    }

    vector<int> inDegree(numVertices, 0); 
    vector<int> visited; 
    vector<int> stack;  // stopień wejśćiowy 0

    
    for (const Edge& edge : graph) {
        inDegree[edge.to]++;
    }

    
    for (int i = 0; i < numVertices; i++) {
        if (inDegree[i] == 0) {
            stack.push_back(i);
        }
    }

    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();
        visited.push_back(current); 
        for (const Edge& edge : graph) {
            if (edge.from == current) {
                inDegree[edge.to]--;
                if (inDegree[edge.to] == 0) {
                    stack.push_back(edge.to); 
                }
            }
        }
    }


    if (visited.size() != numVertices) {
        cout << "Cycle detected" << endl;
    } else {
        cout << "Topological order: ";
        for (int vertex : visited) {
            cout << vertex << " ";
        }
        cout << endl;
    }
}


void DFS2(vector<Edge>& graph, int start, vector<int>& visited, vector<int>& stack) {
    visited[start] = 1; 
    for (const Edge& edge : graph) {
        if (edge.from == start) { 
            if (visited[edge.to] == 0) { 
                DFS2(graph, edge.to, visited, stack); 
            } else if (visited[edge.to] == 1) { 
                cout << "Cycle detected" << endl;
                return;
            }
        }
    }
    visited[start] = 2; // done
    stack.push_back(start); // wynik
}


void tarjanSort(vector<Edge> graph) {
    vector<int> visited(graph.size(), 0); // 0 - not visited, 1 - visited but not processed, 2 - processed
    vector<int> stack;
    

    // ile powinno być
    int numVertices = 0; 
    for (const Edge& edge : graph) {
        numVertices = max(numVertices, max(edge.from, edge.to) + 1); 
    }


    for (int i = 0; i < graph.size(); ++i) {
        if (visited[i] == 0) { // If vertex is not visited
            DFS2(graph, i, visited, stack); // Perform DFS from the vertex
        }
    }



    // Sprawdzanie czy ok
    if (stack.size() != graph.size()) { 
        cout << "Cycle detected" << endl;
    } else {
        cout << "Topological order: ";
        for (int i = stack.size() - 1; i >= 0; --i) {
            if (stack[i] < numVertices){
                cout << stack[i] << " "; 
            }
        }
        cout << endl;
    }
}
