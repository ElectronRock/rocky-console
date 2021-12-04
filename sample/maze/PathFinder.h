/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include <deque>
#include <functional>
#include "MapMaker.h"

class PathFinder final {
public:

    struct Vector2
    {
        Vector2(unsigned ix, unsigned iy) : x(ix), y(iy) {}
        bool operator==(const Vector2& rhs) const { return x == rhs.x && y == rhs.y; }
        bool operator!=(const Vector2& rhs) const { return !(*this == rhs); }
        unsigned x;
        unsigned y;
    };

    using TPath = std::deque<Vector2>;
    using TCallBack = std::function<void(TPath&)>;
    PathFinder(unsigned x, unsigned y, TCallBack callBack);

    TPath Find(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map);

private:
    bool FindImpl(Vector2 start, Vector2 target, TPath& buffer, const MapMaker::TMap& map);
    bool CanMove(unsigned x, unsigned y, const TPath& buffer, const MapMaker::TMap& map);

    TCallBack m_callback;

    unsigned m_x;
    unsigned m_y;
};