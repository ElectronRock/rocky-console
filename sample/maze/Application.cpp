#include "Application.h"
#include "FinderLee.h"
#include "FinderLeeRefined.h"
#include <chrono>
#include <thread>
#include <cassert>

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

void Application::Init() 
{
    InitColors();
    InitMap();
    InitialDraw();
}

void Application::CreateFinder(FinderType type)
{
    if (type == FinderType::Lee || type == FinderType::RefinedLee)
    {
        auto&& callback = [&](const Path::FinderLeeRefined::TWaveMap& map, unsigned waveIndex) mutable
        {
            DrawWave(map, waveIndex);
            m_prevMap = map;
            std::this_thread::sleep_for(std::chrono::microseconds(50000));
        };

        m_pathFinder = type == FinderType::Lee ? (Path::IFinder*)new Path::FinderLee(std::move(callback)) : (Path::IFinder*)new Path::FinderLeeRefined(std::move(callback));
    }
    else if (type == FinderType::AStar) 
    {
        // TODO: create finder
    }
}

void Application::Run() 
{
    auto&& path = m_pathFinder->Find(Path::Vector2{ PointX - FieldX, PointY - FieldY },
        Path::Vector2{ (int)max_x / 2, (int)max_y / 2 }, m_map);

    Draw(path);
}

void Application::DrawWave(const Path::FinderLeeBase::TWaveMap& map, unsigned int curWaveIndex) 
{
    for (unsigned i = 0; i < map.size(); ++i)
    {
        for (unsigned j = 0; j < map.front().size(); ++j)
        {
            if (m_prevMap.empty() || map[i][j] != m_prevMap[i][j] || map[i][j] < curWaveIndex)
            {
                if (map[i][j] > 0 )
                {
                    auto color = curWaveIndex == map[i][j] ? ColorWaveFront : ColorWave;
                    CharAt(CharField, color, i + FieldX, j + FieldY);
                }
            }
        }
    }
}

std::pair<int, int> Application::ConvtEnum(EntityType input) 
{
    switch (input) {
        case EntityType::Field: return { ' ' , ColorField };
        case EntityType::Wall: return { '#', ColorWall };
    }
}

void Application::InitColors() 
{
    m_console->InitColor(ColorTrace, rocky::RockyColor::Red, rocky::RockyColor::Red);
    m_console->InitColor(ColorWaveFront, rocky::RockyColor::Cyan, rocky::RockyColor::Cyan);
    m_console->InitColor(ColorWave, rocky::RockyColor::White, rocky::RockyColor::White);

    m_console->InitColor(ColorWall, rocky::RockyColor::Black, rocky::RockyColor::Blue);
    m_console->InitColor(ColorField, rocky::RockyColor::Green, rocky::RockyColor::Green);
    m_console->InitColor(ColorPoint, rocky::RockyColor::Red, rocky::RockyColor::Green);
}

void Application::CharAt(int ch, int color, int x, int y) 
{
    m_console->GoToXY(x, y);
    m_console->SetColor(color);
    m_console->SetText("%c", ch);
}

void Application::InitialDraw() 
{
    m_console->Clear();
    m_console->GoToXY(TitleX, TitleY);
    int i, j;
    for (i = 0; i < FieldWidth; ++i)
    {
        for (j = 0; j < FieldHeight; ++j)
        {
            if (i == 0 || i == FieldWidth - 1 || j == 0 || j == FieldHeight - 1)
            {
                CharAt(CharWall, ColorWall, FieldX + i, FieldY + j);
                continue;
            }
            auto p = ConvtEnum(m_map[i][j]);
            CharAt(p.first, p.second, FieldX + i, FieldY + j);
            if (p.first != CharWall)
            {
                PointX = FieldX + i; PointY = FieldY + j;
            }
        }
    }
    CharAt(CharPoint, ColorPoint, PointX, PointY);
}

void Application::Draw(const Path::IFinder::TPath& path) 
{
    for (auto v : path)
        CharAt(' ', ColorTrace, v.x + FieldX, v.y + FieldY);

    if (!path.empty())
    {
        auto&& point = path.back();
        PointY = point.y + FieldY;
        PointX = point.x + FieldX;
    }

    CharAt(CharPoint, ColorPoint, PointX, PointY);
}

void Application::FlushPath(const Path::IFinder::TPath& path) 
{
    for (auto v : path)
        CharAt(' ', ColorField, v.x + FieldX, v.y + FieldY);
}

void Application::InitMap() 
{
    // calculate size of field
    m_console->ObtainMaxXY(max_x, max_y);
    FieldX = FieldPadding + TitleY + 1;
    FieldY = FieldPadding;
    FieldWidth = max_x - FieldX - FieldPadding;
    FieldHeight = max_y - FieldY - FieldPadding;
    assert(FieldWidth > 2);
    assert(FieldHeight > 2);

    m_map = MapMaker::Make(FieldWidth, FieldHeight);
}
