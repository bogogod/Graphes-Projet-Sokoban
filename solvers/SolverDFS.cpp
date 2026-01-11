#include "SolverDFS.h"
#include <stack>
#include <iostream>
#include <set>
#include <string>

struct StateDFS {
    Maze maze;
    std::vector<char> path;
    int depth;
};

std::vector<char> SolverDFS::solve(const Maze& startNode, int maxDepth)
{
    std::cout << "Demarrage du Solver DFS (Profondeur max: " << maxDepth << ")..." << std::endl;

    std::stack<StateDFS> s;
    std::set<std::string> visited;

    s.push({ startNode, {}, 0 });
    visited.insert(getSignature(startNode));

    const char moves[4] = { TOP, BOTTOM, LEFT, RIGHT };
    long long iterations = 0;

    while (!s.empty())
    {
        StateDFS current = s.top();
        s.pop();

        iterations++;

        if (current.maze.isSolution())
        {
            std::cout << "Solution DFS trouvee en " << current.depth << " coups !" << std::endl;
            return current.path;
        }
        if (current.depth >= maxDepth) continue;

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

                    s.push({ nextMaze, nextPath, current.depth + 1 });
                }
            }
        }
    }

    std::cout << "Echec DFS (" << iterations << " etats explores)." << std::endl;
    return {};
}

std::string SolverDFS::getSignature(const Maze& m)
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