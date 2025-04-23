#include <iostream>
using namespace std;

class graph {
private:
    int n;
    int cost[10][10];

public:
    graph(int vertices) {
        n = vertices;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cost[i][j] = 999;  
            }
        }
    }

    void displayGraph();
    void addEdge(int u, int v, int weight);
    void create();
    int prims(int start_v);
};

void graph::displayGraph() {
    cout << "\nGraph Cost Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << cost[i][j] << " ";
        }
        cout << endl;
    }
}

void graph::addEdge(int u, int v, int weight) {
    cost[u][v] = weight;
    cost[v][u] = weight;
}

void graph::create() {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {  
            char choice;
            cout << "Is there an edge between " << i << " and " << j << "? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                int c;
                cout << "Enter cost for the edge: ";
                cin >> c;
                addEdge(i, j, c);
            }
        }
    }
}

int graph::prims(int start_v) {
    int mincost = 0;
    int nearest[n];
    int t[n][3];  
    int r = 0;

    nearest[start_v] = -1;
    for (int i = 0; i < n; i++) {
        if (i != start_v) {
            nearest[i] = start_v;
        }
    }
    for (int a=0;a<n;a++){
        cout<<a<<" : "<<nearest[a]<<"  ";
    }
    cout<<endl;

    for (int i = 1; i < n; i++) { 
        cout<<"nearest array:"; 
        int min = 999;
        int j = -1;


        for (int k = 0; k < n; k++) {
            if (nearest[k] != -1 && cost[k][nearest[k]] < min) {
                j = k;
                min = cost[k][nearest[k]];
            }
        }

        if (j == -1) {
            cout << "Error: Graph is not fully connected.\n";
            return -1;
        }

        t[r][0] = nearest[j];
        t[r][1] = j;
        t[r][2] = min;
        r++;

        mincost += min;
        nearest[j] = -1;
        for (int a=0;a<n;a++){
            cout<<a<<" : "<<nearest[a]<<"  ";
        }
        cout<<endl;

        for (int k = 0; k < n; k++) {
            if (nearest[k] != -1 && cost[k][nearest[k]] > cost[k][j]) {
                nearest[k] = j;
            }
        }

        
    }

    cout << "\nMinimum Spanning Tree (MST) using Prim's Algorithm:\n";
    for (int i = 0; i < r; i++) {
        cout << "Edge: " << t[i][0] << " - " << t[i][1] << " | Cost: " << t[i][2] << endl;
    }
    cout << "Total Cost of MST: " << mincost << endl;
    return mincost;
}

int main() {
    int N;
    cout << "Enter number of vertices in the graph: ";
    cin >> N;

    if (N <= 0 || N > 10) {
        cout << "Invalid number of vertices. Please enter between 1 and 10.\n";
        return 1;
    }

    graph g(N);
    g.create();
    g.displayGraph();

    int startVertex;
    cout << "\nEnter the starting vertex for Prim's Algorithm (0 to " << N - 1 << "): ";
    cin >> startVertex;
    g.prims(startVertex);
    return 0;
}
