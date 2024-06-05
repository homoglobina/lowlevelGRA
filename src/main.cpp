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

        vector<vector<bool>> matrix(i, vector<bool>(i, false));
        graph = generateDAG(i, j);
        }

    else if (string(argv[1]) == "--non-hamilton"){
        graph = user();
        
    }

/////////////////////////MENU///////////////////////////
    int j = 0;
    cout << endl <<"Possible actions \n";
    cout << "print\t - prints graph\n";
    cout << "find\t - finds something\n";
    cout << "bfs\t - breadth first search\n";
    cout << "dfs\t - depth first search\n";
    cout << "topSort\t - Topological sort\n";
    cout << "exit\t - Exit\n" << endl;
    do{
        string choice;
        //cin.ignore();
        cout << "action> ";
        cin >> choice;

        if (choice == "print" || choice == "Print" || choice == "PRINT"){
            cout << "Print graph\n";
            printGraph(type, graph);
        }
        else if (choice == "find" || choice == "Find" || choice == "FIND"){
            int from, to;
            
            cout << "from>"; cin >> from;
            cout << "to>"; cin >> to;
            
            switch (find(graph, from, to))
            {
            case 1:
                cout << "True: edge (" << from << "," << to << ") exists in the graph" << endl;
                break;
            case 0:
                cout << "False: edge (" << from << "," << to << ") does not exist in the graph" << endl;
                break;
            }
            
        }
        else if (choice == "Depth-first search" || choice == "DFS" || choice == "dfs"){
            dfs(graph, 0);
            }
        else if (choice == "Breath-first search" || choice == "BFS" || choice == "bfs"){
            bfs(graph, 0);
            }
        else if (choice == "topSort" || choice == "Topological sort" || choice == "topsort"){
            cout << "Topological sort\n";
            cout << "1 - Kahn's algorithm\n2 - Tarjan's algorithm\n";
            int choice;
            cout << ">"; cin >> choice;
            if (choice == 1) kahnSort(graph);
            else if (choice == 2) tarjanSort(graph);
            else cout << "Invalid choice\n";
            }
        

        else if (choice == "exit"){
            cout << "Exit\n";
            j = 1;
            }
        else  cout << "Invalid choice\n";
            
    }while (j != 1);




    return 0;
}


        // g++ -c generacja.cpp -o generacja.o
        // g++ -c user.cpp -o user.o
        // g++ -c print.cpp -o print.o
        // g++ -c find.cpp -o find.o
        // g++ -c bfs.cpp -o bfs.o
        // g++ -c topsort.cpp -o topsort.o
        // g++ -c main.cpp -o main.o
        // g++ main.o generacja.o user.o print.o bfs.o find.o topsort.o -o program
