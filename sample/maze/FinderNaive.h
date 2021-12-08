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

class FinderNaive final  : public IFinder
{
public:
    using TOnStepCallback = std::function<void(const TPath&)>;

    FinderNaive(TOnStepCallback&& callback)
        : m_callback(std::move(callback))
        {

        }   

    // IFinder implementation
    virtual TPath Find(const Vector2& from, const Vector2& to, const TMap& map) const override;

private:
    bool FindImpl(const Vector2& start, const Vector2& target, TPath& path, const TMap& map) const;
    static bool CanMove(const Vector2& to, const TPath& path, const TMap& map);

    const TOnStepCallback m_callback;
};

}
