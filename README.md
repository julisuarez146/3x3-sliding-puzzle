# 3x3-sliding-puzzle
Sliding Puzzle solver using A* algorithm 

📘 Overview
In this assignment, you'll implement a Sliding Puzzle solver (commonly known as the 8-puzzle or 15-puzzle) using the A* algorithm. This project will give you hands-on experience with heuristic functions and search-based problem solving. You will begin by implementing Manhattan Distance as your heuristic and then brainstorm and implement a second heuristic that improves performance or quality of the search.

🎯 Learning Objectives
Understand and implement the A* algorithm.

Analyze and compare heuristic functions in a search-based context.

Apply data structures like priority queues, sets/maps, and coordinate-based grids.

Write clean, modular, and well-documented code.

🧠 Background: What is A*?
A* (A-Star) is a pathfinding algorithm that combines the best aspects of Dijkstra's algorithm and Greedy Best-First Search. It finds the shortest path from a start state to a goal state using a combination of:

g(n): the exact cost from the start node to the current node n

h(n): a heuristic that estimates the cost from node n to the goal

The algorithm uses f(n) = g(n) + h(n) to prioritize which node to explore next.

📏 Part 1: Basic Solver with Manhattan Distance
Implement the A* algorithm to solve a 3x3 or 4x4 sliding puzzle.

Use Manhattan Distance as your first heuristic function:

For each tile, calculate the number of rows and columns it is away from its goal position.

Sum these distances across all tiles (ignore the blank space).

Track and output:

Number of states explored

Final move count

🚀 Part 2: Invent a Better Heuristic
Once your Manhattan Distance version works:

Come up with a custom heuristic. Some ideas:

Linear Conflict: Add penalties if two tiles are in the same row/column and reversed.

Pattern Databases: Precompute and cache subgoals.

Misplaced Tiles (simpler alternative for brainstorming).

Implement the new heuristic and run comparisons:

Total moves

Nodes explored

Any improvement in performance or correctness?

Reflect on whether your heuristic is admissible (never overestimates the true cost).

📽️ Deliverables
✅ Code Repository

Include full implementation in C++

Document your aStar() function and heuristic function(s)

Make sure it builds and runs cleanly

✅ Demo Video (3–5 minutes)

Show your solver solving at least two puzzles (one easy, one hard)

Talk through your approach and show your custom heuristic in action

✅ Reflection Document (PDF or Markdown)
Answer the following:

What challenges did you face implementing A*?

How did you come up with your second heuristic?

Was it admissible? How did it compare to Manhattan Distance?

If you had more time, what would you optimize further?

🧪 Hints
Represent your board as a 2D array or 1D vector.

Store the empty tile position and valid neighbor swaps.

Use a std::priority_queue with a custom comparator for f(n).

Use std::unordered_set to track visited board states (you may need to define a hash function).
