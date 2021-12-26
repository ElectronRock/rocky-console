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
#include "IFinder.h"

namespace Path
{

class FinderLeeBase : public IFinder
{
public:
    using TWaveMap = std::vector<std::vector<int>>;
    using TOnStepCallback = std::function<void(const TWaveMap&, unsigned)>;

    FinderLeeBase(TOnStepCallback&& callback)
            : m_callback(std::move(callback))
    {

    }

    // IFinder implementation
    virtual TPath Find(const Vector2& from, const Vector2& to, const TMap& map) const override;

protected:
    static constexpr Vector2 shifts[4] =
    {
            Vector2(1, 0),
            Vector2(-1, 0),
            Vector2(0, 1),
            Vector2(0, -1)
    };

    static constexpr int Wall = -1;
    static constexpr int Free = -2;

    virtual void RunWaves(const Vector2& from, const Vector2& to, TWaveMap& map) const = 0;

    bool Suitable(const Vector2 desired, const TWaveMap& map) const;
    const TOnStepCallback m_callback;

private:
    TWaveMap CreateWaveMap(const TMap& map) const;
    TPath BuildPath(const Vector2& from, const Vector2& to, const TWaveMap& map) const;
};

}
