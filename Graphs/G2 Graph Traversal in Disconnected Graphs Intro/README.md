# Graphs with Multiple Components and the Role of the Visited Array

Author: [Prakash JC](https://prakash079513.github.io)

## 1. Graphs with Multiple Components

A **connected graph** is one where there is a path between every pair of vertices. However, not all graphs are connected. If a graph is not connected, it can be split into separate **components**.

- Each component is a subgraph in which every pair of vertices is connected, but no vertex in that component is connected to any vertex outside it.
- For example, if a graph has 8 vertices and only 4 edges connecting them into two distinct groups of 4 vertices each, then the graph has **two components**.
- More generally, if a graph has 4 separate parts and none of them are connected to each other, it means the graph has **4 components**.

This is important because when we run a traversal algorithm like BFS or DFS, starting from a single node will only cover the vertices in the same component as that node. The other components will remain untouched unless we account for them.

---

## 2. Traversal and the Need for a Visited Array

When traversing a graph (using BFS or DFS), the idea is to explore nodes systematically. However, to avoid revisiting the same node multiple times, we maintain a **visited array**.

- The visited array is usually a boolean array of size `n` (number of vertices).
- `visited[i] = true` means vertex `i` has already been explored.
- This ensures:
  1. We do not fall into infinite loops in cyclic graphs.
  2. We do not process the same vertex multiple times.

In the case of a disconnected graph, a traversal starting at one vertex will stop after covering its component. The visited array will mark all vertices of that component as visited, but the remaining components will still have unvisited vertices.

---

## 3. Traversing All Components

To make sure that every vertex of the graph is visited, regardless of connectivity, we adopt the following strategy:

- Perform a traversal from the first unvisited vertex.
- Once the traversal finishes, check the visited array.
- If there are still unvisited vertices, start a new traversal from one of them.
- Repeat this process until all vertices are visited.

This way, every component is explored separately, and no vertex is left behind.

---

## 4. Summary of the Concept

- A disconnected graph can be thought of as multiple smaller connected graphs (components).
- Standard traversal algorithms (BFS, DFS) only cover one component at a time.
- A visited array keeps track of which vertices have been explored to avoid repetition.
- By looping over all vertices and starting a new traversal whenever we find an unvisited one, we ensure the entire graph is covered, including all components.

---

THE END
