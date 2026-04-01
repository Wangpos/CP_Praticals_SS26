# Algorithm Implementations Report

## Overview

This practical implements three fundamental graph algorithms: **Floyd-Warshall**, **Johnson's**, and **Boruvka's** algorithms. These are cornerstone algorithms in computer science used for solving shortest path and minimum spanning tree problems.

---

## 1. Floyd-Warshall Algorithm

### Algorithm Description

Floyd-Warshall is an **All-Pairs Shortest Path (APSP)** algorithm that finds the shortest distance between every pair of vertices in a weighted directed graph.

### Key Characteristics

- **Time Complexity**: O(V³) - where V is the number of vertices
- **Space Complexity**: O(V²) - for the distance matrix
- **Best For**: Dense graphs, small-to-medium sized graphs
- **Handles**: Both positive and negative edge weights (but not negative cycles)

### Algorithm Logic

1. Initialize distance matrix with edge weights (∞ for non-existent edges, 0 for self-loops)
2. For each intermediate vertex k from 0 to V-1:
   - For each source vertex i:
     - For each destination vertex j:
       - If path through k is shorter than current distance: `dist[i][j] = dist[i][k] + dist[k][j]`
3. After all iterations, dist[i][j] contains the shortest path from i to j

### Key Implementation Details

```cpp
for (int k = 0; k < V; k++) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][k] + dist[k][j] < dist[i][j]) {
                dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}
```

### Advantages

✓ Simple to understand and implement
✓ Easily detects negative cycles (negative values on diagonal)
✓ Constructs complete shortest path matrix in one algorithm
✓ Path reconstruction is straightforward

### Disadvantages

✗ O(V³) time complexity is impractical for large graphs
✗ Uses O(V²) space even if graph is sparse
✗ Cannot handle negative cycles

### Use Cases

- Finding shortest routes between all city pairs
- Network analysis with small graphs
- Robot path planning
- Game AI pathfinding for limited environments

---

## 2. Johnson's Algorithm

### Algorithm Description

Johnson's Algorithm is an **All-Pairs Shortest Path (APSP)** algorithm that works efficiently on sparse graphs. It combines **Bellman-Ford** and **Dijkstra** algorithms intelligently.

### Key Characteristics

- **Time Complexity**: O(VE + V² log V) with binary heap Dijkstra
- **Space Complexity**: O(V²) for results
- **Best For**: Sparse graphs with non-negative or negative edges
- **Handles**: Negative edge weights (but not negative cycles)

### Algorithm Logic

1. **Reweighting Phase**:
   - Add a temporary source vertex connected to all vertices with weight 0
   - Run Bellman-Ford from this source to compute h[v] = shortest path from source to v
2. **Reweighting Edges**:
   - New weight: w'(u,v) = w(u,v) + h[u] - h[v]
   - This ensures all weights become non-negative while preserving shortest paths

3. **Single-Source Shortest Paths**:
   - For each vertex u, run Dijkstra using reweighted edges
   - Convert distances back to original weights: dist[u][v] = dist'[u][v] - h[u] + h[v]

### Key Implementation Details

```cpp
// Reweighting ensures non-negative weights
int reweightedWeight = w + h[u] - h[v];

// After Dijkstra
dist[source][v] = dijkstra_result[v] - h[source] + h[v];
```

### Advantages

✓ Much faster than Floyd-Warshall on sparse graphs
✓ Uses Dijkstra's efficient algorithm multiple times
✓ Handles negative weights intelligently
✓ Better for real-world applications

### Disadvantages

✗ More complex to implement than Floyd-Warshall
✗ Higher constant factors in time complexity
✗ Still O(V²) space for result matrix
✗ Cannot handle negative cycles

### Use Cases

- Large network routing protocols
- Social network analysis
- Recommendation systems with sparse connections
- Traffic flow optimization

---

## 3. Boruvka's Algorithm

### Algorithm Description

Boruvka's Algorithm finds the **Minimum Spanning Tree (MST)** of a weighted undirected graph. It's one of the oldest known MST algorithm.

### Key Characteristics

- **Time Complexity**: O(E log V) - efficient for sparse graphs
- **Space Complexity**: O(V + E)
- **Best For**: Any graph (dense or sparse)
- **Approach**: Greedy, divide-and-conquer philosophy

### Algorithm Logic

1. Sort edges by weight
2. Maintain forest of connected components (initially each vertex is a component)
3. Repeat until MST is complete:
   - For each component, find the minimum weight edge connecting it to another component
   - Add all such edges that don't create cycles
   - Merge components

### Key Implementation Details

```cpp
// Find minimum outgoing edge for each component
for (int i = 0; i < V; i++) {
    minEdge[componentU] = min(minEdge[componentU], edge);
}

// Add edges while checking for cycles using Union-Find
while (mst.size() < V - 1) {
    if (uf.unite(u, v)) {
        mst.push_back(edge);
    }
}
```

### Advantages

✓ O(E log V) time complexity - optimal
✓ Works on any graph (disconnected, complete, sparse, dense)
✓ Parallelizable - each component can process independently
✓ Uses Union-Find for efficient cycle detection

### Disadvantages

✗ Slightly more complex than Prim's or Kruskal's
✗ Requires sorting edges
✗ Not as intuitive as other MST algorithms

### Use Cases

- Electrical network design
- Telecommunication network optimization
- Minimum cost transportation networks
- Cluster analysis in data science
- Parallel MST computation

---

## Comparative Analysis

