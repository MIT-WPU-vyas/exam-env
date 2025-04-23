#include <iostream>
#include <cmath>
using namespace std;

const int MAX_SIZE = 20; 
int x[MAX_SIZE + 1]; 
int boardSize;
int solutionCount = 0;

bool Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
            return false;
    }
    return true;
}

void printBoard(int k) {
    for (int row = 1; row <= boardSize; row++) {
        for (int col = 1; col <= boardSize; col++) {
            bool queenPlaced = false;
            for (int q = 1; q <= k; q++) {
                if (row == q && x[q] == col) {
                    cout << "Q" << q << " ";
                    queenPlaced = true;
                    break;
                }
            }
            if (!queenPlaced) {
                cout << ".  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Nqueens(int k, int n) {
    for (int i = 1; i <= n; i++) {
        cout << "Trying to place queen " << k << " at position (" << k << "," << i << ")" << endl;
        
        if (Place(k, i)) {
            x[k] = i;
            cout << "Placed queen " << k << " at position (" << k << "," << i << ")" << endl;
            cout << "Current board state:" << endl;
            printBoard(k);
            
            if (k == n) {
                solutionCount++;
                cout << "Solution #" << solutionCount << " found!" << endl;
                cout << "Queen positions: ";
                for (int j = 1; j <= n; j++) {
                    cout << "(" << j << "," << x[j] << ") ";
                }
                cout << endl << endl;
                
                cout << "Final board:" << endl;
                printBoard(n);
            } else {
                Nqueens(k + 1, n);
            }
        }
    }
}

int main() {
    cout << "Enter the size of the chess board: ";
    cin >> boardSize;
    
    if (boardSize <= 0 || boardSize > MAX_SIZE) {
        cout << "Invalid board size. Please enter a value between 1 and " << MAX_SIZE << endl;
        return 1;
    }
    
    cout << "Finding all solutions for " << boardSize << "-Queens problem..." << endl << endl;
    Nqueens(1, boardSize);
    
    cout << "Total solutions found: " << solutionCount << endl;
    
    return 0;
}


//O(N!)
