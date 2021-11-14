#include "rocky/Foundation.h"
#if !defined(ROCKY_WIN)
#include <ncurses.h>
#include "RockyConsoleNix.h"
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <locale.h>

static constexpr int ConsoleCursorSize = 25;

namespace rocky
{
    RockyConsoleNix::RockyConsoleNix() {
        m_colormap =
                {
                        {RockyColor::Black, 0},
                        {RockyColor::Red, 1},
                        {RockyColor::Green, 2},
                        {RockyColor::Yellow, 3},
                        {RockyColor::Blue, 4},
                        {RockyColor::Magenta, 5},
                        {RockyColor::Cyan, 6},
                        {RockyColor::White, 7}
                };
        m_keymap =
                {
                        {0403, RockyKey::Up},
                        {0404, RockyKey::Left},
                        {0405, RockyKey::Right},
                        {0402, RockyKey::Down},
                        {27, RockyKey::Escape},
                        {0513, RockyKey::Insert},
                        {0512, RockyKey::Del},
                        {127, RockyKey::Backspace},
                        {'\n', RockyKey::Enter},
                        {0406, RockyKey::Home},
                        {0550, RockyKey::End},
                        {0523, RockyKey::PageUp},
                        {0522, RockyKey::PageDown},
                };
    }

    void RockyConsoleNix::Initialize() {
        initscr();
        noecho();
        cbreak();
        nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
        start_color();
        attron(A_BOLD);
        ShowCursor();
    }

    void RockyConsoleNix::Destroy() {
        endwin();
    }

    void RockyConsoleNix::SetCursor(int show) {
    }
    void RockyConsoleNix::ShowCursor() {
        curs_set(1);
    }
    void RockyConsoleNix::HideCursor() {
        curs_set(0);
    }

    bool RockyConsoleNix::GoToXY(unsigned int x, unsigned int y) {
        return move(y, x);
    }

    bool RockyConsoleNix::ObtainXY(unsigned int& x, unsigned int& y) {
        return getyx(stdscr, y, x);
    }

    bool RockyConsoleNix::ObtainMaxXY(unsigned int& x, unsigned int& y) {
        return getmaxyx(stdscr, y, x);
    }

    bool RockyConsoleNix::Clear() {
        clear();
        return refresh();
    }

    bool RockyConsoleNix::SetText(const char* format, ...) {
        va_list arglist;
        char buffer[1024];
        int len;

        va_start(arglist, format);

        len = vsnprintf(buffer, sizeof(buffer)-1, format, arglist);
        len = (printw(buffer) != ERR) ? len : -1;
        refresh();
        return len;
    }

    bool RockyConsoleNix::IsKeyPressed() {
        int ch = getch();
        if (ch != ERR)
        {
            ungetch(ch);
            return true;
        }
        return false;
    }

    RockyKey RockyConsoleNix::GetKey() {
        return m_keymap[getch()];
    }

    bool RockyConsoleNix::InitColor(unsigned int index, RockyColor back, RockyColor text) {
        return init_pair(index, m_colormap[text], m_colormap[back]);
    }

    bool RockyConsoleNix::SetColor(unsigned int index) {
        return attron(COLOR_PAIR(index));
    }

    bool RockyConsoleNix::SetColor(RockyColor back, RockyColor text) {
        return false;
    }

}

#endif
