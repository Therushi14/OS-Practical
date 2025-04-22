#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &alloc, vector<vector<int>> &max, vector<int> &avail, int n, int m) {
    vector<vector<int>> need(n, vector<int>(m));
    vector<bool> finish(n, false);
    vector<int> work = avail;
    vector<int> safeSeq;

    // Step 1: Calculate Need matrix
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Step 2: Find a process that can be safely executed
    while (safeSeq.size() < n) {
        bool allocated = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    finish[i] = true;
                    safeSeq.push_back(i);
                    allocated = true;
                }
            }
        }
        if (!allocated) break;
    }

    if (safeSeq.size() == n) {
        cout << "System is in a safe state.\nSafe Sequence: ";
        for (int i : safeSeq)
            cout << "P" << i << " ";
        cout << endl;
        return true;
    } else {
        cout << "System is in an unsafe state (deadlock may occur)." << endl;
        return false;
    }
}

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> avail(m);

    cout << "Enter allocation matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter maximum matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "Enter available resources:\n";
    for (int i = 0; i < m; i++)
        cin >> avail[i];

    isSafe(alloc, max, avail, n, m);

    return 0;
}
