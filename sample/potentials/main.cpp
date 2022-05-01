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
#include "view.h"


using namespace rocky::sample;

void Move(rocky::RockyKey key, rocky::IRockyConsole* console);
bool SetPotential(rocky::RockyKey key, potential_computing& computer, rocky::IRockyConsole* console);



int main(int argc, char* argv[]) {
    auto* console = rocky::Create();
    console->Initialize();

    unsigned max_x, max_y;
    console->ObtainMaxXY(max_x, max_y);
    potential_computing computer(max_x, max_y);
    view viewer(*console, computer.get_matrix());
    viewer.Draw();

    while(true) {   
        if(console->IsKeyPressed()){
            auto key = console->GetKey();
            if(key == rocky::RockyKey::Escape) break;
            Move(key, console);
            if(SetPotential(key, computer, console)){
                computer.compute();
                viewer.Draw();
            }      
        }
    }

    console->Destroy();

    return 0;
}

void Move(rocky::RockyKey key, rocky::IRockyConsole* console) {
    unsigned cur_x, cur_y;
    console->ObtainXY(cur_x, cur_y);

    if (key == rocky::RockyKey::Up) {
        console->GoToXY(cur_x, cur_y - 1);
    }
    else if (key == rocky::RockyKey::Down) {
        console->GoToXY(cur_x, cur_y + 1);
    }
    else if (key == rocky::RockyKey::Left) {
        console->GoToXY(cur_x - 1, cur_y);
    }
    else if (key == rocky::RockyKey::Right) {
        console->GoToXY(cur_x + 1, cur_y);
    }
    console->ShowCursor();
}

bool SetPotential(rocky::RockyKey key, potential_computing& computer, rocky::IRockyConsole* console) {
    if (key == rocky::RockyKey::Minus || key == rocky::RockyKey::Plus ) {
        charge to_update;
        unsigned cur_x, cur_y;
        console->ObtainXY(cur_x, cur_y);
        to_update.x = cur_x;
        to_update.y = cur_y;
        to_update.q = key == rocky::RockyKey::Minus ? -1: 1;
        computer.init_charge(to_update);
        return true;
    }
    return false;
}
