
/*
 *  ****************************************************
 *  *                                                  *
 *  *        Name : Shashwat Raj                       *
 *  *        Entry Number: 2021MT10259                 *
 *  *                                                  *
 *  ****************************************************
 */

 /*
Problem Statement 1: (5 marks) (time limit per test 3 seconds)

You are required to simulate the behavior of a virtual memory management system that divides
the address space into fixed-size pages. You will implement the following TLB replacement
algorithms:
● FIFO (First-In-First-Out)
● LIFO (Last-In-First-Out)
● LRU (Least Recently Used)
● Optimal Algorithm

You will be provided with a predefined size for the address space, page size, and TLB size.
Your task is to develop a simulation that demonstrates how different algorithms behave.

Instructions: This part has to be done in C++
1. TLB Replacement Algorithms:
   ○ Implement each of the following TLB replacement algorithms:
     ■ FIFO: The oldest entry in the TLB is replaced when the TLB is full.
     ■ LIFO: The most recent entry in the TLB is replaced.
     ■ LRU: The least recently used entry in the TLB is replaced.
     ■ Optimal: Replace the entry that will not be used for the longest time in the future.

Deliverables:
● Source code of the simulation, properly commented.
● You will have to print out the number of TLB Hits in the format given below.

Example output format for TLB Hits:
TLB Hits (FIFO): <hits>
TLB Hits (LIFO): <hits>
TLB Hits (LRU): <hits>
TLB Hits (Optimal): <hits>
*/


// Micros and Macros

#include <iostream>
#include <unordered_map>
#define MAX_TLB_SIZE 1024

using namespace std;


// Struct Definitions



// Struct 1 : FIFO TLB

struct FIFOTLB {
    int tlb_size;
    unsigned long long int tlb_array[MAX_TLB_SIZE];
    unordered_map<int, bool> tlb_map;
    int front, rear, count;

    FIFOTLB(int size) : tlb_size(size), front(0), rear(0), count(0) {}

    int simulate(unsigned long long int memory_accesses[], int n) {
        int tlb_hits = 0;

        for (int i = 0; i < n; ++i) {
            unsigned long long int page = memory_accesses[i];
            if (tlb_map.count(page)) {
                tlb_hits++; // TLB hit
            } else {
                if (count == tlb_size) {
                    // Remove the oldest page (FIFO)
                    unsigned long long int oldest_page = tlb_array[front];
                    tlb_map.erase(oldest_page);
                    front = (front + 1) % tlb_size;
                    count--;
                }
                // Insert new page
                tlb_array[rear] = page;
                tlb_map[page] = true;
                rear = (rear + 1) % tlb_size;
                count++;
            }
        }
        return tlb_hits;
    }
};

// Struct 2: LIFO TLB

struct LIFOTLB {
    int tlb_size;
    unsigned long long int tlb_array[MAX_TLB_SIZE];
    unordered_map<int, bool> tlb_map;
    int top;

    LIFOTLB(int size) : tlb_size(size), top(-1) {}

    int simulate(unsigned long long int memory_accesses[], int n) {
        int tlb_hits = 0;

        for (int i = 0; i < n; ++i) {
            unsigned long long int page = memory_accesses[i];
            if (tlb_map.count(page)) {
                tlb_hits++;
            } else {
                if (top == tlb_size - 1) {
                    // Remove the most recent page (LIFO)
                    unsigned long long int recent_page = tlb_array[top];
                    tlb_map.erase(recent_page);
                    top--;
                }
                // Insert new page
                tlb_array[++top] = page;
                tlb_map[page] = true;
            }
        }
        return tlb_hits;
    }
};

// Struct 3 : LRU TLB

struct LRUTLB {
    int tlb_size;
    unsigned long long int tlb_array[MAX_TLB_SIZE];
    unordered_map<int, int> tlb_map;
    int count;

    LRUTLB(int size) : tlb_size(size), count(0) {}

