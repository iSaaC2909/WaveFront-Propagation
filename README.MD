Wavefront Propagation Search is a pathfinding algorithm that operates by assigning wave values to cells in a grid, ensuring the shortest path from the start to the goal. The method is inspired by Breadth-First Search (BFS) and works by propagating numerical distances outward from the goal in a manner similar to how waves spread in water. The algorithm guarantees an optimal path in an unweighted grid while avoiding the need for heuristics like those in A*. Mathematically, it constructs a discrete distance field over the grid and follows the steepest descent path back to the goal.

## Mathematical Representation of Wave Propagation
The wavefront is modeled as an expanding set of numbers, representing the minimum number of steps required to reach the goal. Given a 2D grid G of size W × H, where each cell G(x, y) can be a wall or a walkable path, we initialize a wave map W(x, y) such that:

W(x_g, y_g) = 0 for the goal position (x_g, y_g). The wave expands outward using the recurrence relation:

W(x, y) = min(W(x', y') + 1) for all valid neighbors (x', y') ∈ N(x, y)

where N(x, y) represents the set of valid adjacent cells (up, down, left, right). This ensures that each cell stores the shortest number of steps needed to reach the goal.

## Wavefront Expansion Algorithm
The algorithm begins at the goal and assigns it a value of 0 in the wave map. It then explores neighboring cells, increasing the wave number by 1 for each step. The expansion continues until all reachable cells in the grid are assigned values. This is implemented using a queue-based flood fill method, which ensures that each cell is processed in the order of increasing distance from the goal.

Mathematically, this follows a graph traversal model, where the grid is treated as an implicit graph G=(V,E) with cells as vertices V and edges E between adjacent non-wall cells. The traversal behaves like Dijkstra’s algorithm with a uniform edge weight of 1, ensuring that all shortest paths are correctly computed in O(N) time for N total cells in the grid.

## Path Reconstruction and Gradient Descent in Discrete Space
Once the wavefront has fully expanded, the shortest path is found by following the steepest descent of the wave map. Starting from the start position, the algorithm moves to the adjacent cell with the lowest wave number. This guarantees a path of minimal steps, since the wave values were assigned using the shortest distance from the goal. The movement follows the gradient descent principle in discrete space, where we move in the direction of the steepest decrease in W(x, y):

(x', y') = arg min (x', y') ∈ N(x, y) W(x', y')

This step-by-step movement ensures that the path taken is always optimal. The algorithm terminates once the goal (wave value = 0) is reached.

## Comparison to Other Pathfinding Methods
Unlike A*, which estimates distances using a heuristic function, Wavefront Propagation Search does not require heuristics and guarantees the shortest path by directly computing a discrete distance map. This makes it deterministic and simple to implement in maze-solving scenarios. However, it is less efficient in large open environments because it expands across the entire grid, even in directions that are irrelevant for finding the shortest path. In contrast, A* or Dijkstra’s algorithm prioritize relevant nodes, making them more efficient for large-scale applications.

## Proof of Correctness, Efficiency, and Optimality
### Proof of Correctness
To prove that the Wavefront Propagation Search correctly finds the shortest path, we consider the nature of its expansion. The algorithm initializes the goal with W(x_g, y_g) = 0 and propagates outward, ensuring that any cell W(x, y) has the minimum possible value assigned based on its neighbors. By the principle of BFS traversal, each cell is reached in the shortest number of steps, ensuring correctness.

### Efficiency Analysis
The time complexity of Wavefront Propagation Search is O(N), where N is the total number of grid cells. This is due to the breadth-first nature of the traversal, ensuring each cell is processed only once. However, its space complexity is also O(N), as it requires storing the wave map for all cells. This can become inefficient for large grids.

### Optimality
Wavefront Propagation guarantees optimality in an unweighted grid because it assigns wave values strictly based on the shortest distance from the goal. Since each expansion step increases the wave value by exactly 1, the path reconstructed by following the steepest descent is always of minimal length.

### Limitations
Despite its guarantees, Wavefront Propagation is not always the most practical choice for dynamic or large-scale environments. Algorithms like A* provide faster performance in such cases by focusing only on the most promising directions rather than uniformly expanding across the entire grid.

### Conclusion
Wavefront Propagation Search is a powerful, heuristic-free pathfinding algorithm that guarantees the shortest path in grid-based environments. While it is less efficient for large-scale applications due to its exhaustive nature, its mathematical foundation ensures correctness and optimality, making it a valuable tool for constrained pathfinding scenarios.

