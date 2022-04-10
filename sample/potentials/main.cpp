/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#include "rocky/IRockyConsole.h"
#include "rocky/RockyConsoleFactory.h"


int main(int argc, char* argv[])
{
    auto* console = rocky::Create();

    console->Initialize();
    //console->HideCursor();

    console->Destroy();

    return 0;
}