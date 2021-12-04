#include "PathFinder.h"

#include <cassert>

PathFinder::PathFinder(unsigned x, unsigned y)
    : m_x(x)
    , m_y(y)
{

}

bool PathFinder::DoStep(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map, TPath& path)
{
    assert(!path.empty());
    auto&& start = path.back();
    if (start == Vector2(desiredX, desiredY))
        return true;

    if (start.x + 1 < map.size() && CanMove(start.x + 1, start.y, path, map))
        path.emplace_back(start.x + 1, start.y);
    else if (start.x > 1 && CanMove(start.x - 1, start.y, path, map))
        path.emplace_back(start.x - 1, start.y);
    else if(start.y + 1 < map[0].size() && CanMove(start.x, start.y + 1, path, map))
        path.emplace_back(start.x, start.y + 1);
    else if (start.y > 1 && CanMove(start.x, start.y - 1, path, map))
        path.emplace_back(start.x, start.y - 1);
    
    return false;
}

PathFinder::TPath PathFinder::Find(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map)
{
    TPath output;
    FindImpl({ m_x, m_y }, { desiredX, desiredY }, output, map);
    return output;
}

bool PathFinder::FindImpl(Vector2 start, Vector2 target, TPath& buffer, const MapMaker::TMap& map) {
    if (start == target)
    {
        buffer.emplace_back(start.x, start.y);
        return true;
    }

    if (start.x + 1 < map.size() && CanMove(start.x + 1, start.y, buffer, map))
    {
        buffer.emplace_back(start.x, start.y);
        if (FindImpl({ start.x + 1, start.y }, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }

    if (start.x > 1 && CanMove(start.x - 1, start.y, buffer, map))
    {
        buffer.emplace_back(start.x, start.y);
        if (FindImpl({ start.x - 1, start.y }, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }
    if (start.y + 1 < map[0].size() && CanMove(start.x, start.y + 1, buffer, map))
    {
        buffer.emplace_back(start.x, start.y);
        if (FindImpl({ start.x, start.y + 1 }, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }
    if (start.y > 1 && CanMove(start.x, start.y - 1, buffer, map))
    {
        buffer.emplace_back(start.x, start.y);
        if (FindImpl({ start.x, start.y - 1 }, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }
    return false;
}

bool PathFinder::CanMove(unsigned x, unsigned y, const TPath& buffer, const MapMaker::TMap& map)
{
    return map[x][y] != MapMaker::EntityType::Wall
        && find(begin(buffer), end(buffer), Vector2(x, y)) == end(buffer);
}
