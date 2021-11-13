#include "RockyConsoleFactory.h"

#include <cassert>
#include "stdexcept"
#include "rocky/RockyConsoleNix.h"
#include "rocky/RockyConsoleWin.h"
#include "rocky/RockyConsoleLegacy.h"

namespace rocky
{
     static bool IsInit = false;
     static void AssertLibraryNotInitialized()
     {
         if (IsInit)
         {
             assert(false && "RockyConsole: The library had already been initialized");
             throw std::runtime_error("RockyConsole: The library had already been initialized");
         }
     }
    
    IRockyConsole* Create()
    {
        AssertLibraryNotInitialized();
        IsInit = true;
#if defined(ROCKY_WIN)
        return new RockyConsoleWin;
#else
        return new RockyConsoleNix;
#endif
    }

    IRockyConsole* CreateLegacy()
    {
        AssertLibraryNotInitialized();
        IsInit = true;
        return new RockyConsoleLegacy;
    }

}
