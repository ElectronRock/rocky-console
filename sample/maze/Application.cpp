#include "Application.h"

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


void Application::DrawWave(rocky::IRockyConsole* console, const Path::FinderLeeBase::TWaveMap& map,
                           const Path::FinderLeeBase::TWaveMap& prevMap, unsigned int curWaveIndex) {
    for (unsigned i = 0; i < map.size(); ++i)
    {
        for (unsigned j = 0; j < map.front().size(); ++j)
        {
            if (prevMap.empty() || map[i][j] != prevMap[i][j] || map[i][j] < curWaveIndex)// take to account waves from previous simulation step
            {
                if (map[i][j] > 0 )
                {
                    auto color = curWaveIndex == map[i][j] ? ColorWaveFront : ColorWave;
                    CharAt(console, CharField, color, i + FieldX, j + FieldY);
                }
            }
        }
    }
}

std::pair<int, int> Application::ConvtEnum(EntityType input) {
    switch (input) {
        case EntityType::Field: return { ' ' , ColorField };
        case EntityType::Wall: return { '#', ColorWall };
    }
}

void Application::InitColors(rocky::IRockyConsole* console) {
    console->InitColor(ColorTrace, rocky::RockyColor::Red, rocky::RockyColor::Red);
    console->InitColor(ColorWaveFront, rocky::RockyColor::Cyan, rocky::RockyColor::Cyan);
    console->InitColor(ColorWave, rocky::RockyColor::White, rocky::RockyColor::White);

    console->InitColor(ColorWall, rocky::RockyColor::Black, rocky::RockyColor::Blue);
    console->InitColor(ColorField, rocky::RockyColor::Green, rocky::RockyColor::Green);
    console->InitColor(ColorPoint, rocky::RockyColor::Red, rocky::RockyColor::Green);
}

void Application::CharAt(rocky::IRockyConsole* console, int ch, int color, int x, int y) {
    console->GoToXY(x, y);
    console->SetColor(color);
    console->SetText("%c", ch);
}

void Application::InitialDraw(rocky::IRockyConsole* console, const MapMaker::TMap& map) {
    console->Clear();
    console->GoToXY(TitleX, TitleY);
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

void Application::Draw(rocky::IRockyConsole* console, const Path::IFinder::TPath& path) {
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

void Application::FlushPath(rocky::IRockyConsole* console, const Path::IFinder::TPath& path) {
    for (auto v : path)
        CharAt(console, ' ', ColorField, v.x + FieldX, v.y + FieldY);
}

void Application::CalculateSize(unsigned max_x, unsigned max_y) {
    FieldX = FieldPadding + TitleY + 1;
    FieldY = FieldPadding;
    FieldWidth = max_x - FieldX - FieldPadding;
    FieldHeight = max_y - FieldY - FieldPadding;
    assert(FieldWidth > 2);
    assert(FieldHeight > 2);
}
