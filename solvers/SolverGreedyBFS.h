#ifndef SOLVER_GREEDYBFS_H
#define SOLVER_GREEDYBFS_H

#include <vector>
#include <string>
#include <set>
#include "../Maze.h"

// Simple solver based on Greedy Best-First Search (greedy BFS).
// It always expands the state with the smallest heuristic value.
class SolverGreedyBFS
{
public:
    // Returns a sequence of moves (TOP/BOTTOM/LEFT/RIGHT) or an empty vector on failure.
    static std::vector<char> solve(const Maze& startNode);

private:
    // Builds a simple signature of the state (player + boxes) to avoid cycles.
    static std::string getSignature(const Maze& m);
};

#endif
