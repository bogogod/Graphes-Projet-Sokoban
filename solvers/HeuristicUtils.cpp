#include "HeuristicUtils.h"
#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib> // pour abs

int HeuristicUtils::calculateDistance(const Maze& maze)
{
    //premier test heuristique prend pas en compte les deadlocks et ne place pas de manière optimal
    //juste la cible la plus proche par rapport au caisse
    std::vector<std::pair<int, int>> caisses;
    std::vector<std::pair<int, int>> cibles;

    //collecter
    for (unsigned int i = 0; i < maze.getNbLines(); ++i) {
        for (unsigned int j = 0; j < maze.getNbCols(); ++j) {
            std::pair<int, int> pos = { (int)i, (int)j };
            if (maze.isGoal(pos)) cibles.push_back(pos);
            if (maze.isBox(pos) && !maze.isGoal(pos)) caisses.push_back(pos);
        }
    }

    if (caisses.empty()) return 0;

    int total = 0;
    std::vector<bool> ciblePrises(cibles.size(), false);

    //pour chaque caisse dans l'ordre
    for (const auto& caisse : caisses) {
        int minDist = INT_MAX;
        int idxMeilleure = -1;

        //trouver la cible libre la plus proche
        for (size_t j = 0; j < cibles.size(); ++j) {
            if (!ciblePrises[j]) {
                int d = std::abs(caisse.first - cibles[j].first) +
                        std::abs(caisse.second - cibles[j].second);
                if (d < minDist) {
                    minDist = d;
                    idxMeilleure = (int)j;
                }
            }
        }
        
        //assigner cette caisse à cette cible
        if (idxMeilleure != -1) {
            total += minDist;
            ciblePrises[idxMeilleure] = true;
        }
    }

    return total;
}