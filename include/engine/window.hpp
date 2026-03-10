#ifndef ENGINE_WINDOW_HPP
#define ENGINE_WINDOW_HPP

#include "logger.hpp"
#include "core/window.h"

namespace engine {
    class window {
        friend class renderer;
        Core_Window handle;
        std::string title;
        int pos_x, pos_y;
        int width, height;
        logger log{"WINDOW"};
    public:
        window(const std::string& title, int x, int y, int w, int h, uint flags = WINDOW_FLAGS);
        ~window();
        window(const window&) = delete;
        window(window &&other) noexcept;
        window &operator=(window &&other) noexcept;
        [[nodiscard]] std::string get_title() const { return title; }
        [[nodiscard]] int get_pos_x() const { return pos_x; }
        [[nodiscard]] int get_pos_y() const { return pos_y; }
        [[nodiscard]] int get_width() const { return width; }
        [[nodiscard]] int get_height() const { return height; }
    };
}

#endif //ENGINE_WINDOW_HPP