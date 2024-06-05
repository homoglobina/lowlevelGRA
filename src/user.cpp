#include "graphs.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


vector<Edge> user(){
    vector<int> visited;

    vector<Edge> edges;
    string input;

    int nodes;
    cout << "nodes>> ";
    cin >> nodes;

    cin.ignore();

    vector<int> vertices;               // Tworzymy krawędzie
    for (int i = 0; i < nodes; ++i) {
        
        cout << i <<" >> ";
        getline(cin, input);
        stringstream ss(input);
        int num;

        while (ss >> num) {
            int cnt = count(visited.begin(), visited.end(), num);
            if (num >= nodes || num < 0 || num == i || cnt > 0) { //|| edges[i].to == num
                cout << "Invalid input: "<< num << endl;
            }
            else {
                edges.emplace_back(i,num);
                visited.push_back(num);
            }
        }      
        visited.clear();

    }

    return edges;


}