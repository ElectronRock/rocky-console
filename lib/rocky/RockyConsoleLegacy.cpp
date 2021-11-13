#include "RockyConsoleLegacy.h"

namespace rocky
{
    void RockyConsoleLegacy::Initialize()
    {
    }

    void RockyConsoleLegacy::Destroy()
    {
    }

    void RockyConsoleLegacy::ShowCursor()
    {
    }

    void RockyConsoleLegacy::HideCursor()
    {
    }

    bool RockyConsoleLegacy::GoToXY(unsigned x, unsigned y)
    {
        return false;
    }

    bool RockyConsoleLegacy::ObtainXY(unsigned& x, unsigned& y)
    {
        return false;
    }

    bool RockyConsoleLegacy::ObtainMaxXY(unsigned& x, unsigned& y)
    {
        return false;
    }

    bool RockyConsoleLegacy::Clear()
    {
        return false;
    }

    bool RockyConsoleLegacy::SetTest(const char* format, ...)
    {
        return false;
    }

    bool RockyConsoleLegacy::IsKeyPressed()
    {
        return false;
    }

    RockyKey RockyConsoleLegacy::GetKey()
    {
        return RockyKey::Count;
    }

    bool RockyConsoleLegacy::InitColor(unsigned index, RockyColor back, RockyColor text)
    {
        return false;
    }

    bool RockyConsoleLegacy::SetColor(RockyColor back, RockyColor text)
    {
        return false;
    }

    bool RockyConsoleLegacy::SetColor(unsigned index)
    {
        return false;
    }

}
