#include "PathFinder.h"

#include <cassert>

PathFinder::PathFinder(unsigned x, unsigned y, TCallBack callBack)
    : m_x(x)
    , m_y(y)
    , m_callback(callBack)
{

}

PathFinder::TPath PathFinder::Find(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map)
{
    TPath output;
    FindImpl({ m_x, m_y }, { desiredX, desiredY }, output, map);
    return output;
}

bool PathFinder::FindImpl(Vector2 start, Vector2 target, TPath& buffer, const MapMaker::TMap& map)
{
    if (start == target) {
        buffer.emplace_back(m_x, m_y);
        return true;
    }

    m_callback(buffer);

    std::vector<Vector2> cases = {
            Vector2(start.x + 1, start.y),
            Vector2(start.x - 1, start.y),
            Vector2(start.x, start.y + 1),
            Vector2(start.x, start.y - 1)};

    for(Vector2 step : cases) {
        if ( 0 < step.x < map.size() && 0 < step.y < map[0].size() && CanMove(step.x, step.y, buffer, map)) {
            buffer.emplace_back(m_x, m_y);
            if(FindImpl(step, target, buffer, map)) {
                return true;
            }
            buffer.pop_back();
        }
    }

}

bool PathFinder::CanMove(unsigned x, unsigned y, const TPath& buffer, const MapMaker::TMap& map)
{
    return map[x][y] != MapMaker::EntityType::Wall && buffer.back() != Vector2(x, y);
}
