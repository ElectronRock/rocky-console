#include "PathFinder.h"

#include <cassert>

PathFinder::PathFinder(unsigned x, unsigned y)
    : m_x(x)
    , m_y(y)
{

}

bool PathFinder::DoStep(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map, TPath& path)
{
    return false;
}

PathFinder::TPath PathFinder::Find(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map)
{
    TPath output;
    FindImpl({ m_x, m_y }, { desiredX, desiredY }, output, map);
    return output;
}

bool PathFinder::FindImpl(Vector2 start, Vector2 target, TPath& buffer, const MapMaker::TMap& map)
{
    return false;
}

bool PathFinder::CanMove(unsigned x, unsigned y, const TPath& buffer, const MapMaker::TMap& map)
{
    return false;
}
