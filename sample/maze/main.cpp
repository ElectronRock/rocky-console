/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>
#include "MapMaker.h"
#include "FinderLeeRefined.h"
#include "rocky/IRockyConsole.h"
#include "rocky/RockyConsoleFactory.h"

static constexpr int ColorField = 0;
static constexpr int ColorWall = 1;
static constexpr int ColorPoint = 2;
static constexpr int ColorTrace = 3;
static constexpr int ColorWaveFront = 4;
static constexpr int ColorWave = 5;
static constexpr int FieldPadding = 3;
static constexpr int TitleX = 3;
static constexpr char CharWall = '#';
static constexpr char CharField = ' ';
static constexpr char CharPoint = '@';
static constexpr int TitleY = 1;
static int FieldX, FieldY; // top-left corner
static int FieldWidth, FieldHeight;
static int PointX, PointY;

std::pair<int, int> ConvtEnum(EntityType input)
{
    switch (input) {
    case EntityType::Field: return { ' ' , ColorField };
    case EntityType::Wall: return { '#', ColorWall };
    }
}

static void InitColors(rocky::IRockyConsole* console) 
{
    console->InitColor(ColorTrace, rocky::RockyColor::Red, rocky::RockyColor::Red);
    console->InitColor(ColorWaveFront, rocky::RockyColor::Cyan, rocky::RockyColor::Cyan);
    console->InitColor(ColorWave, rocky::RockyColor::White, rocky::RockyColor::White);

    console->InitColor(ColorWall, rocky::RockyColor::Black, rocky::RockyColor::Blue);
    console->InitColor(ColorField, rocky::RockyColor::Green, rocky::RockyColor::Green);
    console->InitColor(ColorPoint, rocky::RockyColor::Red, rocky::RockyColor::Green);
}

static void CharAt(rocky::IRockyConsole* console, int ch, int color, int x, int y)
{
    console->GoToXY(x, y);
    console->SetColor(color);
    console->SetText("%c", ch);
}

static void InitialDraw(rocky::IRockyConsole* console, const MapMaker::TMap& map)
{
    console->Clear();
    console->GoToXY(TitleX, TitleY);
    console->SetText("Use arrows to move point, use Esc to exit.");
    int i, j;
    for (i = 0; i < FieldWidth; ++i)
    {
        for (j = 0; j < FieldHeight; ++j)
        {
            if (i == 0 || i == FieldWidth - 1 || j == 0 || j == FieldHeight - 1)
            {
                CharAt(console, CharWall, ColorWall, FieldX + i, FieldY + j);
                continue;
            }
            auto p = ConvtEnum(map[i][j]);
            CharAt(console, p.first, p.second, FieldX + i, FieldY + j);
            if (p.first != CharWall) 
			{
                PointX = FieldX + i; PointY = FieldY + j;
            }
        }
    }
    CharAt(console, CharPoint, ColorPoint, PointX, PointY);
}

static void DrawWave(rocky::IRockyConsole* console, const Path::FinderLeeRefined::TWaveMap& map, const Path::FinderLeeRefined::TWaveMap& prevMap, unsigned curWaveIndex)
{
    for (unsigned i = 0; i < map.size(); ++i) 
    {
        for (unsigned j = 0; j < map.front().size(); ++j) 
        {
            if (prevMap.empty() || map[i][j] != prevMap[i][j])
            {
                if (map[i][j] > 0) 
                {
                    auto color = curWaveIndex == map[i][j] ? ColorWaveFront : ColorWave;
                    CharAt(console, CharField, ColorPoint, i + FieldX, j + FieldY);
                }
            }
        }
    }
}

static void Draw(rocky::IRockyConsole* console, const Path::IFinder::TPath& path)
{
    for (auto v : path)
        CharAt(console, ' ', ColorTrace, v.x + FieldX, v.y + FieldY);

    if (!path.empty())
    {
        auto&& point = path.back();
        PointY = point.y + FieldY;
        PointX = point.x + FieldX;
    }

    CharAt(console, CharPoint, ColorPoint, PointX, PointY);
}

static void FlushPath(rocky::IRockyConsole* console, const Path::IFinder::TPath& path)
{
    for (auto v : path)
        CharAt(console, ' ', ColorField, v.x + FieldX, v.y + FieldY);
}

int main(int argc, char* argv[])
{
    auto* console = rocky::Create();

    int quit = 0;
    unsigned max_x, max_y;

    console->Initialize();
    console->HideCursor();

    InitColors(console);

    // calculate size of field
    console->ObtainMaxXY(max_x, max_y);
    FieldX = FieldPadding + TitleY + 1;
    FieldY = FieldPadding;
    FieldWidth = max_x - FieldX - FieldPadding;
    FieldHeight = max_y - FieldY - FieldPadding;
    assert(FieldWidth > 2);
    assert(FieldHeight > 2);

    auto map = MapMaker::Make(FieldWidth, FieldHeight);

    InitialDraw(console, map);
    Path::FinderLeeRefined::TWaveMap prevMap;
    unsigned curWaveIndex = 0;
    Path::FinderLeeRefined finder(
        [&](const Path::FinderLeeRefined::TWaveMap& map) mutable
        {
            DrawWave(console, map, prevMap, curWaveIndex);
            prevMap = map;
            ++curWaveIndex;
            std::this_thread::sleep_for(std::chrono::microseconds(50000));
        }
	);

    auto&& path = finder.Find(Path::Vector2{ PointX - FieldX, PointY - FieldY }, 
		Path::Vector2{ (int)max_x / 2, (int)max_y / 2 }, map);

    Draw(console, path);
	
	char c;
    std::cin >> c;
	//console->Clear();
    console->Destroy();

    return 0;
}