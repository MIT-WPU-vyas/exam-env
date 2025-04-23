#include <iostream>
#include <climits>

using namespace std;

// Maximum number of cities
#define MAX_N 15

// Function to find minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to find the TSP solution
void solveTSP(int n, int graph[MAX_N][MAX_N]) {
    // dp[i][j] represents the shortest path visiting all vertices in set i and ending at vertex j
    int dp[1 << MAX_N][MAX_N];
    
    // path[i][j] stores the previous city in the path to get to city j with set i
    int path[1 << MAX_N][MAX_N];
    
    // Initialize dp array
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INT_MAX;
            path[i][j] = -1;
        }
    }
    
    // Base case: path starting from city 0
    dp[1][0] = 0;  // 1 represents set with only the 0th city

    // Iterate over all possible subsets of cities
    for (int mask = 1; mask < (1 << n); mask++) {
        cout << "\n------ Processing subset mask: " << mask << " ------\n";
        
        // Skip if the start city (0) is not in the subset
        if (!(mask & 1)) continue;
        
        // Try to go from city i to city j
        for (int i = 0; i < n; i++) {
            // Skip if city i is not in current subset
            if (!(mask & (1 << i))) continue;
            
            // prev_mask is the subset without city i
            int prev_mask = mask & ~(1 << i);
            
            // Skip if it's the start and not all cities have been visited
            if (i == 0 && mask != (1 << n) - 1) continue;
            
            for (int j = 0; j < n; j++) {
                // Skip if city j is not in the previous subset or cities i and j are the same
                if (!(prev_mask & (1 << j)) || i == j) continue;
                
                // If we can improve the path
                if (dp[prev_mask][j] != INT_MAX && graph[j][i] != INT_MAX) {
                    int new_cost = dp[prev_mask][j] + graph[j][i];
                    if (new_cost < dp[mask][i]) {
                        dp[mask][i] = new_cost;
                        path[mask][i] = j;
                        cout << "Updated dp[" << mask << "][" << i << "] = " << dp[mask][i] 
                             << " (coming from city " << j << ")\n";
                    }
                }
            }
        }
    }
    
    // Find the shortest tour
    int final_mask = (1 << n) - 1;
    int min_cost = INT_MAX;
    int last_city = -1;
    
    // Check for path from the last city back to city 0
    for (int i = 1; i < n; i++) {
        if (dp[final_mask][i] != INT_MAX && graph[i][0] != INT_MAX) {
            int cost = dp[final_mask][i] + graph[i][0];
            if (cost < min_cost) {
                min_cost = cost;
                last_city = i;
            }
        }
    }
    
    if (min_cost == INT_MAX) {
        cout << "\nNo solution exists!" << endl;
        return;
    }
    
    // Reconstruct the path
    cout << "\n------ Final Solution ------\n";
    cout << "Total cost: " << min_cost << endl;
    cout << "Path: ";
    
    // Start with the last city before returning to city 0
    int curr_mask = final_mask;
    int curr_city = last_city;
    int path_length = 0;
    int path_order[MAX_N];
    
    while (curr_city != -1) {
        path_order[path_length++] = curr_city;
        int next_city = path[curr_mask][curr_city];
        curr_mask &= ~(1 << curr_city);
        curr_city = next_city;
    }
    
    // Print the path in reverse (correct order)
    cout << "0 -> ";
    for (int i = path_length - 1; i >= 0; i--) {
        cout << path_order[i];
        if (i > 0) cout << " -> ";
    }
    cout << " -> 0" << endl;
}

int main() {
    // Sample problem with 4 cities
    int n = 4;
    int graph[MAX_N][MAX_N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    cout << "Solving TSP for " << n << " cities...\n";
    cout << "Distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }
    
    solveTSP(n, graph);
    
    return 0;
}
