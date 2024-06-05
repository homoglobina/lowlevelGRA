#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "graphs.h"

using namespace std;

void printGraph(string type, vector<Edge> graph) {
    if (type == "list" || type == "List") {
        cout << "List: (";
        for (const Edge& edge : graph) {
            cout << edge.from << "->" << edge.to << ",";
        }
        cout << ")" << endl;
    }
    else if (type == "matrix" || type == "Matrix") {
        printMatrix(graph);
    }
    else if (type == "table" || type == "Table") {
        cout << "Table:" << endl;
        cout << "From\tTo" << endl;
        for (const Edge& edge : graph) {
            cout << edge.from << "\t" << edge.to << endl;
        }
    }
    else {
        cout << "Invalid type: " << type << endl;
    }
}

void printMatrix(const vector<Edge>& edges) {
    
    
    int n = 0;
    for (const Edge& edge : edges) {
        n = max({n, edge.from, edge.to});
    }
    n++;

    vector<vector<bool>> adjacencyMatrix(n,vector<bool>(n, false));

    // Populate adjacency matrix based on edges
    for (const Edge& edge : edges) {
        adjacencyMatrix[edge.from][edge.to] = true;
    }

    int a;
    // Print adjacency matrix
    cout << endl << "Adjacency Matrix:" << endl;
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            if (i==1 && j == 1){
                cout << "+" <<" ";
            }
            else if (i == 1){
                cout << "-" << " ";
            }
            else if (j == 1){
                cout << "|" << " ";
            }
            else if (i == 0 && j == 0) {
                cout << "  ";
            }
            else if (i == 0) {
                //a = j - 2;
                cout << j-2 << " ";
            }
            else if (j == 0) {
                //a = i - 2;
                cout << i-2 << " ";
            }
            else{
                cout << adjacencyMatrix[i-2][j-2] << " ";  
            }

        }
        cout << endl;
    }
}