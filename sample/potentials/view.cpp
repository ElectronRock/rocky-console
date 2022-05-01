#include "view.h"
#include "rocky/IRockyConsole.h"

template<typename T>
T clamp(const T v, const T l, const T r){
    if(v < l) return l;
    if(v > r) return r;
    return v;
}

namespace rocky::sample {
    void view::Draw() {
        for (auto i_y = 0; i_y < m_matrix.size(); i_y++) {
            for (auto i_x = 0; i_x < m_matrix[i_y].size(); i_x++) {
                auto color = clamp((int) m_matrix[i_y][i_x] + 4, MinColor, MaxColor);
                CharAt(' ',
                       color,
                       i_x, i_y
                );
            }
        }
        m_console.HideCursor();
    }

    void view::InitColors() {
        m_console.InitColor(MaxColor, rocky::RockyColor::Red, rocky::RockyColor::Red);
        m_console.InitColor(5, rocky::RockyColor::Yellow, rocky::RockyColor::Yellow);
        m_console.InitColor(4, rocky::RockyColor::White, rocky::RockyColor::White);
        m_console.InitColor(3, rocky::RockyColor::Cyan, rocky::RockyColor::Cyan);
        m_console.InitColor(2, rocky::RockyColor::Blue, rocky::RockyColor::Blue);
        m_console.InitColor(MinColor, rocky::RockyColor::Black, rocky::RockyColor::Black);
    }

    void view::CharAt(int ch, int color, int x, int y) {
        unsigned cur_x, cur_y;
        m_console.ObtainXY(cur_x, cur_y);
        m_console.GoToXY(x, y);
        m_console.SetColor(color);
        m_console.SetText("%c", ch);
        m_console.GoToXY(cur_x, cur_y);
    }

    view::view(IRockyConsole& console, const std::vector<std::vector<double>>& matrix) :
            m_console(console), m_matrix(matrix)
            {InitColors();}
}