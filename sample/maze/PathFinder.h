/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include <deque>
#include "MapMaker.h"

class PathFinder final {
public:

    struct Vector2
    {
        unsigned x;
        unsigned y;
    };

    using TPath = std::deque<Vector2>;

    PathFinder(unsigned x, unsigned y);

    TPath Find(unsigned desiredX, unsigned desiredY, const MapMaker::TMap& map);
    
private:
    unsigned m_x;
    unsigned m_y;
};