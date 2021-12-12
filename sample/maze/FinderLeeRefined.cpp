#include "FinderLeeRefined.h"
#include "MapMaker.h"
#include <cassert>

namespace Path
{

    namespace
    {
        const auto shifts =
                {
                        Vector2(1, 0),
                        Vector2(-1, 0),
                        Vector2(0, 1),
                        Vector2(0, -1)
                };

        constexpr int Wall = -1;
        constexpr int Free = -2;
    }

    struct Node {
        Node(Vector2 coords_inp, int wave_inp) : coordinates(coords_inp), wave(wave_inp) {}
        Vector2 coordinates = {0, 0};
        int wave = 0;
    };

    FinderLeeRefined::TPath FinderLeeRefined::Find(const Vector2& from, const Vector2& to, const TMap& map) const
    {
        if(map[from.x][from.y] == EntityType::Wall || map[to.x][to.y] == EntityType::Wall)
            return {};

        auto mapCopy = CreateWaveMap(map);
        RunWaves(from, to, mapCopy);
        if(mapCopy[to.x][to.y] == (int)EntityType::Field)
            return {}; // the path could not be found

        return BuildPath(from, to, mapCopy);
    }

    void FinderLeeRefined::RunWaves(const Vector2& from, const Vector2& to, TWaveMap& map) const
    {
        auto curWaveIndex = 0;
        std::deque<Node> waves = {{from, 0}};
        map[from.x][from.y] = 0;
        do
        {
            Node node = waves.front();
            for(auto&& shift : shifts)
            {
                auto desired = node.coordinates + shift;
                if(Suitable(desired, map) && map[desired.x][desired.y] == Free)
                {
                    map[desired.x][desired.y] = node.wave + 1;
                    waves.emplace_back(desired, node.wave + 1);
                    if (node.wave > curWaveIndex) 
                    {
                        ++curWaveIndex;
                        m_callback(map);
                    }
                }
            }
            waves.pop_front();
        }
        while(!waves.empty() && map[to.x][to.y] == Free);
    }

    FinderLeeRefined::TPath FinderLeeRefined::BuildPath(const Vector2& from, const Vector2& to, const TWaveMap& map) const
    {
        auto len = map[to.x][to.y];
        auto wave = len;
        FinderLeeRefined::TPath path;
        path.resize(len + 1);
        auto curPosition = to;
        while(wave > 0)
        {
            path[wave] = curPosition;
            --wave;
            for(auto&& shift : shifts)
            {
                auto&& desired = curPosition + shift;
                if(Suitable(desired, map) && map[desired.x][desired.y] == wave)
                {
                    curPosition = desired;
                    break;
                }
            }
        }
        path[0] = from;
        return path;
    }

    FinderLeeRefined::TWaveMap FinderLeeRefined::CreateWaveMap(const TMap& map) const
    {
        TWaveMap result;
        for(auto&& row : map)
        {
            std::vector<int> waveRow;
            waveRow.reserve(row.size());
            for(auto&& cell : row)
                waveRow.push_back(cell == EntityType::Wall ? Wall : Free);
            result.push_back(std::move(waveRow));
        }
        return result;
    }

    bool FinderLeeRefined::Suitable(const Vector2 desired, const TWaveMap& map) const
    {
        return desired.x > 0 && desired.y > 0
               && desired.x < map.size() && desired.y < map.front().size();
    }

}