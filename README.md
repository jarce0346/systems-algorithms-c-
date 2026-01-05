# systems-algorithms-c++


<h2>Overview</h2>

    This repository contains selected systems-oriented algorithm implementations written in C++ as part of advanced undergraduate coursework.
    The focus is on correctness, deterministic performance, and low-level control, with all core data structures implemented manually under restricted standard library usage.

    These projects were curated to demonstrate systems-level problem solving relevant to simulation, control software, and performance-critical environments.

<h1>Projects</h1>
<h2>1. Maze Solver using Dijkstra’s Algorithm</h2>


<h3>Description</h3>

    Implements a shortest-path solver for grid-based mazes using Dijkstra’s algorithm. The maze is modeled as a graph where nodes represent cells and edges represent valid movements. Some mazes include teleportation portals, modeled as additional graph edges between matching portal identifiers.

<h3>Key Features</h3>

   * Custom graph representation

   * Custom min-heap / priority queue (no STL containers)

   * Support for teleportation portals

   * Deterministic shortest-path computation

   * Extensive deterministic and randomized testing

<h3>Algorithm</h3>

   * Dijkstra’s shortest-path algorithm

   * Time complexity: O((V+E)logV)

<h3>Testing</h3>

   * Dozens of fixed test cases covering edge cases and large mazes

   * Randomized test generation to prevent hard-coded solutions

<h2>2. Maximum Flow using Edmonds–Karp</h2>

<h3>Description</h3>

    Implements the Edmonds–Karp maximum flow algorithm on a directed graph with capacity constraints. The project models constrained resource routing problems using residual graphs and BFS-based augmenting paths.

<h3>Key Features</h3>

   * Custom directed graph implementation

   * Explicit residual graph handling

   * BFS-based augmenting path discovery

   * Deterministic flow updates and correctness checks

<h3>Algorithm</h3>

   * Edmonds–Karp (Ford–Fulkerson variant)

   * Time complexity: O(V · E²)


<h2>Design Constraints</h2>

   * STL containers were not permitted

   * All data structures (graphs, queues, heaps) were implemented from scratch

   * Only minimal standard library features were used (e.g., namespaces, swap)

   * Emphasis on correctness, clarity, and predictable execution behavior