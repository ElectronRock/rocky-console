/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#include "rocky/IRockyConsole.h"
#include "rocky/RockyConsoleFactory.h"
#include "potential_computing.h"

constexpr static int MinColor { 1 };
constexpr static int MaxColor { 6 };

using namespace rocky::sample;

void InitColors(rocky::IRockyConsole* console);
void Draw(rocky::IRockyConsole* console, const potential_computing::t_matrix& matrix);
void CharAt(int ch, int color, int x, int y, rocky::IRockyConsole* console);
void Move(rocky::RockyKey key, rocky::IRockyConsole* console);
bool SetPotential(rocky::RockyKey key, potential_computing& computer, rocky::IRockyConsole* console);

template<typename T>
T clamp(const T v, const T l, const T r){
    if(v < l) return l;
    if(v > r) return r;
    return v;
}

int main(int argc, char* argv[]) {
    auto* console = rocky::Create();

    console->Initialize();
    InitColors(console);

    unsigned max_x, max_y;
    console->ObtainMaxXY(max_x, max_y);
    potential_computing computer(max_x, max_y);
    
    Draw(console, computer.get_matrix());

    while(true) {   
        if(console->IsKeyPressed()){
            auto key = console->GetKey();
            if(key == rocky::RockyKey::Escape) break;
            Move(key, console);
            if(SetPotential(key, computer, console)){
                computer.compute();
                Draw(console, computer.get_matrix());
            }      
        }
    }

    console->Destroy();

    return 0;
}

void CharAt(int ch, int color, int x, int y, rocky::IRockyConsole* console) {
    unsigned cur_x, cur_y;
    console->ObtainXY(cur_x, cur_y);
    console->GoToXY(x, y);
    console->SetColor(color);
    console->SetText("%c", ch);
    console->GoToXY(cur_x, cur_y);
}

void Draw(rocky::IRockyConsole* console, const potential_computing::t_matrix& matrix) {
    for(auto i_y = 0; i_y < matrix.size(); i_y++) {
        for(auto i_x = 0; i_x < matrix[i_y].size(); i_x++) {
            auto color = clamp((int)matrix[i_y][i_x] + 4, MinColor, MaxColor);
            CharAt(' ', 
                color,
                i_x, i_y, console
            );
        }
    }
    console->HideCursor();
}

void InitColors(rocky::IRockyConsole* console) {
    console->InitColor(MaxColor, rocky::RockyColor::Red, rocky::RockyColor::Red);
    console->InitColor(5, rocky::RockyColor::Yellow, rocky::RockyColor::Yellow);
    console->InitColor(4, rocky::RockyColor::White, rocky::RockyColor::White);
    console->InitColor(3, rocky::RockyColor::Cyan, rocky::RockyColor::Cyan);
    console->InitColor(2, rocky::RockyColor::Blue, rocky::RockyColor::Blue);
    console->InitColor(MinColor, rocky::RockyColor::Black, rocky::RockyColor::Black);
}

void Move(rocky::RockyKey key, rocky::IRockyConsole* console) {
    // TODO: Move cursor
}

bool SetPotential(rocky::RockyKey key, potential_computing& computer, rocky::IRockyConsole* console) {
    // TODO: Add potential to the map
    // M == +
    // P == -

    return false;
}