    void move_to_front(int index) {
        unsigned long long int page = tlb_array[index];
        // Shift elements between index and front
        for (int i = index; i > 0; --i) {
            tlb_array[i] = tlb_array[i - 1];
            tlb_map[tlb_array[i]] = i;
        }
        // Place the page at the front
        tlb_array[0] = page;
        tlb_map[page] = 0;
    }

    int simulate(unsigned long long int memory_accesses[], int n) {
        int tlb_hits = 0;

        for (int i = 0; i < n; ++i) {
            unsigned long long int page = memory_accesses[i];
            if (tlb_map.count(page)) {
                tlb_hits++;
                move_to_front(tlb_map[page]); // Move to front
            } else {
                if (count == tlb_size) {
                    // Remove the least recently used page (last in the array)
                    unsigned long long int lru_page = tlb_array[tlb_size - 1];
                    tlb_map.erase(lru_page);
                    count--;
                }
                // Insert new page at the front
                for (int j = count; j > 0; --j) {
                    tlb_array[j] = tlb_array[j - 1];
                    tlb_map[tlb_array[j]] = j;
                }
                tlb_array[0] = page;
                tlb_map[page] = 0;
                count++;
            }
        }
        return tlb_hits;
    }
};

// Struct 4 Optimal TLB

struct OptimalTLB {
    int tlb_size;
    unsigned long long int tlb_array[MAX_TLB_SIZE];
    unordered_map<unsigned long long int, int> tlb_map;
    int count;

    OptimalTLB(int size) : tlb_size(size), count(0) {}

    void replace_page(unsigned long long int new_page, int index_to_replace) {
        if (count < tlb_size) {
            tlb_array[count] = new_page;
            tlb_map[new_page] = count;
            count++;
        } else {
            unsigned long long int old_page = tlb_array[index_to_replace];
            tlb_array[index_to_replace] = new_page;
            tlb_map.erase(old_page);
            tlb_map[new_page] = index_to_replace;
        }
    }

    int find_optimal_replacement(unsigned long long int memory_accesses[], int n, int start_index) {
        int farthest = -1;
        int replace_index = -1;

        for (int i = 0; i < count; i++) {
            unsigned long long int page = tlb_array[i];
            int j;
            for (j = start_index; j < n; j++) {
                if (memory_accesses[j] == page) {
                    if (j > farthest) {
                        farthest = j;
                        replace_index = i;
                    }
                    break;
                }
            }
            if (j == n) {
                return i; // This page is not used in the future, so replace it
            }
        }

        return (replace_index == -1) ? 0 : replace_index;
    }

    int simulate(unsigned long long int memory_accesses[], int n) {
        int tlb_hits = 0;

        for (int i = 0; i < n; ++i) {
            unsigned long long int page = memory_accesses[i];

            if (tlb_map.count(page)) {
                tlb_hits++;
            } else {
                int replace_index = (count < tlb_size) ? count : find_optimal_replacement(memory_accesses, n, i + 1);
                replace_page(page, replace_index);
            }
        }

        return tlb_hits;
    }
};



// Main Function

int main() {
    int T;
    cin >> T;
    while (T--) {
        int S, P, K, N;
        cin >> S >> P >> K >> N;

        unsigned long long int memory_accesses[N];
        for (int i = 0; i < N; ++i) {
            cin >> hex >> memory_accesses[i];
            memory_accesses[i] /= P; // Convert to page number
        }

        // Reset input stream to decimal
        cin >> dec;

        FIFOTLB fifo_tlb(K);
        LIFOTLB lifo_tlb(K);
        LRUTLB lru_tlb(K);
        OptimalTLB optimal_tlb(K);

        int fifo_hits = fifo_tlb.simulate(memory_accesses, N);
        int lifo_hits = lifo_tlb.simulate(memory_accesses, N);
        int lru_hits = lru_tlb.simulate(memory_accesses, N);
        int opt_hits = optimal_tlb.simulate(memory_accesses, N);

        cout << fifo_hits << " " << lifo_hits << " " << lru_hits << " " << opt_hits << endl;
    }
    return 0;
}
