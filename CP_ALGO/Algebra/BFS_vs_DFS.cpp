/*
=====================================================
    BFS vs DFS - Notes
=====================================================

🔹 BFS (Breadth-First Search)
--------------------------------
- Explores graph level by level (layer by layer).
- Implemented using a Queue (FIFO).
- Time Complexity: O(V + E)
- Space Complexity: O(V) (can grow large due to storing all frontier nodes).

✅ When to use BFS:
1. Shortest Path in Unweighted Graphs
   - BFS guarantees the shortest path (minimum number of edges).
   - Example: Maze solving, minimum moves in a puzzle.
2. Level-order Traversal
   - Tree/graph processing level by level.
   - Example: Printing tree levels.
3. Finding Connected Components
   - Useful for exploring all nodes in a component.
4. Situations where path length is important.

⚠️ Limitation:
- BFS may use a lot of memory in very wide graphs
  (because it stores all nodes of the current level).

--------------------------------

🔹 DFS (Depth-First Search)
--------------------------------
- Explores graph deeply along one path before backtracking.
- Implemented using Recursion or a Stack (LIFO).
- Time Complexity: O(V + E)
- Space Complexity: O(H) where H = depth of recursion (can be less than BFS).

✅ When to use DFS:
1. Path Existence
   - When you only need to know if a path exists (not the shortest one).
2. Topological Sorting
   - For Directed Acyclic Graphs (DAGs).
3. Cycle Detection
   - Useful in both directed and undirected graphs.
4. Backtracking Problems
   - N-Queens, Sudoku, permutations, subsets, etc.
5. Strongly Connected Components (SCC)
   - DFS-based algorithms like Kosaraju’s and Tarjan’s.

⚠️ Limitation:
- DFS does not guarantee the shortest path.
- Recursive DFS may hit stack overflow on very deep graphs.

--------------------------------

🔹 Quick Comparison

Feature                | BFS                        | DFS
---------------------------------------------------------------
Data Structure          | Queue (FIFO)              | Stack/Recursion (LIFO)
Path Guarantee          | Shortest path (unweighted)| Not guaranteed
Memory Usage            | High (wide frontier)      | Lower (depth only)
Best Use Case           | Distance / Shortest Path  | Exploration / Structure
Typical Applications    | Shortest path, levels     | Topological sort, SCC, backtracking

--------------------------------

🔹 Intuition
- Use BFS when DISTANCE or MINIMUM STEPS matter.
- Use DFS when STRUCTURE, CYCLES, or FEASIBILITY matter.

=====================================================
*/
