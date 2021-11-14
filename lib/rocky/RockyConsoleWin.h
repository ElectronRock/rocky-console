/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include "rocky/IRockyConsole.h"
#include <unordered_map>

namespace rocky
{

    class RockyConsoleWin final : public IRockyConsole
    {
        using TColorMap = std::unordered_map<RockyColor, short>;
        using TKeyMap = std::unordered_map<int, RockyKey>;
        void InitializeColorMap();
        void InitializeKeyMap();
        RockyConsoleWin();

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

        // Own methods

        short GetColor(RockyColor color);
        static void SetCursor(int show);
        RockyKey ConvertKey(int key);

        static constexpr unsigned ConMaxColors = 64;
        static constexpr unsigned ConsoleCursorSize = 25;

        short m_colors[ConMaxColors];
        TColorMap m_colorMap;
        TKeyMap m_keyMap;

        friend IRockyConsole* Create();
    };
}