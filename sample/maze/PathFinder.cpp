#include "PathFinder.h"

PathFinder::PathFinder(unsigned x, unsigned y)
    : m_x(x)
    , m_y(y)
{

}

PathFinder::TPath PathFinder::Find(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map)
{
    PathFinder::TPath output;
    FindImpl({m_x, m_y}, {desiredX, desiredY}, output, map);
    return output;
}

bool PathFinder::FindImpl(PathFinder::Vector2 start, PathFinder::Vector2 target, PathFinder::TPath &buffer, const MapMaker::TMap& map) {
    if(start==target)
    {
        buffer.emplace_back(start.x,start.y);
        return true;
    }
    if(start.x+1<map.size() && Vector2{start.x+1, start.y}!=buffer.back() && map[start.x+1][start.y]!=MapMaker::EntityType::Wall)
    {
        buffer.emplace_back(start.x,start.y);
        if(FindImpl({start.x+1, start.y}, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }
    if(start.x-1>0 && Vector2{start.x-1, start.y}!=buffer.back() && map[start.x-1][start.y]!=MapMaker::EntityType::Wall)
    {
        buffer.emplace_back(start.x,start.y);
        if(FindImpl({start.x-1, start.y}, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }
    if(start.y+1<map[0].size() && Vector2{start.x, start.y+1}!=buffer.back() && map[start.x][start.y+1]!=MapMaker::EntityType::Wall)
    {
        buffer.emplace_back(start.x,start.y);
        if(FindImpl({start.x, start.y+1}, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }
    if(start.y-1>0 && Vector2{start.x, start.y-1}!=buffer.back() && map[start.x][start.y-1]!=MapMaker::EntityType::Wall)
    {
        buffer.emplace_back(start.x,start.y);
        if(FindImpl({start.x, start.y+1}, target, buffer, map))
        {
            return true;
        }
        buffer.pop_back();
    }
    return false;
}

