#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

int totalPages, frameCount;

// Check if page is already in frame (hit)
bool isPageInFrame( vector<int>& frames, int page) {
    for (int f : frames) {
        if (f == page) return true;
    }
    return false;
}

void simulateFCFS( vector<int>& pageSequence) {
    cout << "\n--- First Come First Serve (FCFS) Page Replacement ---\n";
    vector<int> frames(frameCount, -1);
    int pointer = 0;
    int pageFaults = 0;

    for (int page : pageSequence) {
        if (!isPageInFrame(frames, page)) {
            frames[pointer] = page;
            pointer = (pointer + 1) % frameCount;
            pageFaults++;
        }

        cout << "Page " << page << ": ";
        for (int frame : frames) {
            cout << (frame == -1 ? "- " : to_string(frame) + " ");
        }
        cout << "\n";
    }

    int pageHits = totalPages - pageFaults;
    cout << "Total Page Faults: " << pageFaults << "\n";
    cout << "Total Page Hits: " << pageHits << "\n";
    cout << fixed << setprecision(2);
    cout << "Hit Ratio: " << (static_cast<float>(pageHits) / totalPages) * 100 << "%\n";
}

void simulateLRU(const vector<int>& pageSequence) {
    cout << "\n--- Least Recently Used (LRU) Page Replacement ---\n";
    vector<int> frames(frameCount, -1);
    vector<int> lastUsed(frameCount, 0);
    int currentTime = 0;
    int pageFaults = 0;

    for (int pageIndex = 0; pageIndex < totalPages; ++pageIndex) {
        int page = pageSequence[pageIndex];
        currentTime++;
        bool hit = false;

        for (int i = 0; i < frameCount; ++i) {
            if (frames[i] == page) {
                lastUsed[i] = currentTime;
                hit = true;
                break;
            }
        }

        if (!hit) {
            pageFaults++;
            int lruIndex = -1, minTime = numeric_limits<int>::max();
            for (int i = 0; i < frameCount; ++i) {
                if (frames[i] == -1) {
                    lruIndex = i;
                    break;
                }
                if (lastUsed[i] < minTime) {
                    minTime = lastUsed[i];
                    lruIndex = i;
                }
            }
            frames[lruIndex] = page;
            lastUsed[lruIndex] = currentTime;
        }

        cout << "Page " << page << ": ";
        for (int frame : frames) {
            cout << (frame == -1 ? "- " : to_string(frame) + " ");
        }
        cout << "\n";
    }

    int pageHits = totalPages - pageFaults;
    cout << "Total Page Faults: " << pageFaults << "\n";
    cout << "Total Page Hits: " << pageHits << "\n";
    cout << fixed << setprecision(2);
    cout << "Hit Ratio: " << (static_cast<float>(pageHits) / totalPages) * 100 << "%\n";
}

int getOptimalReplacementIndex(const vector<int>& pageSequence, const vector<int>& frames, int currentIndex) {
    int farthest = -1;
    int indexToReplace = -1;

    for (int i = 0; i < frameCount; ++i) {
        int nextUse = -1;
        for (int j = currentIndex; j < totalPages; ++j) {
            if (pageSequence[j] == frames[i]) {
                nextUse = j;
                break;
            }
        }
        if (nextUse == -1) return i;
        if (nextUse > farthest) {
            farthest = nextUse;
            indexToReplace = i;
        }
    }
    return indexToReplace;
}

void simulateOptimal(const vector<int>& pageSequence) {
    cout << "\n--- Optimal Page Replacement ---\n";
    vector<int> frames(frameCount, -1);
    int pageFaults = 0;

    for (int currentIndex = 0; currentIndex < totalPages; ++currentIndex) {
        int page = pageSequence[currentIndex];

        if (!isPageInFrame(frames, page)) {
            pageFaults++;
            bool inserted = false;

            for (int i = 0; i < frameCount; ++i) {
                if (frames[i] == -1) {
                    frames[i] = page;
                    inserted = true;
                    break;
                }
            }

            if (!inserted) {
                int replaceIndex = getOptimalReplacementIndex(pageSequence, frames, currentIndex + 1);
                frames[replaceIndex] = page;
            }
        }

        cout << "Page " << page << ": ";
        for (int frame : frames) {
            cout << (frame == -1 ? "- " : to_string(frame) + " ");
        }
        cout << "\n";
    }

    int pageHits = totalPages - pageFaults;
    cout << "Total Page Faults: " << pageFaults << "\n";
    cout << "Total Page Hits: " << pageHits << "\n";
    cout << fixed << setprecision(2);
    cout << "Hit Ratio: " << (static_cast<float>(pageHits) / totalPages) * 100 << "%\n";
}

int main() {
    vector<int> pageSequence;
    int choice;

    cout << "Enter the number of pages: ";
    cin >> totalPages;

    cout << "Enter the page reference string:\n";
    pageSequence.resize(totalPages);
    for (int i = 0; i < totalPages; ++i)
        cin >> pageSequence[i];

    cout << "Enter the number of frames: ";
    cin >> frameCount;

    do {
        cout << "\nChoose Page Replacement Algorithm:\n";
        cout << "1. FCFS\n2. LRU\n3. Optimal\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                simulateFCFS(pageSequence);
                break;
            case 2:
                simulateLRU(pageSequence);
                break;
            case 3:
                simulateOptimal(pageSequence);
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
