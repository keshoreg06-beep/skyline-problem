# Skyline Problem — Algorithm Comparison

A C implementation comparing two approaches to solve the **Skyline Problem**:
- **Max-Heap** approach
- **Divide & Conquer** approach

## Problem Statement
Given a list of buildings with left, right, and height values, compute the skyline outline formed by these buildings.

## Algorithms
| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Max-Heap | O(n² log n) | O(n) |
| Divide & Conquer | O(n log n) | O(n) |

## How to Run

### Compile
```bash
gcc skyline.c -o skyline
```

### Execute
```bash
./skyline
```

### Input
Enter number of buildings when prompted:
```
Enter number of buildings (try 10000 or more): 10000
```

### Sample Output
```
Average Execution Time (Max-Heap): 0.023140 seconds
Average Execution Time (Divide & Conquer): 0.004821 seconds
```

## Project Structure
```
skyline-problem/
├── skyline.c        # Main source file
├── README.md        # Project documentation
├── .gitignore       # Git ignore file
└── report.md        # Analysis report
```

## Key Features
- Randomly generates buildings for testing
- Repeats each algorithm 50 times for accurate timing
- Compares average execution time of both approaches

## Conclusion
Divide & Conquer is significantly faster than Max-Heap for large inputs due to better time complexity.
