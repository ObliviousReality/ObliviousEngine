#include "oepch.h"

#include "Input.h"

#ifdef OE_PLATFORM_WINDOWS
#include "Platforms/Win/WinInput.h"
#endif // OE_PLATFORM_WINDOWS

namespace OE
{
    Scope<Input> Input::instance = Input::Create();

    Scope<Input> Input::Create()
    {
#ifdef OE_PLATFORM_WINDOWS
        return CreateScope<WinInput>();
#else
        OE_CORE_ASSERT(false, "UNKNOWN PLATFORM");
        return nullptr;
#endif // OE_PLATFORM_WINDOWS
    }
} // namespace OE
