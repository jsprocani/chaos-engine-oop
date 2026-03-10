#ifndef ENGINE_GEOMETRY_HPP
#define ENGINE_GEOMETRY_HPP

#include "math.hpp"

namespace engine::d2 {
    template <typename T>
    struct figure {
        virtual ~figure() = default;
        [[nodiscard]] virtual bool contains(const vec2<T>& p) const = 0;
        [[nodiscard]] virtual vec2<T> center() const = 0;
        virtual void move(T dx, T dy) = 0;
        virtual void set(T _x, T _y) = 0;
    };
    template <typename T>
    struct surface : figure<T> {
        [[nodiscard]] virtual T area() const = 0;
    };
    template <typename T>
    struct rect final : surface<T> {
        T x, y, w, h;
        rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
        rect(vec2<T> pos, vec2<T> size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
        void set(T _x, T _y) override { x = _x; y = _y; }
        bool contains(const vec2<T>& p) const override {
            return p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h;
        }
        vec2<T> center() const override { return {x + w / 2, y + h / 2}; }
        void move(T dx, T dy) override { x += dx; y += dy; }
        [[nodiscard]] T area() const override { return w * h; }
        bool intersects(const rect& o) const {
            return x < o.x + o.w && x + w > o.x && y < o.y + o.h && y + h > o.y;
        }
    };
    template <typename T>
    struct circle final : surface<T> {
        T x, y, radius;
        circle(T x, T y, T r) : x(x), y(y), radius(r) {}
        void set(T _x, T _y) override { x = _x; y = _y; }
        bool contains(const vec2<T>& p) const override {
            T dx = p.x - x;
            T dy = p.y - y;
            return dx * dx + dy * dy <= radius * radius;
        }
        vec2<T> center() const override { return {x, y}; }
        void move(T dx, T dy) override { x += dx; y += dy; }
        [[nodiscard]] T area() const override {
            return PI_v<double> * radius * radius;
        }
    };
}

#endif // ENGINE_GEOMETRY_HPP