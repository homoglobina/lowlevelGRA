#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>


using namespace std;


// LISTA SASIEDZTWA



struct Vertex {
    Vertex(int v, vector<int> &a) : id(v), adjacents(a) {}
    int id;
    vector<int> adjacents;
};

class Graph {
public:
    Graph(vector<Vertex> &v) : vertices(v) {}
    vector<Vertex> vertices;

    void display() {
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.id << " -> ";
            for (int adj : vertex.adjacents) {
                cout << adj << " ";
            }
            cout << endl;
        }
    }
    void findEdge(int from, int to) {
        for (const auto& vertex : vertices) {
            if (vertex.id == from) {
                for (int adj : vertex.adjacents) {
                    if (adj == to) {
                        cout << "Edge found: " << from << " -> " << to << endl;
                        return;
                    }
                }
            }
        }
        cout << "Edge not found: " << from << " -> " << to << endl;
    }

    void kahnSort() {
        vector<int> inDegree(vertices.size(), 0);

        // Calculate in-degrees of all vertices
        for (const auto& vertex : vertices) {
            for (int adj : vertex.adjacents) {
                inDegree[adj]++;
            }
        }

        // Queue for vertices with zero in-degree
        queue<int> zeroInDegree;
        for (int i = 0; i < vertices.size(); ++i) {
            if (inDegree[i] == 0) {
                zeroInDegree.push(i);
            }
        }

        vector<int> topologicalOrder;
        while (!zeroInDegree.empty()) {
            int v = zeroInDegree.front();
            zeroInDegree.pop();
            topologicalOrder.push_back(v);

            for (int adj : vertices[v].adjacents) {
                inDegree[adj]--;
                if (inDegree[adj] == 0) {
                    zeroInDegree.push(adj);
                }
            }
        }

        // Check for cycle in the graph
        if (topologicalOrder.size() != vertices.size()) {
            cout << "Graph has a cycle, topological sorting not possible!" << endl;
            return;
        }

        // Print topological order
        cout << "Topological Order: ";
        for (int v : topologicalOrder) {
            cout << v << " ";
        }
        cout << endl;
    }


    void tarjanSort() {
        vector<bool> visited(vertices.size(), false);
        stack<int> Stack;

        for (int i = 0; i < vertices.size(); ++i) {
            if (!visited[i]) {
                tarjanSortUtil(i, visited, Stack);
            }
        }

        // Print topological order
        cout << "Topological Order: ";
        while (!Stack.empty()) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
        cout << endl;
    }

private:
    void tarjanSortUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;

        for (int adj : vertices[v].adjacents) {
            if (!visited[adj]) {
                tarjanSortUtil(adj, visited, Stack);
            }
        }

        Stack.push(v);
    }


};

Graph generateAcyclicGraph(int numNodes, double saturation) {
    vector<Vertex> vertices;

    // Initialize vertices
    for (int i = 0; i < numNodes; ++i) {
        vector<int> empty;
        vertices.push_back(Vertex(i, empty));
    }

    // Calculate maximum possible edges in a DAG
    int maxEdges = (numNodes * (numNodes - 1)) / 2;
    int targetEdges = static_cast<int>(maxEdges * saturation);

    // Seed random number generator
    srand(static_cast<unsigned>(time(0)));

    // Add edges while maintaining acyclic property
    int edgesAdded = 0;
    while (edgesAdded < targetEdges) {
        int from = rand() % numNodes;
        int to = rand() % numNodes;

        // Ensure 'from' is less than 'to' to maintain acyclic property
        if (from < to) {
            // Check if edge already exists
            bool edgeExists = false;
            for (int adj : vertices[from].adjacents) {
                if (adj == to) {
                    edgeExists = true;
                    break;
                }
            }
            if (!edgeExists) {
                vertices[from].adjacents.push_back(to);
                edgesAdded++;
            }
        }
    }

    return Graph(vertices);
}








int main() {
    int numNodes, x,y;
    double saturation;

    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    cout << "Enter the saturation level (0 to 1): ";
    cin >> saturation;

    // DAG generation
    Graph graph = generateAcyclicGraph(numNodes, saturation);
    graph.display();
    
    
    cout << "From:"; cin >> x;
    cout << "To:"; cin >> y;
    graph.findEdge(x, y);


    graph.kahnSort();

    graph.tarjanSort();

    return 0;
}
