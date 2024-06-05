#include <iostream>
#include <vector>
#include <algorithm>
#include "graphs.h"

using namespace std;

void dfs(vector<Edge> graph, int start) {
    vector<int> visited;
    vector<int> stack;
    stack.push_back(start);
    visited.push_back(start);
    cout << "inline: ";
    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();
        //if (curren not in)
        cout << current << " ";
        for (const Edge& edge : graph) {
            if (edge.from == current) {
                if (find(visited.begin(), visited.end(), edge.to) == visited.end()) {
                    stack.push_back(edge.to);
                    visited.push_back(edge.to);
                }
            }
        }
    }
    cout << endl;
}


void bfs(vector<Edge> graph, int start) {
    vector<int> visited;
    vector<int> queue;
    queue.push_back(start);
    visited.push_back(start);
    cout << "inline: ";
    while (!queue.empty()) {
        int current = queue.front();
        queue.erase(queue.begin());
        cout << current << " ";
        for (const Edge& edge : graph) {
            if (edge.from == current) {
                if (find(visited.begin(), visited.end(), edge.to) == visited.end()) {
                    queue.push_back(edge.to);
                    visited.push_back(edge.to);
                }
            }
        }
    }
    cout << endl;
}