/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include <deque>
#include "Vector2.h"

enum class EntityType;

namespace Path
{

class IFinder 
{
public:
    virtual ~IFinder() = default;
    IFinder() = default;

    using TPath = std::deque<Vector2>;
    using TMap = std::vector<std::vector<EntityType>>;

    virtual TPath Find(const Vector2& from, const Vector2& to, const TMap& map) const = 0;
};

}