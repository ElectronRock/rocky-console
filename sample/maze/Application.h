#include "FinderLeeBase.h"
#include "rocky/IRockyConsole.h"
#include "MapMaker.h"

class Application final
{
public:
    enum FinderType 
    {
        Lee,
        RefinedLee,
        AStar,
    };

    Application(rocky::IRockyConsole* console) 
        : m_console(console)
    { };

    ~Application() = default;

    void Init();
    void CreateFinder(FinderType type);
    void Run();

private:

    // For Lee's algo
    void DrawWave(const Path::FinderLeeBase::TWaveMap& map, unsigned curWaveIndex);

    std::pair<int, int> ConvtEnum(EntityType input);
    void InitColors();
    void CharAt(int ch, int color, int x, int y);
    void InitialDraw();
    void Draw(const Path::IFinder::TPath& path);
    void FlushPath(const Path::IFinder::TPath& path);
    void InitMap();

    Path::FinderLeeBase::TWaveMap m_prevMap;

    rocky::IRockyConsole* m_console;
    MapMaker::TMap m_map;

    int FieldX, FieldY; // top-left corner
    int FieldWidth, FieldHeight;
    int PointX, PointY;
    unsigned max_x, max_y;

    Path::IFinder* m_pathFinder = nullptr;
};