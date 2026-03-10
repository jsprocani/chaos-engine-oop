#ifndef ENGINE_COLOR_HPP
#define ENGINE_COLOR_HPP

#include "core/types.h"

namespace engine {
    namespace colors {
        inline constexpr uint TRANSPARENT = 0x00000000;
        inline constexpr uint BLACK = 0x000000FF;
        inline constexpr uint WHITE = 0xFFFFFFFF;
        inline constexpr uint RED = 0xFF0000FF;
        inline constexpr uint GREEN = 0x00FF00FF;
        inline constexpr uint BLUE = 0x0000FFFF;
        inline constexpr uint YELLOW = 0xFFFF00FF;
        inline constexpr uint CYAN = 0x00FFFFFF;
        inline constexpr uint MAGENTA = 0xFF00FFFF;
    }
    struct color {
        uchar r, g, b, a;
        color(const uchar r = 0, const uchar g = 0, const uchar b = 0, const uchar a = 255) : r(r), g(g), b(b), a(a) {}
        color(const uint hex) {
            r = hex >> 24 & 0xFF;
            g = hex >> 16 & 0xFF;
            b = hex >> 8 & 0xFF;
            a = hex & 0xFF;
        }
    };
}

#endif //ENGINE_COLOR_HPP