# Virtual Memory Management System Simulation

This project is a simulation of a virtual memory management system that implements four TLB (Translation Lookaside Buffer) replacement algorithms: FIFO (First-In-First-Out), LIFO (Last-In-First-Out), LRU (Least Recently Used), and Optimal Algorithm. The simulation demonstrates how these algorithms behave with different memory access patterns, and provides the number of TLB hits for each algorithm.

## Table of Contents
1. [Project Overview](#project-overview)
2. [TLB Replacement Algorithms](#tlb-replacement-algorithms)
3. [Input Format](#input-format)
4. [Output Format](#output-format)
5. [Compiling and Running the Code](#compiling-and-running-the-code)


## Project Overview

The simulation divides the address space into fixed-size pages and uses a TLB to map virtual addresses to physical addresses. The address space, page size, and TLB size are predefined for each test case. The goal is to evaluate how different TLB replacement algorithms behave when managing memory accesses.

### TLB Replacement Algorithms

1. **FIFO (First-In-First-Out)**: The oldest entry in the TLB is replaced when the TLB is full.
2. **LIFO (Last-In-First-Out)**: The most recent entry in the TLB is replaced.
3. **LRU (Least Recently Used)**: The least recently used entry in the TLB is replaced.
4. **Optimal Algorithm**: The entry that will not be used for the longest time in the future is replaced.

## Input Format

The input consists of multiple test cases. The format is as follows:

1. The first line contains an integer `T` (1 ≤ T ≤ 100), representing the number of test cases.
2. For each test case:
   - `S` (1 ≤ S ≤ 4096): Address space size in megabytes (MB).
   - `P` (1 ≤ P ≤ S): Page size in kilobytes (KB).
   - `K` (1 ≤ K ≤ 1024): TLB size, i.e., number of entries in the TLB.
   - `N` (1 ≤ N ≤ 10^6): Number of memory accesses.
   - `N` subsequent lines, each containing a memory address in hexadecimal format. Each address is a valid 32-bit hexadecimal number without any prefix (e.g., `1A2B3C4D`).

## Output Format

For each test case, output a single line containing four space-separated integers representing the number of TLB hits for each replacement algorithm in the following order:
1. FIFO TLB Hits
2. LIFO TLB Hits
3. LRU TLB Hits
4. Optimal TLB Hits

## Compiling and Running the Code

### Requirements

- C++ compiler (e.g., `g++`)

### Compilation

To compile the code, run:
```bash
g++ -o tlb_simulation tlb_simulation.cpp