| Feature              | Floyd-Warshall | Johnson's        | Boruvka's  |
| -------------------- | -------------- | ---------------- | ---------- |
| **Problem Type**     | APSP           | APSP             | MST        |
| **Time Complexity**  | O(V³)          | O(VE + V² log V) | O(E log V) |
| **Space**            | O(V²)          | O(V²)            | O(V + E)   |
| **Negative Weights** | Yes            | Yes              | No         |
| **Graph Type**       | Dense optimal  | Sparse optimal   | Any        |
| **Implementation**   | Simple         | Complex          | Medium     |
| **Practical Use**    | Small graphs   | Large networks   | Any graph  |

### When to Use Each:

- **Floyd-Warshall**: V ≤ 500, dense graphs, educational purposes
- **Johnson's Algorithm**: Large sparse graphs, practical applications
- **Boruvka's Algorithm**: MST needed for any graph type, parallel processing

---

## Learning Reflection

### Understanding Gained

#### 1. **Dynamic Programming vs Greedy Approaches**

- Floyd-Warshall demonstrates pure **dynamic programming** - it builds solutions from subproblems
- Boruvka's and Kruskal's show **greedy strategy** - making locally optimal choices
- Both approaches have their place in algorithm design

#### 2. **Negative Weight Handling**

- Floyd-Warshall and Johnson's handle negative weights differently:
  - Floyd-Warshall: brute force through all paths
  - Johnson's: reweighting technique preserves shortest paths while enabling Dijkstra
- This shows how problem constraints (negative weights) require algorithm adaptation

#### 3. **Time-Space Trade-offs**

- Floyd-Warshall trades cubic time for simplicity
- Johnson's adds complexity but reduces time for sparse graphs
- Boruvka's maintains optimal time but needs careful implementation

#### 4. **Union-Find as a Core Data Structure**

- Boruvka's and Kruskal's heavily rely on efficient Union-Find
- Path compression and union by rank reduce operations to nearly O(1)
- This is a critical technique for competitive programming

#### 5. **Real-World Applicability**

- **Floyd-Warshall**: Limited to small graphs; rarely used in production
- **Johnson's**: Used in real network routing protocols, social networks
- **Boruvka's**: Essential for infrastructure design, parallel computing
- Algorithm choice dramatically affects scalability

#### 6. **Testing and Edge Cases**

- Disconnected graphs: Floyd-Warshall shows INF; Boruvka's shows incomplete MST
- Negative cycles: Floyd-Warshall detects via negative diagonal
- Single vertex: Requires special handling
- These cases reveal algorithm robustness

### Key Insights

1. **No Silver Bullet**: Different algorithms excel in different scenarios
2. **Graph Representation Matters**: Adjacency matrix vs list affects algorithm efficiency
3. **Cycle Detection**: Union-Find is fundamental to many graph algorithms
4. **Mathematical Elegance**: Johnson's reweighting is mathematically clever and efficient
5. **Scalability**: For production systems with millions of nodes, algorithm choice is critical

### Practical Observations

- **Floyd-Warshall** is O(V³) but with very small constant factors - good for V < 500
- **Johnson's Algorithm** shines when E << V² (sparse graphs)
- **Boruvka's Algorithm** is rarely implemented manually; Kruskal's is often preferred for MST
- Path reconstruction (tracking actual paths) adds complexity to both SP algorithms

### Future Improvements

1. **Parallelization**: Johnson's can run Dijkstra in parallel; Boruvka's naturally parallelizable
2. **Approximate Algorithms**: For very large graphs, approximate solutions needed
3. **Dynamic Algorithms**: Handling edge weight changes efficiently
4. **Specialized Versions**:
   - DAG shortest paths (linear time possible)
   - Planar graph algorithms (subquadratic APSP possible)

---

## Code Quality Features

### Implementation Highlights

- ✓ **Path Tracking**: All algorithms track actual paths, not just distances
- ✓ **Edge Cases**: Handles disconnected components, single vertices, INF distances
- ✓ **Negative Cycle Detection**: Floyd-Warshall checks diagonal values
- ✓ **Multiple Test Cases**: Each algorithm includes 3-4 diverse test scenarios
- ✓ **Clean Output**: Formatted tables for easy result verification
- ✓ **Modular Design**: Each algorithm in separate class for reusability

### Test Cases Include

1. **Simple Graphs**: Basic connectivity, small examples
2. **Complete Graphs**: Dense connections
3. **Disconnected Graphs**: Multiple components (appropriate to algorithm)
4. **Negative Edges**: Testing algorithm capabilities
5. **Edge Weights**: Variety of weight values

---

## Compilation and Execution

```bash
# Compile individual programs
g++ -o floyd_warshall floyd_warshall.cpp
g++ -o johnsons johnsons_algorithm.cpp
g++ -o boruvka boruvakas_algorithm.cpp

# Run each program
./floyd_warshall
./johnsons
./boruvka
```

Each program includes comprehensive test cases with output showing:

- Graph structure
- Computed shortest paths/MST
- Path reconstruction
- Edge cases handling

---

## Conclusion

These three algorithms represent fundamental approaches to graph problems:

1. **Floyd-Warshall** - teaches dynamic programming and simplicity
2. **Johnson's** - demonstrates algorithmic optimization and reweighting tricks
3. **Boruvka's** - shows divide-and-conquer and efficient data structures

Understanding when and how to apply each algorithm is crucial for:

- Competitive programming success
- System design for large-scale applications
- Research and academic achievement
- Building scalable network solutions

The true mastery comes not from memorizing implementations, but from understanding the trade-offs, recognizing problem types, and selecting the appropriate tool for each challenge.

---

**Author**: CSF303 - Practical 4
**Date**: Spring 2026
**Topic**: Advanced Graph Algorithms
