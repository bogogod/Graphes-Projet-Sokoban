#include "HeuristicUtils.h"
#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib> // pour abs

int HeuristicUtils::calculateDistance(const Maze& maze)
{
    std::vector<std::pair<int, int>> caisses;
    std::vector<std::pair<int, int>> cibles;

    // 1. Collecter les positions
    for (unsigned int i = 0; i < maze.getNbLines(); ++i) {
        for (unsigned int j = 0; j < maze.getNbCols(); ++j) {
            std::pair<int, int> pos = { (int)i, (int)j };
            if (maze.isGoal(pos)) cibles.push_back(pos);
            // Une caisse est une "BOX" mais pas "BOX_PLACED" (si on veut compter la distance restante)
            // Ta logique originale incluait les caisses non placées sur un goal
            if (maze.isBox(pos) && !maze.isGoal(pos)) caisses.push_back(pos);
        }
    }

    if (caisses.empty()) return 0;

    int total = 0;
    std::vector<bool> ciblePrises(cibles.size(), false);

    // 2. Calculer les distances (Algorithme glouton simple)
    for (const auto& caisse : caisses) {
        int minDist = INT_MAX;
        int idxMeilleure = -1;

        // Trouver la cible libre la plus proche
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
        
        // Assigner cette caisse à cette cible
        if (idxMeilleure != -1) {
            total += minDist;
            ciblePrises[idxMeilleure] = true;
        }
    }

    return total;
}