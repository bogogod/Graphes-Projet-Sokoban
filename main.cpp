#include "Maze.h"
#include "GraphicAllegro5.h"
#include <vector>
#include <iostream>

GraphicAllegro5 graphic(1024, 768);

// ---- BruteForce----
static std::vector<char> bruteForce(const Maze& start, int maxLen)
{
    for (int len = 1; len <= maxLen; ++len)
    {
        std::cout << "Test des sequences de " << len << " coups..." << std::endl;
        long long total = 1;
        for (int i = 0; i < len; ++i) total *= 4;

        for (long long code = 0; code < total; ++code)
        {
            Maze m = start;
            std::vector<char> seq;
            long long x = code;

            for (int step = 0; step < len; ++step)
            {
                char dir = (x % 4);  // 0=TOP, 1=BOTTOM, 2=LEFT, 3=RIGHT
                x /= 4;

                if (m.updatePlayer(dir)) {
                    seq.push_back(dir);
                    return seq;
                }
                seq.push_back(dir);
            }
        }
    }
    return {};
}
int main()
{
    const std::string level = "levels/Easy1.txt";
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
            int maxLen = 30;
            std::cout << "Recherche brute force (max " << maxLen << " coups)..." << std::endl;

            std::vector<char> sol = bruteForce(m, maxLen);

            if (!sol.empty())
            {
                std::cout << "Solution trouvee en " << sol.size() << " coups!" << std::endl;
                m.playSolution(graphic, sol);
            }
            else
            {
                std::cout << "Aucune solution en " << maxLen << " coups maximum." << std::endl;
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