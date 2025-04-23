/*
============================================================================
Name        : pbl7.cpp
Author      : Om
Subject     : Project Based Learning
Description : N-Queen Problem
============================================================================
*/
#include <iostream>
#include <cstdlib>
using namespace std;

class NQueens {
    int* x;
    int n;
    int count;

public:
    void solve(int size);
    void Nqueens(int k);
    bool place(int k, int i);
    void display();
    ~NQueens();
};


int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    NQueens q;
    q.solve(n);

    return 0;
}

void NQueens::solve(int size) {
    n = size;
    count = 1;
    x = new int[n + 1];
    Nqueens(1);
}


void NQueens::Nqueens(int k) {
    for (int i = 1; i <= n; i++) {
        if (place(k, i)) {
            x[k] = i;
            if (k == n)
                display();
            else
                Nqueens(k + 1);
        }
    }
}

bool NQueens::place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
            return false;
    }
    return true;
}

void NQueens::display() {
    cout << "\nSolution " << count++ << ":\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i] == j)
                cout << " Q ";
            else
                cout << " - ";
        }
        cout << "\n";
    }
}

NQueens::~NQueens() {
    delete[] x;
}
