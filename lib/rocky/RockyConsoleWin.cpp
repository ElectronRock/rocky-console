#include <conio.h>
#include "RockyConsoleWin.h"
#include <cstdarg>
#include <cstdio>
#include <cassert>
#include <wtypes.h>
#include <wincon.h>
#include <clocale>

namespace rocky
{
    RockyConsoleWin::RockyConsoleWin()  // NOLINT(cppcoreguidelines-pro-type-member-init)
    {
        InitializeColorMap();
        InitializeKeyMap();
    }

    // place implementation here    
    void RockyConsoleWin::Initialize()
    {
        setlocale(LC_ALL, ".OCP");
        ShowCursor();
    }

    void RockyConsoleWin::Destroy()
    {
        // nothing to do
    }

    void RockyConsoleWin::SetCursor(int show) {
        CONSOLE_CURSOR_INFO ci = { ConsoleCursorSize, show };
        auto* hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorInfo(hStdOut, &ci);
    }

    void RockyConsoleWin::ShowCursor()
    {
        SetCursor(TRUE);
    }

    void RockyConsoleWin::HideCursor()
    {
        SetCursor(FALSE);
    }

    bool RockyConsoleWin::GoToXY(unsigned x, unsigned y)
    {
        const COORD pos = { SHORT(x), SHORT(y) };
        auto* hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        return SetConsoleCursorPosition(hStdOut, pos);
    }

    bool RockyConsoleWin::ObtainXY(unsigned& x, unsigned& y)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;

        if (auto * hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); GetConsoleScreenBufferInfo(hStdOut, &info))
        {
            x = info.dwCursorPosition.X;
            y = info.dwCursorPosition.Y;
            return true;
        }
        return false; // error
    }

    bool RockyConsoleWin::ObtainMaxXY(unsigned& x, unsigned& y)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;

        if (auto * hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); GetConsoleScreenBufferInfo(hStdOut, &info))
        {
            x = info.srWindow.Right - info.srWindow.Left;
            y = info.srWindow.Bottom - info.srWindow.Top;
            return true;
        }
        return false; // error
    }

    bool RockyConsoleWin::Clear()
    {
        if (unsigned mx, my; ObtainMaxXY(mx, my))
        {
            const COORD bufferSize = { SHORT(mx + 1), SHORT(my + 1) };
            const COORD coordinates = { 0, 0 };
            SMALL_RECT srWriteRegion = { 0, 0, SHORT(mx), SHORT(my) };

            auto* lpBuffer = (CHAR_INFO*)calloc(bufferSize.X * bufferSize.Y, sizeof(CHAR_INFO));

            auto* hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            const auto nResult = WriteConsoleOutput(hStdOut, lpBuffer, bufferSize, coordinates, &srWriteRegion);
            free(lpBuffer);

            return nResult != 0;
        }

        return false; // error
    }

    bool RockyConsoleWin::SetTest(const char* format, ...)
    {
        va_list argList;
        char buffer[1024];

        va_start(argList, format);

        assert(format);
        // ReSharper disable once CppDeprecatedEntity
        auto len = _vsnprintf(buffer, sizeof(buffer) - 1, format, argList);
        assert(len >= 0);

        return _cputs(buffer) == 0;
    }

    bool RockyConsoleWin::IsKeyPressed()
    {
        return _kbhit() != 0;
    }

    RockyKey RockyConsoleWin::GetKey()
    {
        int ch = _getch();
        if (ch == 0x00 || ch == 0xE0) // extended code
            ch = -_getch();
        return ConvertKey(ch);
    }

    unsigned short RockyConsoleWin::CombineColors(RockyColor back, RockyColor text)
    {
        return GetColor(text) | FOREGROUND_INTENSITY | GetColor(back) << 4;
    }

    bool RockyConsoleWin::InitColor(unsigned index, RockyColor back, RockyColor text)
    {
        if (index > ConMaxColors)
            return false;
        m_colors[index] = CombineColors(back, text);
        return true;
    }

    bool RockyConsoleWin::SetColor(RockyColor back, RockyColor text)
    {
       const auto color = CombineColors(back, text);
       auto* hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
       return SetConsoleTextAttribute(hStdOut, color) != 0;
    }

    bool RockyConsoleWin::SetColor(unsigned index)
    {
        if (index < 0 || index > ConMaxColors)
            return 0;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        return SetConsoleTextAttribute(hStdOut, m_colors[index]) != 0;
    }

    void RockyConsoleWin::InitializeColorMap()
    {
        m_colorMap =
        {
            {RockyColor::Black, 0x0000},
            {RockyColor::Blue, 0x0001},
            {RockyColor::Green, 0x0002},
            {RockyColor::Red, 0x0004},
            {RockyColor::Yellow, 0x0004 | 0x0002},
            {RockyColor::Magenta, 0x0004 | 0x0001},
            {RockyColor::Cyan, 0x0002 | 0x0001},
            {RockyColor::White, 0x0002 | 0x0001 | 0x0004}
        };
    }

    void RockyConsoleWin::InitializeKeyMap()
    {
        m_keyMap =
        {
            {-72, RockyKey::Up},
            {-75, RockyKey::Left},
            {-77, RockyKey::Right},
            {-80, RockyKey::Down},
            {27, RockyKey::Escape},
            {-82, RockyKey::Insert},
            {-83, RockyKey::Del},
            {'\b', RockyKey::Backspace},
            {'\r', RockyKey::Enter},
            {-71, RockyKey::Home},
            {-79, RockyKey::End},
            {-73, RockyKey::PageUp},
            {-81, RockyKey::PageDown},
        };
    }

    unsigned short RockyConsoleWin::GetColor(RockyColor color)
    {
        return m_colorMap[color];
    }

    RockyKey RockyConsoleWin::ConvertKey(int key)
    {
        return m_keyMap[key];
    }

}
