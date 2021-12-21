#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>
#include "MapMaker.h"
#include "FinderLeeRefined.h"
#include "FinderLee.h"
#include "rocky/IRockyConsole.h"
#include "rocky/RockyConsoleFactory.h"


class Application {
public:
    enum FinderType {
        Lee,
        RefinedLee,
        NaiveLee
    };

    Application(rocky::IRockyConsole* console, const MapMaker::TMap& map) : m_console(console), m_map(map) {};
    ~Application() = default;

    void Init();
    void CreateFinder();
    void Process();

    static void DrawWave(rocky::IRockyConsole* console, const Path::FinderLeeRefined::TWaveMap& map, const Path::FinderLeeRefined::TWaveMap& prevMap, unsigned curWaveIndex);

private:
    static std::pair<int, int> ConvtEnum(EntityType input);
    static void InitColors(rocky::IRockyConsole* console);
    static void CharAt(rocky::IRockyConsole* console, int ch, int color, int x, int y);
    static void InitialDraw(rocky::IRockyConsole* console, const MapMaker::TMap& map);
    static void Draw(rocky::IRockyConsole* console, const Path::IFinder::TPath& path);
    static void FlushPath(rocky::IRockyConsole* console, const Path::IFinder::TPath& path);
    static void CalculateSize(unsigned max_x, unsigned max_y);

    rocky::IRockyConsole* m_console;
    const MapMaker::TMap& m_map;

    static int FieldX, FieldY; // top-left corner
    static int FieldWidth, FieldHeight;
    static int PointX, PointY;

    FinderType finder;
};