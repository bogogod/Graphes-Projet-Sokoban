#ifndef SOLVER_BRUTEFORCE_H
#define SOLVER_BRUTEFORCE_H

#include <vector>
#include "../Maze.h"

class SolverBruteForce
{
public:
    // Méthode statique ou d'instance, ici statique car pas d'état interne au solveur
    static std::vector<char> solve(const Maze& startNode, int maxLen);
};

#endif