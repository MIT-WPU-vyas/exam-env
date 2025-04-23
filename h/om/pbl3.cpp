/*
============================================================================
Name        : pbl3.cpp
Author      : Om
Subject     : Project Based Learning
Description : Prim's Algorithm
============================================================================
*/

#include <iostream>

using namespace std;

class graph{

	int cost[10][10];
    int v;
    int nearest[10];
    int t[10][2];
    int mincost;

	public:
    	graph();
    	void create();
    	void display();
    	void prims();
};

int main() {

	graph g;
	int choice;

	do {
		cout << endl << "Enter the Desired Operation:" << endl
				<< "1. Create an Adjacency Matrix" << endl
				<< "2. Display the Adjacency Matrix" << endl
				<< "3. Execute Prim's Algorithm" << endl
				<< "4. EXIT" << endl
				<< "Choice:";
		cin >> choice;
		cout << endl;

		switch(choice) {

			case 1:
				g.create();
				break;

			case 2:
				g.display();
				break;

			case 3:
				g.prims();
				break;

			case 4:
				break;

			default:
				cout << endl << "Please Enter Correct Inputs" << endl;
				break;
		}
	}while(choice != 4);
}

graph::graph() {
	mincost = 0;


	cout << "Enter the Total Number of Vertices:";
	cin >> v;

	for(int i = 0; i < v; i++) {
		for(int j = 0; j < v; j++) {
			cost[i][j] = 999;
		}
	}
}

void graph::create() {
    char ch;
    for(int i = 0; i < v; i++) {
    	for(int j = 0; j < i; j++) {
    		cout << endl << "Is there a connection between " << i << " " << j << "(y or n):";
    		cin >> ch;

    		if(ch == 'y') {
    			int dist;
    			cout << "Cost of edge (" << i << "," << j << "):";
    			cin >> dist;
    			cost[i][j] = dist;
    			cost[j][i] = dist;
    		}
    	}
    }
}

void graph::display() {

	cout << "  ";
	for (int i = 0; i < v; i++) {
		cout << "\t" << i;
	}
	cout << endl;
	for (int i = 0; i < v; i++) {
		cout << i;
		for (int j = 0; j < v; j++) {
			cout << "\t" << cost[i][j];
		}
		cout << endl;
	}
}

void graph::prims() {
	int start;
	cout << endl << "Enter the Starting Vertex:";
	cin >> start;

	nearest[start] = -1;

	for(int i = 0; i < v; i++) {
		if(i != start) {
			nearest[i] = start;
		}
	}
	int r = 0;

	for(int i = 0; i < v-1; i++) {
		int min = 999;
		int j;

		for(int k = 0; k < v; k++) {
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

		for(int k = 0; k < v; k++) {
			if(nearest[k] != -1 && cost[k][nearest[k]] > cost[k][j]) {
				nearest[k] = j;
			}
		}

		cout << endl << "Pass " << i+1 << endl;

		cout << endl << "T ARRAY:" << endl << endl;
		for(int m = 0; m < v; m++) {                //PRINT T ARRAY
			for(int n = 0; n < 3; n++) {
				cout << t[m][n] << "\t";
			}
			cout << endl;
		}

		cout << endl <<  "NEAREST ARRAAY:" << endl;
		for(int m = 0; m < v; m++) {                // PRINT NEAREST ARRAY
			cout << nearest[m] << "\t";
		}
		cout << endl;
	}

	cout << endl << "The Cost of the Minimum Spanning Tree is:" << mincost << endl;
}
