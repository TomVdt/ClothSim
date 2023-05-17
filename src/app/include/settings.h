#pragma once

#include <imgui/imgui.h>

namespace Settings {
    #if defined(QWERTY)
    inline constexpr ImGuiKey FRONT(ImGuiKey_W);
    inline constexpr ImGuiKey BACK(ImGuiKey_S);
    inline constexpr ImGuiKey LEFT(ImGuiKey_A);
    inline constexpr ImGuiKey RIGHT(ImGuiKey_D);
    #elif defined(AZERTY)
    inline constexpr ImGuiKey FRONT(ImGuiKey_Z);
    inline constexpr ImGuiKey BACK(ImGuiKey_S);
    inline constexpr ImGuiKey LEFT(ImGuiKey_Q);
    inline constexpr ImGuiKey RIGHT(ImGuiKey_D);
    #else
    // Valid on all keyboard layouts
    inline constexpr ImGuiKey FRONT(ImGuiKey_UpArrow);
    inline constexpr ImGuiKey BACK(ImGuiKey_DownArrow);
    inline constexpr ImGuiKey LEFT(ImGuiKey_LeftArrow);
    inline constexpr ImGuiKey RIGHT(ImGuiKey_RightArrow);
    #endif

    inline constexpr ImGuiKey DOWN(ImGuiKey_LeftShift);
    inline constexpr ImGuiKey UP(ImGuiKey_Space);
}
