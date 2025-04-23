#include <iostream>
#include <cmath> // For abs() function
using namespace std;

int x[10]; 

void display(int n) {
    cout << "\nSolution:\n";
    int k =1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i] == j) {
                cout << " Q"<<k; 
                k++;
                }
            else cout << " . ";
        }
        cout << endl;
    }
    cout << endl;
}

bool plank(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return false; 
        }
    }
    return true; 
}

void nQueen(int k, int n) {
    for (int i = 1; i <= n; i++) {
        x[k] = i; 
        if (plank(k, i)) { 
            if (k == n) { 
                display(n);
            } 
            else {
                nQueen(k + 1, n); // otherwise Recur
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;
    nQueen(1, n); 
    return 0;
}
