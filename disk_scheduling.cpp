#include <bits/stdc++.h>
using namespace std;

void fcfs(vector<int> v, int head) {
    int seek_time = 0;
    for (auto i : v) {
        seek_time += abs(head - i);
        head = i;
    }
    cout << "FCFS Total Seek Time: " << seek_time << "\n";
}

void sstf(vector<int> v, int head) {
    int n = v.size();
    vector<int> visited(n, false);
    int seek_time = 0;

    for (int i = 0; i < n; i++) {
        int mini = INT_MAX;
        int ind = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(head - v[j]) < mini) {
                mini = abs(head - v[j]);
                ind = j;
            }
        }
        seek_time += mini;
        head = v[ind];
        visited[ind] = true;
    }
    cout << "SSTF Total Seek Time: " << seek_time << "\n";
}

void scan(vector<int> v, int head, string direction, int disk_size) {
    int seek_time = 0;
    vector<int> left, right;

    if (direction == "left") left.push_back(0);
    else right.push_back(disk_size - 1);

    for (auto i : v) {
        if (i < head) left.push_back(i);
        else right.push_back(i);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (direction == "left") {
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_time += abs(head - left[i]);
            head = left[i];
        }
        for (int i = 0; i < right.size(); i++) {
            seek_time += abs(head - right[i]);
            head = right[i];
        }
    } else {
        for (int i = 0; i < right.size(); i++) {
            seek_time += abs(head - right[i]);
            head = right[i];
        }
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_time += abs(head - left[i]);
            head = left[i];
        }
    }
    cout << "SCAN Total Seek Time: " << seek_time << "\n";
}

void cscan(vector<int> v, int head, int disk_size) {
    vector<int> left, right;
    int seek_time = 0;

    left.push_back(0);
    right.push_back(disk_size - 1);

    for (int i : v) {
        if (i < head) left.push_back(i);
        else right.push_back(i);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int i = 0; i < right.size(); i++) {
        seek_time += abs(head - right[i]);
        head = right[i];
    }

    seek_time += abs(head - 0);
    head = 0;

    for (int i = 0; i < left.size(); i++) {
        seek_time += abs(head - left[i]);
        head = left[i];
    }

    cout << "C-SCAN Total Seek Time: " << seek_time << "\n";
}

int main() {
    int n, disk_size, head, choice;
    string dir;
    vector<int> requests;

    cout << "Enter the number of disk requests: ";
    cin >> n;

    requests.resize(n);
    cout << "Enter the disk request sequence:\n";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter the disk size: ";
    cin >> disk_size;

    cout << "Enter the initial head position: ";
    cin >> head;

    do {
        cout << "\n==== Disk Scheduling Menu ====\n";
        cout << "1. FCFS\n";
        cout << "2. SSTF\n";
        cout << "3. SCAN\n";
        cout << "4. C-SCAN\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                fcfs(requests, head);
                break;
            case 2:
                sstf(requests, head);
                break;
            case 3:
                cout << "Enter the direction (left/right): ";
                cin >> dir;
                scan(requests, head, dir, disk_size);
                break;
            case 4:
                cscan(requests, head, disk_size);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
