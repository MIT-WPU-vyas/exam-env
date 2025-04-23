#include <cmath>
#include <iostream>
using namespace std;
#define INFINITE 999

class graph {
    int cost[10][10];
    int tcities;
public:
    graph();
    void create();
    void display();
    void prims(int start_v);
    void print_arrays(int nearest[], int t[][3], int r);  
};


graph::graph() {
    tcities = 0;
    cout << "\n enter no. of cities:";
    cin >> tcities;
    for(int i = 0; i < tcities; i++) {
        for(int j = 0; j < tcities; j++) {
            cost[i][j] = INFINITE;
        }
    }
}

void graph::create() {
    char ch;
    for (int i = 0; i < tcities; i++) {
        for (int j = i+1; j < tcities; j++) {
            cout << "\n is there a connection between " << i <<" "<< j << " (y/n) : ";
            cin >> ch;
            if (ch == 'y') {
                int cost_1;
                cout << "enter the cost between the connection: ";
                cin >> cost_1;
                cost[i][j] = cost_1;
                cost[j][i] = cost_1;
            }
        }
    }
}

void graph::display() {
    for (int i = 0; i < tcities; i++) {
        for(int j = 0; j < tcities; j++) {
            cout << cost[i][j] << " \t";
        }
        cout << endl;
    }
}

void graph::print_arrays(int nearest[], int t[][3], int r) {
    cout << "\nNearest array: ";
    for(int i = 0; i < tcities; i++) {
        cout << nearest[i] << " ";
    }
    cout << "\n (t array):";
    for(int i = 0; i < r; i++) {
        cout << "\nEdge " << i + 1 << ": " << t[i][0] << " - " << t[i][1] << " (cost: " << t[i][2] << ")";
    }
    cout << "\n------------------------\n";
}

void graph::prims(int start_v) {
    int nearest[tcities];
    int t[10][3];
    int mincost = 0;
    
    nearest[start_v] = -1;
    for(int i = 0; i < tcities; i++) {
        if(i != start_v) {
            nearest[i] = start_v;
        }
    }
    
    cout << "\nInitial State:";
    print_arrays(nearest, t, 0);
    
    int r = 0;
    for(int i = 1; i < tcities; i++) {
        int min = INFINITE;
        int j = 0;
        
        for(int k = 0; k < tcities; k++) {
            if(nearest[k] != -1 && cost[k][nearest[k]] < min) {
                j = k;
                min = cost[k][nearest[k]];
            }
        }
        
        t[r][0] = nearest[j];
        t[r][1] = j;
        t[r][2] = min;
        r++;
        mincost += cost[j][nearest[j]];
        nearest[j] = -1;
        
        cout << "\nAfter adding vertex " << j << " to MST:";
        print_arrays(nearest, t, r);
        
        for(int k = 0; k < tcities; k++) {
            if(nearest[k] != -1 && cost[k][nearest[k]] > cost[k][j]) {
                nearest[k] = j;
                cout << "\nUpdated nearest[" << k << "] to " << j;
            }
        }
        
        cout << "\nAfter updating nearest array:";
        print_arrays(nearest, t, r);
    }
    
    cout << "\nFinal MST Cost: " << mincost << endl;
}

int main() {
    graph g;
    int start;
    g.create();
    cout << "\nAdjacency Matrix:\n";
    g.display();
    cout << "\nFrom which node do you want to start the prims algo ?? : ";
    cin >> start;
    g.prims(start);
    return 0;
}

//O(V^2) with adjacency matrix
//O(E+V log V) with priority queue
