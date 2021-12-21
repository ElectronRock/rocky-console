#include "FinderLee.h"
#include "MapMaker.h"
#include <cassert>

namespace Path {

    void FinderLee::RunWaves(const Vector2& from, const Vector2& to, TWaveMap& map) const {
        bool allMarked = true;
        int wave = 0;
        map[from.x][from.y] = 0;
        do {
            allMarked = true;
            for (unsigned i = 0; i < map.size(); ++i) {
                for (unsigned j = 0; j < map.front().size(); ++j) {
                    auto cell = map[i][j];
                    if (cell == wave) {
                        for (auto&& shift: shifts) {
                            auto desired = Vector2{(int) i, (int) j} + shift;
                            if (Suitable(desired, map) && map[desired.x][desired.y] == Free) {
                                allMarked = false;
                                map[desired.x][desired.y] = wave + 1;
                            }
                        }
                    }
                }
            }

            ++wave;
            m_callback(map, wave);

        } while (!allMarked && map[to.x][to.y] == Free);
    }

}