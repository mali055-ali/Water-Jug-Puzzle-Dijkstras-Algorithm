# Water Jug Puzzle Solver (Graph Search with Dijkstra's Algorithm)

A C++ program that solves the classic water jug puzzle — famously seen in
*Die Hard 3* — by modeling every possible jug state as a graph and finding
the cheapest sequence of moves with Dijkstra's algorithm.

## Project Description

Given two jugs of known capacity and a target amount of water to measure
out, this program figures out the minimum-cost sequence of fill/empty/pour
actions needed to reach that target. Every possible combination of water
levels in the two jugs is treated as a node in a graph, and the six
possible actions (fill A, fill B, empty A, empty B, pour A→B, pour B→A)
become weighted edges between those nodes. Dijkstra's algorithm then finds
the cheapest path from the empty-empty starting state to any state where
the target jug holds the desired amount — supporting custom (and even
asymmetric) costs for each action.

## Features

- **State-space graph construction** — every reachable `(a, b)` water
  level combination is numbered and pre-computed with its six outgoing
  transitions (`buildGraph()`)
- **Configurable action costs** — fill, empty, and pour actions can each
  have independent costs, and pouring A→B can cost differently than
  pouring B→A
- **Dijkstra's shortest-path search** — a priority-queue-based
  implementation finds the minimum total cost to reach a state where the
  target jug holds the required amount
- **Full solution reconstruction** — traces back through the shortest-path
  tree to reproduce the exact sequence of actions (e.g. "fill A", "pour A
  B") that reaches the goal, along with the total cost
- **Input validation** — invalid capacities, targets, or costs are
  rejected before the search begins
- **Reference starter material included** — `getting_started.cpp` (course-
  provided, not authored as part of this solution) walks through how to
  number states and begin a Dijkstra implementation

## Technologies Used

- **Language:** C++
- **Libraries:** C++ Standard Library (`<queue>` for the priority queue,
  `<vector>`, `<limits>`, `<stdexcept>`)
- **Algorithm:** Dijkstra's shortest-path algorithm over an explicit
  state-space graph

## Files

| File | Description |
|------|-------------|
| `Jug.h` / `Jug.cpp` | `Jug` class: state graph construction and Dijkstra-based solver |
| `main.cpp` | Runs sample test cases (e.g. the classic 3/5-gallon "Die Hard" scenario) |
| `getting_started.cpp` | Course-provided reference code demonstrating graph construction and Dijkstra basics (not part of the final solution) |
| `README` | Original assignment note pointing to the getting-started reference |

## How It Works

1. `buildGraph()` enumerates every possible `(a, b)` water level pair for
   the two jug capacities and precomputes where each of the six actions
   leads.
2. `solve()` runs Dijkstra's algorithm from the empty-empty start state,
   using a min-priority-queue ordered by total cost so far.
3. As each state is popped, its six neighboring states are relaxed (cost
   updated) if a cheaper path to them is found.
4. Once a state with the target amount in jug B is reached, the algorithm
   reconstructs the path of actions taken by walking backward through the
   `previous` pointers, reverses it, and returns it as a solution string
   along with the total cost.

## Build & Run

```bash
g++ -o jug_solver main.cpp Jug.cpp
./jug_solver
```

Example scenario (classic *Die Hard* 3/5-gallon jugs, target 4 gallons,
each action costing 1):

```
Jug head1(3, 5, 4, 1, 1, 1, 1, 1, 1);
```

produces the step-by-step sequence of fills, empties, and pours needed to
measure out exactly 4 gallons, followed by the total cost.
