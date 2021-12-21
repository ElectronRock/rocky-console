#include "FinderLeeBase.h"
#include "MapMaker.h"
#include <cassert>

namespace Path
{

    FinderLeeBase::TPath FinderLeeBase::Find(const Vector2& from, const Vector2& to, const TMap& map) const
    {
        if(map[from.x][from.y] == EntityType::Wall || map[to.x][to.y] == EntityType::Wall)
            return {};

        auto mapCopy = CreateWaveMap(map);
        RunWaves(from, to, mapCopy);
        if(mapCopy[to.x][to.y] == (int)EntityType::Field)
            return {}; // the path could not be found

        return BuildPath(from, to, mapCopy);
    }

    void FinderLeeBase::RunWaves(const Vector2& from, const Vector2& to, FinderLeeBase::TWaveMap& map) const {}

    FinderLeeBase::TPath FinderLeeBase::BuildPath(const Vector2& from, const Vector2& to, const TWaveMap& map) const
    {
        auto len = map[to.x][to.y];
        auto wave = len;
        FinderLeeBase::TPath path;
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

    FinderLeeBase::TWaveMap FinderLeeBase::CreateWaveMap(const TMap& map) const {
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

    bool FinderLeeBase::Suitable(const Vector2 desired, const TWaveMap& map) const
    {
        return desired.x > 0 && desired.y > 0
               && desired.x < map.size() && desired.y < map.front().size();
    }



}