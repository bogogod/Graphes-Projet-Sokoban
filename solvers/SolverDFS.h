#ifndef SOLVER_DFS_H
#define SOLVER_DFS_H

#include <vector>
#include <string>
#include <set>
#include "../Maze.h"

class SolverDFS
{
public:
    static std::vector<char> solve(const Maze& startNode, int maxDepth);

private:
    // Helper pour générer une clé unique (signature) représentant l'état du labyrinthe
    // (Position du joueur + positions des boîtes) pour éviter les cycles.
    static std::string getSignature(const Maze& m);
};

#endif