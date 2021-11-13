/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include "rocky/IRockyConsole.h"

namespace rocky
{

    class RockyConsoleWin final : public IRockyConsole
    {
        RockyConsoleWin() = default;

        virtual void Initialize() override;
        virtual void Destroy() override;
        virtual void ShowCursor() override;
        virtual void HideCursor() override;
        virtual bool GoToXY(unsigned x, unsigned y) override;
        virtual bool ObtainXY(unsigned& x, unsigned& y) override;
        virtual bool ObtainMaxXY(unsigned& x, unsigned& y) override;
        virtual bool Clear() override;
        virtual bool SetTest(const char* format, ...) override;
        virtual bool IsKeyPressed() override;
        virtual RockyKey GetKey() override;
        virtual bool InitColor(unsigned index, RockyColor back, RockyColor text) override;
        virtual bool SetColor(unsigned index) override;
        virtual bool SetColor(RockyColor back, RockyColor text) override;

        friend IRockyConsole* Create();
    };
}