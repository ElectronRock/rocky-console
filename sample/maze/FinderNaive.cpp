#include "FinderNaive.h"
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
}

bool FinderNaive::CanMove(const Vector2& to, const TPath& path, const FinderNaive::TMap& map)
{
    return to.x > 0 && to.y > 0 && to.x < map.size() && to.x < map.back().size()
        && map[to.x][to.y] != EntityType::Wall
        && (path.empty() || path.back() != to);
}

FinderNaive::TPath FinderNaive::Find(const Vector2& from, const Vector2& to, const TMap& map) const
{
    TPath output;
    FindImpl(from, to, output, map);
    return output;
}

bool FinderNaive::FindImpl(const Vector2& from, const Vector2& to, TPath& path, const MapMaker::TMap& map) const
{
    if(m_callback)
        m_callback(path);

    if (from == to)
    {
        path.emplace_back(from);
        return true;
    }

    for(auto&& shift : shifts)
    {
        auto&& desired = shift + from;
        if(CanMove(desired, path, map))
        {
            path.emplace_back(desired);
            if(FindImpl(desired, to, path, map))
                return true;
            path.pop_back();
        }
    }

    return false;
}

}


