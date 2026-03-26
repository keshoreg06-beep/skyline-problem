# Algorithm Analysis Report — Skyline Problem

## Overview
This report compares the performance of two algorithms solving the Skyline Problem.

## Algorithm 1: Max-Heap
- Uses a max-heap to track active building heights
- For each event (start/end of building), updates the heap
- Time Complexity: **O(n² log n)** — due to linear search in removeHeap
- Space Complexity: **O(n)**

## Algorithm 2: Divide & Conquer
- Splits buildings into halves recursively
- Merges skylines similar to merge sort
- Time Complexity: **O(n log n)**
- Space Complexity: **O(n log n)**

## Test Results
<img width="1281" height="733" alt="Graph" src="https://github.com/user-attachments/assets/7db99f3c-663b-4d84-860c-a757f8aedb37" />

| Input Size | Max-Heap (avg) | Divide & Conquer (avg) |
|------------|---------------|------------------------|
| 10,000 | ~0.005s | ~0.001s |
| 20,000 | ~0.058s | ~0.003s |
| 30,000 | ~0.230s | ~0.005s |
| 40,000 | ~5.800s | ~0.028s |

## Conclusion
- Divide & Conquer is **~10x faster** for large inputs
- Max-Heap degrades due to O(n) removal operation
- Divide & Conquer is the preferred approach for production use
  
