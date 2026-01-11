#include "Maze.h"
#include "GraphicAllegro5.h"
#include <vector>
#include <iostream>

GraphicAllegro5 graphic(1024, 768);
// ---- Brute force ----
static std::vector<char> bruteForce(const Maze& start, int maxLen)
{
    const char moves[4] = {TOP, BOTTOM, LEFT, RIGHT};

    for (int len = 1; len <= maxLen; ++len)
    {
        std::cout << "Test des sequences de " << len << " coups..." << std::endl;

        long long total = 1;
        for (int i = 0; i < len; ++i) total *= 4;

        for (long long code = 0; code < total; ++code)
        {
            Maze m = start;
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
    return {};
}
static int heuristic(const Maze& maze)
{
    //premier test heuristique prend pas en compte les deadlocks et ne place pas de manière optimal
    //juste la cible la plus proche par rapport au caisse
    std::vector<std::pair<int, int>> caisses;
    std::vector<std::pair<int, int>> cibles;
    //collecter
    for (unsigned int i = 0; i < maze.getNbLines(); ++i) {
        for (unsigned int j = 0; j < maze.getNbCols(); ++j) {
            std::pair<int, int> pos = {i, j};
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
                int d = abs(caisse.first - cibles[j].first) +
                       abs(caisse.second - cibles[j].second);
                if (d < minDist) {
                    minDist = d;
                    idxMeilleure = j;
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
int main()
{
    const std::string level = "levels/easy1.txt";
    Maze m(level);

    graphic.show();

    while (!graphic.keyGet(ALLEGRO_KEY_ESCAPE) && !graphic.keyGet(ALLEGRO_KEY_Q))
    {
        // Move player
        if (graphic.keyGet(ALLEGRO_KEY_UP))    m.updatePlayer(TOP);
        if (graphic.keyGet(ALLEGRO_KEY_DOWN))  m.updatePlayer(BOTTOM);
        if (graphic.keyGet(ALLEGRO_KEY_LEFT))  m.updatePlayer(LEFT);
        if (graphic.keyGet(ALLEGRO_KEY_RIGHT)) m.updatePlayer(RIGHT);

        // Brute force
        if (graphic.keyGet(ALLEGRO_KEY_B))
        {
            int maxLen = 100;
            std::vector<char> sol = bruteForce(m, maxLen);

            if (!sol.empty())
            {
                m.playSolution(graphic, sol);
            }
            else
            {
                std::cout << "Aucune solution (maxLen=" << maxLen << ")\n";
            }
        }

        // Test heuristique
        if (graphic.keyGet(ALLEGRO_KEY_H))
        {
            int h = heuristic(m);
            std::cout << "Heuristique = " << h << std::endl;

            if (m.isSolution()) {
                std::cout << "Etat resolu (heuristique devrait etre 0)" << std::endl;
            }
        }

        // Check solved
        if (graphic.keyGet(ALLEGRO_KEY_C))
        {
            if (m.isSolution()) std::cout << "Level solved !" << std::endl;
            else std::cout << "Level not solved !" << std::endl;
        }

        // Play hardcoded test
        if (graphic.keyGet(ALLEGRO_KEY_P))
        {
            const std::vector<char> moves = {BOTTOM, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, TOP, RIGHT, BOTTOM};
            m.playSolution(graphic, moves);
        }

        // Reload
        if (graphic.keyGet(ALLEGRO_KEY_R))
        {
            m = Maze(level);
        }

        // Display
        graphic.clear();
        m.draw(graphic);
        graphic.display();
    }

    return 0;
}