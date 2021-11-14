#if defined(ROCKY_WIN)
#include <conio.h> //ну это виндовая, но она просто ругается на виндовский файл, тут if
#include "rocky/Foundation.h"
#include "RockyConsoleWin.h"
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <wtypes.h>
#include <wincon.h>
#include <locale.h>

static constexpr int ConsoleCursorSize = 25;

namespace rocky
{
    RockyConsoleWin::RockyConsoleWin()
    {
        m_colormap =
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
        m_keymap =
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

    // place implementation here    
    void RockyConsoleWin::Initialize()
    {
        setlocale(LC_ALL, ".OCP");
        ShowCursor();
    }

    void RockyConsoleWin::Destroy()
    {
        ; // nothing to do
    }

    void RockyConsoleWin::SetCursor(int show) {
        CONSOLE_CURSOR_INFO ci = { ConsoleCursorSize, show };
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
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
        COORD pos = { SHORT(x), SHORT(y) };
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        return SetConsoleCursorPosition(hStdOut, pos);
    }

    bool RockyConsoleWin::ObtainXY(unsigned& x, unsigned& y)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            x = csbi.dwCursorPosition.X;
            y = csbi.dwCursorPosition.Y;
            return true;
        }
        return false; // error
    }

    bool RockyConsoleWin::ObtainMaxXY(unsigned& x, unsigned& y)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            x = csbi.srWindow.Right - csbi.srWindow.Left;
            y = csbi.srWindow.Bottom - csbi.srWindow.Top;
            return true;
        }
        return false; // error
    }

    bool RockyConsoleWin::Clear()
    {
        unsigned mx, my;

        if (ObtainMaxXY(mx, my))
        {
            COORD szBuf = { SHORT(mx + 1), SHORT(my + 1) };
            COORD BufferCoord = { 0, 0 };
            SMALL_RECT srWriteRegion = { 0, 0, SHORT(mx), SHORT(my) };

            auto* lpBuffer = (CHAR_INFO*)calloc(szBuf.X * szBuf.Y, sizeof(CHAR_INFO));

            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            int nResult = WriteConsoleOutput(hStdOut, lpBuffer, szBuf, BufferCoord, &srWriteRegion);
            free(lpBuffer);

            return nResult != 0;
        }
        return false; // error
    }

    bool RockyConsoleWin::SetTest(const char* format, ...)
    {
        va_list arglist;
        char buffer[1024];

        va_start(arglist, format);

        assert(format);
        int len = _vsnprintf(buffer, sizeof(buffer) - 1, format, arglist);
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
        return ConvtKey(ch);
    }

    bool RockyConsoleWin::InitColor(unsigned index, RockyColor back, RockyColor text)
    {
        if (index < 0 || index > ConMaxColors)
            return 0;
        m_colors[index] = GetColor(text) | FOREGROUND_INTENSITY | (GetColor(back) << 4);
        return 1;
    }

    bool RockyConsoleWin::SetColor(RockyColor back, RockyColor text)
    {
       auto color = GetColor(text) | FOREGROUND_INTENSITY | (GetColor(back) << 4);
       HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
       return SetConsoleTextAttribute(hStdOut, color) != 0;
    }

    bool RockyConsoleWin::SetColor(unsigned index)
    {
        if (index < 0 || index > ConMaxColors)
            return 0;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        return SetConsoleTextAttribute(hStdOut, m_colors[index]) != 0;
    }

    short RockyConsoleWin::GetColor(RockyColor color)
    {
        return m_colormap[color];
    }

    RockyKey RockyConsoleWin::ConvtKey(int key)
    {
        return m_keymap[key];
    }
}
#endif
