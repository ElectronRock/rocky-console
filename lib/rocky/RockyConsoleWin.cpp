#include "rocky/Foundation.h"
#if defined(ROCKY_WIN)
#include "RockyConsoleWin.h"

namespace rocky
{
    // place implementation here    
    void RockyConsoleWin::Initialize()
    {
    }

    void RockyConsoleWin::Destroy()
    {
    }

    void RockyConsoleWin::ShowCursor()
    {
    }

    void RockyConsoleWin::HideCursor()
    {
    }

    bool RockyConsoleWin::GoToXY(unsigned x, unsigned y)
    {
        return false;
    }

    bool RockyConsoleWin::ObtainXY(unsigned& x, unsigned& y)
    {
        return false;
    }

    bool RockyConsoleWin::ObtainMaxXY(unsigned& x, unsigned& y)
    {
        return false;
    }

    bool RockyConsoleWin::Clear()
    {
        return false;
    }

    bool RockyConsoleWin::SetTest(const char* format, ...)
    {
        return false;
    }

    bool RockyConsoleWin::IsKeyPressed()
    {
        return false;
    }

    RockyKey RockyConsoleWin::GetKey()
    {
        return RockyKey::Count;
    }

    bool RockyConsoleWin::InitColor(unsigned index, RockyColor back, RockyColor text)
    {
        return false;
    }

    bool RockyConsoleWin::SetColor(RockyColor back, RockyColor text)
    {
        return false;
    }

    bool RockyConsoleWin::SetColor(unsigned index)
    {
        return false;
    }

}

#endif
