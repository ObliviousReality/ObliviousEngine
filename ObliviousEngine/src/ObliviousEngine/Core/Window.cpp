#include "oepch.h"

#include "Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platforms/Win/WinWindow.h"
#endif // PLATFORM_WINDOWS

namespace OE
{
    Scope<Window> Window::WindowCreate(const Properties & props)
    {
#ifdef PLATFORM_WINDOWS
        return CreateScope<WinWindow>(props);
#else
        CORE_ASSERT(false, "UNKNOWN PLATFORM");
        return nullptr;
#endif // PLATFORM_WINDOWS
    }
} // namespace OE
