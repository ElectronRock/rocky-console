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

    bool RockyConsoleWin::InitColor(unsigned index, unsigned back, unsigned text)
    {
        return false;
    }

    bool RockyConsoleWin::SetColor(unsigned index)
    {
        return false;
    }

    bool RockyConsoleWin::SetColor(unsigned back, unsigned text)
    {
        return false;
    }

}

#endif
