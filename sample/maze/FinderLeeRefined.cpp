#include "FinderLeeRefined.h"
#include "MapMaker.h"
#include <cassert>

namespace Path
{

    struct Node 
    {
        Node(Vector2 coords_inp, int wave_inp) : coordinates(coords_inp), wave(wave_inp) {}
        Vector2 coordinates = {0, 0};
        int wave = 0;
    };


    void FinderLeeRefined::RunWaves(const Vector2& from, const Vector2& to, TWaveMap& map) const
    {
        auto curWaveIndex = 0u;
        std::deque<Node> waves = {{from, 0}};
        map[from.x][from.y] = 0;
        do
        {
            Node node = waves.front();
            if (node.wave > curWaveIndex)
            {
                ++curWaveIndex;
                m_callback(map, curWaveIndex);
            }
            for(auto&& shift : shifts)
            {
                auto desired = node.coordinates + shift;
                if(Suitable(desired, map) && map[desired.x][desired.y] == Free)
                {
                    map[desired.x][desired.y] = node.wave + 1;
                    waves.emplace_back(desired, node.wave + 1);
                }
            }
            waves.pop_front();
        }
        while(!waves.empty() && map[to.x][to.y] == Free);
    }
}