#include "oepch.h"

#include "Window.h"

#ifdef OE_PLATFORM_WINDOWS
#include "Platforms/Win/WinWindow.h"
#endif // OE_PLATFORM_WINDOWS

namespace OE
{
    Scope<Window> Window::WindowCreate(const Properties & props)
    {
#ifdef OE_PLATFORM_WINDOWS
        return CreateScope<WinWindow>(props);
#else
        OE_CORE_ASSERT(false, "UNKNOWN PLATFORM");
        return nullptr;
#endif // OE_PLATFORM_WINDOWS
    }
} // namespace OE
