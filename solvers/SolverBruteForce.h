#ifndef SOLVER_BRUTEFORCE_H
#define SOLVER_BRUTEFORCE_H

#include <vector>
#include "../Maze.h"

class SolverBruteForce
{
public:
    static std::vector<char> solve(const Maze& startNode, int maxLen);
};

#endif