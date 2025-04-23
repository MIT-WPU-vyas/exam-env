#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    struct Job {
        int start, end, profit;
        Job() {} 
        Job(int s, int e, int p) : start(s), end(e), profit(p) {}
    };

    static bool compare(Job a, Job b) {
        return a.end < b.end;
    }

    int findLastNonOverlapping(Job jobs[], int index) {
        for (int i = index - 1; i >= 0; i--) {
            if (jobs[i].end <= jobs[index].start) {
                return i;
            }
        }
        return -1;
    }

    int findMaxProfit(Job jobs[], int index) {
        if (index < 0) return 0; 

        int lastJob = findLastNonOverlapping(jobs, index);
        int take = jobs[index].profit + findMaxProfit(jobs, lastJob);
        int skip = findMaxProfit(jobs, index - 1);
        return max(take, skip);
    }

    int jobScheduling(int startTime[], int endTime[], int profit[], int n) {
        Job jobs[n];

        for (int i = 0; i < n; i++) {
            jobs[i] = Job(startTime[i], endTime[i], profit[i]); 
        }

        sort(jobs, jobs + n, compare);
        return findMaxProfit(jobs, n - 1);
    }
};

int main() {
    Solution sol;
    
    int startTime[] = {1,1,1};
    int endTime[] = {2,3,4};
    int profit[] = {5,6,4};
    int n = sizeof(startTime) / sizeof(startTime[0]);

    cout << "Maximum Profit: " << sol.jobScheduling(startTime, endTime, profit, n) << endl;

    return 0;
}
