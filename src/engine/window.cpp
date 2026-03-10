#include "engine/window.hpp"
#include "core/utils.h"

engine::window::window(const std::string& title, const int x, const int y, const int w, const int h, const uint flags) :
    title(title), pos_x(x), pos_y(y), width(w), height(h){
    int status = SUCCESS;
    handle = Core_CreateWindow(title.c_str(), x, y, w, h, flags, &status);
    if (!handle || status != SUCCESS) {
        log.error("Failed to create window instance.");
        std::exit(EXIT_FAILURE);
    }
    log.ok("Window instance created.");
}

engine::window::~window() {
    if (handle) {
        Core_DestroyWindow(handle);
        log.info("Window instance destroyed.");
    }
}

engine::window& engine::window::operator=(window&& other) noexcept {
    if (this != &other) {
        if (handle) Core_DestroyWindow(handle);
        handle = other.handle;
        other.handle = nullptr;
        title = std::move(other.title);
        pos_x = other.pos_x;
        pos_y = other.pos_y;
        width = other.width;
        height = other.height;
    }
    return *this;
}

engine::window::window(window&& other) noexcept :
    handle(other.handle), title(std::move(other.title)),
    pos_x(other.pos_x), pos_y(other.pos_y),
    width(other.width), height(other.height) {
    other.handle = nullptr;
}
