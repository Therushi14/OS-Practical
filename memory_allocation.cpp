#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void firstFit(vector<int> holes, const vector<int>& procs) {
    cout << endl;
    for (size_t i = 0; i < procs.size(); ++i) {
        bool allocated = false;
        for (size_t j = 0; j < holes.size(); ++j) {
            if (holes[j] >= procs[i]) {
                cout << "Process " << i+1
                     << " (size=" << procs[i] << ") -> "
                     << "Hole " << j+1
                     << " (was " << holes[j]
                     << ", now " << (holes[j] - procs[i]) << ")\n";
                holes[j] -= procs[i];
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            cout << "Process " << i+1
                 << " (size=" << procs[i]
                 << ") cannot be allocated.\n";
        }
    }
}

void bestFit(vector<int> holes, const vector<int>& procs) {
    cout << endl;
    for (size_t i = 0; i < procs.size(); ++i) {
        int bestIdx = -1;
        int bestSize = numeric_limits<int>::max();
        for (size_t j = 0; j < holes.size(); ++j) {
            if (holes[j] >= procs[i] && holes[j] < bestSize) {
                bestSize = holes[j];
                bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            cout << "Process " << i+1
                 << " (size=" << procs[i] << ") -> "
                 << "Hole " << bestIdx+1
                 << " (was " << holes[bestIdx]
                 << ", now " << (holes[bestIdx] - procs[i]) << ")\n";
            holes[bestIdx] -= procs[i];
        } else {
            cout << "Process " << i+1
                 << " (size=" << procs[i]
                 << ") cannot be allocated.\n";
        }
    }
}

void worstFit(vector<int> holes, const vector<int>& procs) {
    cout << endl;
    for (size_t i = 0; i < procs.size(); ++i) {
        int worstIdx = -1;
        int worstSize = -1;
        for (size_t j = 0; j < holes.size(); ++j) {
            if (holes[j] >= procs[i] && holes[j] > worstSize) {
                worstSize = holes[j];
                worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            cout << "Process " << i+1
                 << " (size=" << procs[i] << ") -> "
                 << "Hole " << worstIdx+1
                 << " (was " << holes[worstIdx]
                 << ", now " << (holes[worstIdx] - procs[i]) << ")\n";
            holes[worstIdx] -= procs[i];
        } else {
            cout << "Process " << i+1
                 << " (size=" << procs[i]
                 << ") cannot be allocated.\n";
        }
    }
}

void nextFit(vector<int> holes, const vector<int>& procs) {
    cout << endl;
    size_t start = 0;
    for (size_t i = 0; i < procs.size(); ++i) {
        bool allocated = false;
        for (size_t cnt = 0, j = start; cnt < holes.size(); ++cnt, j = (j + 1) % holes.size()) {
            if (holes[j] >= procs[i]) {
                cout << "Process " << i+1
                     << " (size=" << procs[i] << ") -> "
                     << "Hole " << j+1
                     << " (was " << holes[j]
                     << ", now " << (holes[j] - procs[i]) << ")\n";
                holes[j] -= procs[i];
                start = j;
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            cout << "Process " << i+1
                 << " (size=" << procs[i]
                 << ") cannot be allocated.\n";
        }
    }
}

int main() {
    int m, n, choice;

    cout << "Enter number of holes (max 10): ";
    cin >> m;
    if (m < 1 || m > 10) {
        cerr << "Invalid number of holes.\n";
        return EXIT_FAILURE;
    }

    cout << "Enter number of processes (max 10): ";
    cin >> n;
    if (n < 1 || n > 10) {
        cerr << "Invalid number of processes.\n";
        return EXIT_FAILURE;
    }

    vector<int> holes(m), procs(n);

    cout << "\nEnter sizes of holes:\n";
    for (int i = 0; i < m; ++i) {
        cout << " Hole[" << i+1 << "]: ";
        cin >> holes[i];
    }

    cout << "\nEnter sizes of processes:\n";
    for (int i = 0; i < n; ++i) {
        cout << " Process[" << i+1 << "]: ";
        cin >> procs[i];
    }

    do {
        cout << "\n===== Memory Allocation Menu =====\n"
             << "1. First Fit\n"
             << "2. Best Fit\n"
             << "3. Worst Fit\n"
             << "4. Next Fit\n"
             << "5. Exit\n"
             << "Select option [1-5]: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- First Fit ---\n";
                firstFit(holes, procs);
                break;
            case 2:
                cout << "\n--- Best Fit ---\n";
                bestFit(holes, procs);
                break;
            case 3:
                cout << "\n--- Worst Fit ---\n";
                worstFit(holes, procs);
                break;
            case 4:
                cout << "\n--- Next Fit ---\n";
                nextFit(holes, procs);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        if (choice >= 1 && choice <= 4)
            cout << "----------------------------------------\n";

    } while (choice != 5);

    return EXIT_SUCCESS;
}