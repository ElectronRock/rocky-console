#include "FinderLee.h"
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

FinderLee::TPath FinderLee::Find(const Vector2& from, const Vector2& to, const TMap& map) const
{
    if(map[from.x][from.y] == EntityType::Wall || map[to.x][to.y] == EntityType::Wall)
        return {};

    auto mapCopy = CreateWaveMap(map);
    RunWaves(from, to, mapCopy);
    if(mapCopy[to.x][to.y] == (int)EntityType::Field)
        return {}; // the path could not be found

    return BuildPath(from, to, mapCopy);
}

void FinderLee::RunWaves(const Vector2& from, const Vector2& to, TWaveMap& map) const
{
    bool allMarked = true;
    int wave = 0;
    map[from.x][from.y] = 0;
    do 
    {
        allMarked = true;
        for(unsigned i = 0; i < map.size(); ++i)
        {
            for(unsigned j = 0; j < map.front().size(); ++j)
            {
                auto cell = map[i][j];
                if(cell == wave)
                {
                    for(auto&& shift : shifts)
                    {
                        auto desired = Vector2{ (int)i, (int)j } + shift;
                        if(Suitable(desired, map) && map[desired.x][desired.y] == Free)
                        {
                            allMarked = false;
                            map[desired.x][desired.y] = wave + 1;
                        }
                    }
                }
            }
        }

        m_callback(map);
        ++wave;
    } 
    while(!allMarked && map[to.x][to.y] == Free);
}

FinderLee::TPath FinderLee::BuildPath(const Vector2& from, const Vector2& to, const TWaveMap& map) const 
{
    auto len = map[to.x][to.y];
    auto wave = len;
    FinderLee::TPath path;
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

FinderLee::TWaveMap FinderLee::CreateWaveMap(const TMap& map) const
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

bool FinderLee::Suitable(const Vector2 desired, const TWaveMap& map) const
{
    return desired.x > 0 && desired.y > 0 
        && desired.x < map.size() && desired.y < map.front().size();
}

}