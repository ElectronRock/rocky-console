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

void InitColors(rocky::IRockyConsole* console);
void Init(rocky::IRockyConsole* console);
void Draw(rocky::IRockyConsole* console);
void CharAt(int ch, int color, int x, int y, rocky::IRockyConsole* console);
void GetKey(rocky::IRockyConsole* console)

int main(int argc, char* argv[])
{
    auto* console = rocky::Create();

    console->Initialize();
    //console->HideCursor();
    bool isPressed = false;
    Init(console);
    while(true) {
        if(isPressed)
            GetKey(console);
    }
    //m_console->ObtainMaxXY(max_x, max_y);

    console->Destroy();

    return 0;
}

void CharAt(int ch, int color, int x, int y, rocky::IRockyConsole* console) {
    console->GoToXY(x, y);
    console->SetColor(color);
    console->SetText("%c", ch);
}

void Init(rocky::IRockyConsole* console) {
    InitColors(console);
    Draw(console);
}

void Draw(rocky::IRockyConsole* console, potential_computing::t_matrix& matrix) {
    for(auto i_y = 0; i_y < matrix.size(); i_y++)
        for(auto i_x = 0; i_x < matrix[i_y].size(); i_x++)
            CharAt(' ', 3, i_x, i_y, console);
}

void InitColors(rocky::IRockyConsole* console) {
    console->InitColor(5, rocky::RockyColor::Red, rocky::RockyColor::Red);
    console->InitColor(4, rocky::RockyColor::Yellow, rocky::RockyColor::Yellow);
    console->InitColor(3, rocky::RockyColor::White, rocky::RockyColor::White);
    console->InitColor(2, rocky::RockyColor::Cyan, rocky::RockyColor::Cyan);
    console->InitColor(1, rocky::RockyColor::Blue, rocky::RockyColor::Blue);
}