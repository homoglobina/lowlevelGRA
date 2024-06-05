#include <iostream>
#include <vector>
#include <string>
#include "graphs.h"

using namespace std;


int main(int argc, char *argv[]) {
    
    if (argc != 2 || (string(argv[1]) != "--hamilton" && string(argv[1]) != "--non-hamilton")){
        cout << "Argument: " << string(argv[1]) << endl;
        cout << "Usage: ./program --hamilton\n";
        exit(1);
    }


    string type;
    cout << "type> "; cin >> type;
    while(type != "matrix" && type != "Matrix" && type != "list" && type != "List" && type != "table" && type != "Table") {
        cout << "Invalid type" << endl;
        cout << "type> "; cin >> type;
    } 
    
    
    vector<Edge> graph;
 
    
    if (string(argv[1]) == "--hamilton"){
        int i,j;
        cout << "nodes>  ";
        cin >> i;
        cout << "saturation> ";
        cin >> j;

        graph = generateDAG(i, j);
        }

    else if (string(argv[1]) == "--non-hamilton"){
        graph = user();
        
    }


    initializeMenu(graph, type);



    return 0;
}


        // g++ -c generacja.cpp -o generacja.o
        // g++ -c user.cpp -o user.o
        // g++ -c print.cpp -o print.o
        // g++ -c find.cpp -o find.o
        // g++ -c bfs.cpp -o bfs.o
        // g++ -c topsort.cpp -o topsort.o
        // g++ -c menu.cpp -o menu.o
        // g++ -c main.cpp -o main.o
        // g++ main.o generacja.o user.o print.o bfs.o find.o topsort.o menu.o -o program
