#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V; 
    int adjMatrix[10][10];
public:
    Graph(int vertices) {
        V = vertices;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adjMatrix[i][j] = 999;
            }
        }
    }

    void addEdge(int u, int v,int weight);
    void displayGraph();
    void create();
    int prims(int start_v);
    

};

void Graph :: addEdge(int u, int v,int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; 
    }

void Graph :: displayGraph() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

void Graph :: create(){
    for (int i=0;i<V;i++){
        for (int j=i;j<V;j++){            
            if(j==i){
                continue;
            }
            string choice;
            cout<<"is there a connection between "<<i<<" and "<<j<<"? : ";
            cin>>choice;
            if (choice == "y"){
                if(adjMatrix[i][j] == 999){
                    int cost;
                    cout<<"enter cost for the edge : ";
                    cin>>cost;
                    addEdge(i, j, cost);
                }
            }

        }
    }
}

int Graph:: prims(int start_v) {
    int nearest[10];    
    bool inMST[10];     
    int minEdge[10];    
    int t[10][3];       
    int totalCost = 0, r = 0;

    for (int i = 0; i < V; i++) { 
        nearest[i] = -1;
        inMST[i] = false;
        minEdge[i] = 999;
    }

    minEdge[start_v] = 0; 

    for (int i = 0; i < V - 1; i++) { 
        int min = 999, j = -1;

        for (int k = 0; k < V; k++) { 
            if (!inMST[k] && minEdge[k] < min) {
                min = minEdge[k];
                j = k;
            }
        }

        if (j == -1) break;

        inMST[j] = true; 
        totalCost += min; 

        if (nearest[j] != -1) {
            t[r][0] = nearest[j];
            t[r][1] = j;
            t[r][2] = min;
            r++;
        }

        for (int k = 0; k < V; k++) { 
            if (!inMST[k] && adjMatrix[k][j] < minEdge[k]) {
                minEdge[k] = adjMatrix[k][j];
                nearest[k] = j;
            }
        }
    }

    cout << "\nMinimum Spanning Tree (MST) using Prim's Algorithm:\n";
    for (int i = 0; i < r; i++) {
        cout << "Edge: " << t[i][0] << " - " << t[i][1] << " | Cost: " << t[i][2] << endl;
    }
    cout << "Total Cost of MST: " << totalCost << endl;

    return totalCost;
}

int main(){
    Graph g(5);
    g.create();
    g.displayGraph();
    int startVertex;
    cout << "\nEnter the starting vertex for Prim's Algorithm: ";
    cin >> startVertex;
    g.prims(startVertex);
    return 0;
}

