#include "FinderLeeRefined.h"
#include "MapMaker.h"
#include <cassert>

namespace Path
{

void FinderLeeRefined::RunWaves(const Vector2& from, const Vector2& to, TWaveMap& map) const
{
    auto curWaveIndex = 0u;
    std::deque<Vector2> waves = {from};
    map[from.x][from.y] = 0;
    do
    {
        Vector2 node = waves.front();
        if (map[node.x][node.y] > curWaveIndex)
        {
            ++curWaveIndex;
            m_callback(map, curWaveIndex);
        }
        for(auto&& shift : shifts)
        {
            auto desired = node + shift;
            if(Suitable(desired, map) && map[desired.x][desired.y] == Free)
            {
                map[desired.x][desired.y] = map[node.x][node.y] + 1;
                waves.emplace_back(desired);
            }
        }
        waves.pop_front();
    }
    while(!waves.empty() && map[to.x][to.y] == Free);
}

}