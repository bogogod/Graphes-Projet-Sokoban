#include "SolverBFS.h"
#include <queue>       
#include <iostream>
#include <algorithm>

// Structure d'état pour le BFS
struct StateBFS {
    Maze maze;
    std::vector<char> path;
};

std::vector<char> SolverBFS::solve(const Maze& startNode)
{
    std::cout << "Demarrage du Solver BFS (Recherche du chemin le plus court)..." << std::endl;

    // Utilisation d'une FILE (Queue) pour le parcours en largeur
    std::queue<StateBFS> q;
    std::set<std::string> visited;

    // État initial
    q.push({ startNode, {} });
    visited.insert(getSignature(startNode));

    const char moves[4] = { TOP, BOTTOM, LEFT, RIGHT };
    long long iterations = 0;

    while (!q.empty())
    {
        // On récupère le PREMIER élément ajouté (FIFO)
        StateBFS current = q.front();
        q.pop();

        iterations++;

        // Affichage de debug périodique
        if (iterations % 50000 == 0) {
            std::cout << "BFS running... " << iterations << " etats testes. Longueur actuelle: " << current.path.size() << std::endl;
        }

        if (current.maze.isSolution())
        {
            std::cout << "Solution OPTIMALE trouvee en " << current.path.size() << " coups !" << std::endl;
            std::cout << "Etats explores : " << iterations << std::endl;
            return current.path;
        }

        for (char dir : moves)
        {
            Maze nextMaze = current.maze;

            std::pair<int, int> oldPos = nextMaze.getPlayerPosition();
            bool solved = nextMaze.updatePlayer(dir);
            std::pair<int, int> newPos = nextMaze.getPlayerPosition();

            if (solved || oldPos != newPos)
            {
                std::string signature = getSignature(nextMaze);

                if (visited.find(signature) == visited.end())
                {
                    visited.insert(signature);
                    
                    std::vector<char> nextPath = current.path;
                    nextPath.push_back(dir);

                    // Ajout à la fin de la file
                    q.push({ nextMaze, nextPath });
                }
            }
        }
    }

    std::cout << "Aucune solution BFS trouvee (" << iterations << " etats)." << std::endl;
    return {};
}

// Même signature que pour le DFS
std::string SolverBFS::getSignature(const Maze& m)
{
    std::string sig = "";
    std::pair<int, int> pos = m.getPlayerPosition();
    sig += "P:" + std::to_string(pos.first) + "," + std::to_string(pos.second) + "|";

    for (unsigned int i = 0; i < m.getNbLines(); ++i)
    {
        for (unsigned int j = 0; j < m.getNbCols(); ++j)
        {
            std::pair<int, int> p = { (int)i, (int)j };
            if (m.isBox(p)) 
            {
                sig += "B" + std::to_string(i) + "-" + std::to_string(j);
            }
        }
    }
    return sig;
}