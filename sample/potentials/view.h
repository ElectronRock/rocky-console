#include <vector>
/* Copyright (C) 2022 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

constexpr static int MinColor { 1 };
constexpr static int MaxColor { 6 };

namespace rocky {
    class IRockyConsole;
}

namespace rocky::sample {
    class view final {
    public:
        view(IRockyConsole& console, const std::vector<std::vector<double>>& matrix);

        void Draw();
    private:
        const std::vector<std::vector<double>>& m_matrix;
        IRockyConsole& m_console;

        void InitColors();
        void CharAt(int ch, int color, int x, int y);
    };
}
