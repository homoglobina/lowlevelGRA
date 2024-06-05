#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

class GraphM {
public:
    GraphM(int n) : adjacency(n, vector<bool>(n, false)), size(n) {}

    // Function to add an edge from u to v
    bool addEdge(int u, int v) {
        if (u == v || adjacency[u][v]) {
            return false; // No self-loops and no duplicate edges
        }
        adjacency[u][v] = true;
        if (isCyclic()) {
            adjacency[u][v] = false; // Remove edge if it creates a cycle
            return false;
        }
        return true;
    }

    // Function to check if the graph contains a cycle
    bool isCyclic() {
        vector<bool> visited(size, false);
        vector<bool> recStack(size, false);
        for (int i = 0; i < size; i++) {
            if (isCyclicUtil(i, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

    // Utility function for DFS to detect cycle
    bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (int i = 0; i < size; i++) {
                if (adjacency[v][i] && !visited[i] && isCyclicUtil(i, visited, recStack)) {
                    return true;
                } else if (adjacency[v][i] && recStack[i]) {
                    return true;
                }
            }
        }
        recStack[v] = false;
        return false;
    }

    void printGraph() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << adjacency[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool hasEdge(int u, int v) {
        return adjacency[u][v];
    }

    // Function to perform Kahn's algorithm for topological sorting
    vector<int> kahnSort() {
        vector<int> inDegree(size, 0);
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                if (adjacency[u][v]) {
                    inDegree[v]++;
                }
            }
        }

        queue<int> q;
        for (int i = 0; i < size; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topOrder.push_back(u);

            for (int v = 0; v < size; v++) {
                if (adjacency[u][v]) {
                    inDegree[v]--;
                    if (inDegree[v] == 0) {
                        q.push(v);
                    }
                }
            }
        }

        if (topOrder.size() != size) {
            cout << "Cycle detected in the graph. Topological sorting not possible." << endl;
            return {};
        }

        return topOrder;
    }

    // Function to perform Tarjan's algorithm for topological sorting
    void tarjanSortUtil(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;

        for (int i = 0; i < size; i++) {
            if (adjacency[v][i] && !visited[i]) {
                tarjanSortUtil(i, visited, Stack);
            }
        }

        Stack.push(v);
    }

    vector<int> tarjanSort() {
        vector<bool> visited(size, false);
        stack<int> Stack;

        for (int i = 0; i < size; i++) {
            if (!visited[i]) {
                tarjanSortUtil(i, visited, Stack);
            }
        }

        vector<int> topOrder;
        while (!Stack.empty()) {
            topOrder.push_back(Stack.top());
            Stack.pop();
        }
        return topOrder;
    }

private:
    vector<vector<bool>> adjacency;
    int size;
};

int main() {
    srand(time(0));
    int n;
    double saturation;

    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the saturation (probability of edge creation between 0 and 1): ";
    cin >> saturation;

    GraphM graph(n);

    // Try to add edges based on the given saturation
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v && (static_cast<double>(rand()) / RAND_MAX) < saturation) {
                graph.addEdge(u, v);
            }
        }
    }

    cout << "Generated DAG:" << endl;
    graph.printGraph();

    int u, v;
    cout << "Enter the edge to check (u v): ";
    cin >> u >> v;

    if (graph.hasEdge(u, v)) {
        cout << "There is an edge from " << u << " to " << v << "." << endl;
    } else {
        cout << "There is no edge from " << u << " to " << v << "." << endl;
    }

    vector<int> kahnTopOrder = graph.kahnSort();
    cout << "Topological Sorting using Kahn's Algorithm:" << endl;
    for (int node : kahnTopOrder) {
        cout << node << " ";
    }
    cout << endl;

    vector<int> tarjanTopOrder = graph.tarjanSort();
    cout << "Topological Sorting using Tarjan's Algorithm:" << endl;
    for (int node : tarjanTopOrder) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
