#ifndef SOLVER_BFS_H
#define SOLVER_BFS_H

#include <vector>
#include <string>
#include <set>
#include "../Maze.h"

class SolverBFS
{
public:
    static std::vector<char> solve(const Maze& startNode);

private:
    static std::string getSignature(const Maze& m);
};

#endif