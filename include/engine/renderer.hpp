#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <optional>
#include "window.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "core/renderer.h"
#include "core/utils.h"

namespace engine {
    class renderer {
        Core_Renderer handle;
        color draw_color = colors::WHITE;
        logger log{"RENDER"};
        template <typename T>
        int draw_rect_impl(const T x, const T y, const T w, const T h, const bool fill) {
            if constexpr (std::is_same_v<T, int>)
                return Core_DrawRect(static_cast<int>(x), static_cast<int>(y),
                                     static_cast<int>(w), static_cast<int>(h),
                                     fill);
            else if constexpr (std::is_floating_point_v<T>)
                return Core_DrawRectF(static_cast<float>(x), static_cast<float>(y),
                                      static_cast<float>(w), static_cast<float>(h),
                                      fill);
            else return WARNING;
        }
        template <typename T>
        int draw_rects_impl(const T *rects, const int count, const bool fill) {
            if constexpr (std::is_same_v<T, int>)
                return Core_DrawRects(reinterpret_cast<const int*>(rects), count, fill);
            else if constexpr (std::is_floating_point_v<T>)
                return Core_DrawRectsF(reinterpret_cast<const float*>(rects), count, fill);
            else return WARNING;
        }
        template <typename T>
        int draw_circle_impl(const T x, const T y, const T radius, const bool fill) {
            if constexpr (std::is_same_v<T, int>)
                return Core_DrawCircle(static_cast<int>(x), static_cast<int>(y),
                                       static_cast<int>(radius), fill);
            else if constexpr (std::is_floating_point_v<T>)
                return Core_DrawCircleF(static_cast<float>(x), static_cast<float>(y),
                                        static_cast<float>(radius), fill);
            else return WARNING;
        }
    public:
        explicit renderer(const window& window, uint flags = RENDER_FLAGS);
        ~renderer();
        renderer(const renderer&) = delete;
        renderer& operator=(const renderer&) = delete;
        void activate() const;
        void present() const;
        void clear(const color &c = colors::BLACK) const;
        int set_draw_color(uchar r, uchar g, uchar b, uchar a);
        int set_draw_color(const color& c);
        template <typename T>
        int draw(const T x, const T y, const T w, const T h, const bool fill, const std::optional<color>& c = std::nullopt) {
            if (c.has_value()) set_draw_color(c.value());
            return draw_rect_impl(x, y, w, h, fill);
        }
        template <typename T>
        int draw(const d2::rect<T>& rect, const bool fill = false, const std::optional<color>& c = std::nullopt) {
            if (c.has_value()) set_draw_color(c.value());
            return draw_rect_impl(rect.x, rect.y, rect.w, rect.h, fill);
        }
        template <typename T>
        int draw(const vec2<T>& pos, const vec2<T>& size, const bool fill = false, const std::optional<color>& c = std::nullopt) {
            if (c.has_value()) set_draw_color(c.value());
            return draw_rect_impl(pos.x, pos.y, size.x, size.y, fill);
        }
        template <typename T>
        int draw(const T x, const T y, const T radius, const bool fill = false, const std::optional<color>& c = std::nullopt) {
            if (c.has_value()) set_draw_color(c.value());
            return draw_circle_impl(x, y, radius, fill);
        }
        template <typename T>
        int draw(const d2::circle<T>& circ, const bool fill = false, const std::optional<color>& c = std::nullopt) {
            if (c.has_value()) set_draw_color(c.value());
            return draw_circle_impl(circ.x, circ.y, circ.radius, fill);
        }
        template <typename T>
        int draw_rects(const vec2<T>* data, const int count, const bool fill = false, const std::optional<color>& c = std::nullopt) {
            if (c.has_value()) set_draw_color(c.value());
            return draw_rects_impl(reinterpret_cast<const T*>(data), count, fill);
        }
    };
}

#endif //ENGINE_RENDERER_HPP