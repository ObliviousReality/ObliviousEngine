#include "oepch.h"

#include "Input.h"

#ifdef PLATFORM_WINDOWS
#include "Platforms/Win/WinInput.h"
#endif // PLATFORM_WINDOWS

namespace OE
{
    Scope<Input> Input::instance = Input::Create();

    Scope<Input> Input::Create()
    {
#ifdef PLATFORM_WINDOWS
        return CreateScope<WinInput>();
#else
        CORE_ASSERT(false, "UNKNOWN PLATFORM");
        return nullptr;
#endif // PLATFORM_WINDOWS
    }
} // namespace OE
