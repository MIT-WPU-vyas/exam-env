#include <iostream>

using namespace std;

int knapsack(int profits[], int weights[], int capacity, int n) {
    int B[n + 1][capacity + 1];
    for (int w = 0;w<=capacity;w++) { 
        B[0][w] = 0;
        }
    for(int i = 0;i<=n;i++) { 
        B[i][0] = 0;
        }

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                B[i][w] = max(profits[i-1] + B[i - 1][w - weights[i-1]], B[i - 1][w]);
            } 
            else {
                B[i][w] = B[i - 1][w];
            }
        }
    }

    int i = n, k = capacity;
    cout << "Index of Items included: ";
    while (i > 0 && k > 0) {
        if (B[i][k] != B[i - 1][k]) {
            cout << (i - 1) << " ";
            k -= weights[i - 1];
        }
        i--;
    }
    cout << endl;

    // maximum profit
    return B[n][capacity];
}

int main() {
    int profits[] = {2,4,7,10};
    int weights[] = {1,3,5,7};
    int capacity = 8;
    int n = sizeof(profits) / sizeof(profits[0]);

    int max_profit = knapsack(profits, weights, capacity, n);
    cout << "Maximum Profit: " << max_profit << endl;

    return 0;
}
