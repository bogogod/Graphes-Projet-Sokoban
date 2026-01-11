#include "SolverBruteForce.h"
#include <iostream>
#include <cmath>

std::vector<char> SolverBruteForce::solve(const Maze& start, int maxLen)
{
    const char moves[4] = {TOP, BOTTOM, LEFT, RIGHT};

    for (int len = 1; len <= maxLen; ++len)
    {
        std::cout << "Test des sequences de " << len << " coups..." << std::endl;

        // Attention: pow peut être lourd, une boucle simple ou bitshift est mieux, 
        // mais gardons ta logique originale pour l'instant
        long long total = 1;
        for (int i = 0; i < len; ++i) total *= 4;

        for (long long code = 0; code < total; ++code)
        {
            Maze m = start; // Copie du labyrinthe
            std::vector<char> seq;
            seq.reserve(len);

            long long x = code;

            for (int step = 0; step < len; ++step)
            {
                int d = (int)(x % 4);
                x /= 4;

                char dir = moves[d];
                m.updatePlayer(dir);
                seq.push_back(dir);
            }

            if (m.isSolution()) {
                std::cout << "Solution trouvee en " << len << " coups!" << std::endl;
                return seq;
            }
        }
    }
    return {}; // Retourne un vecteur vide si rien trouvé
}