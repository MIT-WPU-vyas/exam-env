/*
============================================================================
Name        : pbl6.cpp
Author      : Om
Subject     : Project Based Learning
Description : Dynamic Programming (0/1 Knapsack)
============================================================================
*/

#include <iostream>

using namespace std;

void knapSack(int, int[], int[], int);
int max(int,int);

int main()
{
    cout << "Enter the number of items in a Knapsack:";
    int n, W;
    cin >> n;
    int val[n], wt[n];
    for (int i = 0; i < n; i++)
    {
        cout << endl << "Enter Value for item " << i + 1 << ":";
        cin >> val[i];
        cout << "Enter Weight for item " << i + 1<< ":";
        cin >> wt[i];
    }

    cout << endl << "Enter the capacity of knapsack:";
    cin >> W;
    knapSack(W, wt, val, n);

    return 0;
}

int max(int a, int b) {
	if(a > b) {
		return a;
	}
	return b;
}

void knapSack(int W, int wt[], int val[], int n) {
    int K[n+1][W+1];

    for(int k = 0; k <= W; k++) {
    	K[0][k] = 0;
    }

    for(int k = 0; k <= n; k++) {
    	K[k][0] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= W; w++)
        {
        	if (wt[i-1] <= w) {
				K[i][w] = max(val[i-1] + K[i-1][w - wt[i-1]], K[i-1][w]);
        	}
        	else {
        		K[i][w] = K[i-1][w];
        	}
        }
    }

    int i = n, j = W;
    while (i > 0 and j > 0) {
    	if(K[i][j] != K[i-1][j]) {
    		cout << "Element " << i << " included" << endl;
    		j -= wt[i-1];
    		i--;
    	}
    	else {
    		i--;
    	}
    }

    cout << endl << "Maximum Profit: " <<  K[n][W];
}
