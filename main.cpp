#include "Maze.h"
#include "GraphicAllegro5.h"
#include <vector>
#include <iostream>
#include "solvers/SolverBruteForce.h"
#include "solvers/HeuristicUtils.h"
#include "solvers/SolverDFS.h"
#include "solvers/SolverBFS.h"
#include "solvers/SolverGreedyBFS.h"

GraphicAllegro5 graphic(1024, 768);


int main()
{
    const std::string level = "levels/easy5.txt";

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
            int maxLen = 12;
            std::vector<char> sol = SolverBruteForce::solve(m, maxLen);

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
            int h = HeuristicUtils::calculateDistance(m);
            std::cout << "Heuristique = " << h << std::endl;

            if (m.isSolution()) {
                std::cout << "Etat resolu (heuristique devrait etre 0)" << std::endl;
            }
        }

        //DFS
        if (graphic.keyGet(ALLEGRO_KEY_D))
        {
            std::vector<char> sol = SolverDFS::solve(m, 200);

            if (!sol.empty()) m.playSolution(graphic, sol);
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
