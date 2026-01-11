#include "SolverGreedyBFS.h"
#include "HeuristicUtils.h"
#include <queue>
#include <iostream>
#include <set>

struct StateGreedy
{
    Maze maze;
    std::vector<char> path;
    int h;
};

struct CompareStateGreedy
{
    bool operator()(const StateGreedy& a, const StateGreedy& b) const
    {
        return a.h > b.h;
    }
};

std::vector<char> SolverGreedyBFS::solve(const Maze& startNode)
{
    std::cout << "Greedy - Best First Search ..." << std::endl;

    // Priority queue (open list). We always expand the state with the smallest h.
    std::priority_queue<StateGreedy, std::vector<StateGreedy>, CompareStateGreedy> open;

    std::set<std::string> visited;

    int h0 = HeuristicUtils::calculateDistance(startNode);
    open.push({ startNode, {}, h0 });
    visited.insert(getSignature(startNode));

    const char moves[4] = { TOP, BOTTOM, LEFT, RIGHT };
    long long iterations = 0;

    while (!open.empty())
    {
        StateGreedy current = open.top();
        open.pop();

        iterations++;

        // If this state is a solution, return the path.
        if (current.maze.isSolution())
        {
            std::cout << "Greedy BFS solution: " << current.path.size() << " moves" << std::endl;
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

                // Only add if we never saw this state before.
                if (visited.find(signature) == visited.end())
                {
                    visited.insert(signature);

                    std::vector<char> nextPath = current.path;
                    nextPath.push_back(dir);
                    int h = HeuristicUtils::calculateDistance(nextMaze);

                    open.push({ nextMaze, nextPath, h });
                }
            }
        }
    }

    std::cout << "Greedy BFS failed after" << iterations << " states explored :(" << std::endl;
    return {};
}

std::string SolverGreedyBFS::getSignature(const Maze& m)
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
