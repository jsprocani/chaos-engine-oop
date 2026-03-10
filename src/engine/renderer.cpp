#include "engine/renderer.hpp"

void engine::renderer::activate() const { Core_SetRenderer(handle); }
void engine::renderer::present() const { activate(); Core_Present(); }

engine::renderer::renderer(const window& window, const uint flags) {
    int status = SUCCESS;
    handle = Core_CreateRenderer(window.handle, flags, &status);
    if (!handle || status != SUCCESS) {
        log.error("Failed to create renderer instance.");
        std::exit(EXIT_FAILURE);
    }
    log.ok("Renderer instance initialized.");
}

engine::renderer::~renderer() {
    if (handle) {
        Core_DestroyRenderer(handle);
        log.info("Renderer instance destroyed.");
    }
}

void engine::renderer::clear(const color &c) const {
    const bool color_changed = c.r != draw_color.r || c.g != draw_color.g || c.b != draw_color.b || c.a != draw_color.a;
    if (color_changed) Core_SetDrawColor(c.r, c.g, c.b, c.a);
    Core_Clear();
    if (color_changed) Core_SetDrawColor(draw_color.r, draw_color.g, draw_color.b, draw_color.a);
}

int engine::renderer::set_draw_color(const uchar r, const uchar g, const uchar b, const uchar a = 255) {
    if (r == draw_color.r && g == draw_color.g && b == draw_color.b && a == draw_color.a) return SUCCESS;
    draw_color = color(r, g, b, a);
    return Core_SetDrawColor(r, g, b, a);
}

int engine::renderer::set_draw_color(const color& c) {
    return set_draw_color(c.r, c.g, c.b, c.a);
}
