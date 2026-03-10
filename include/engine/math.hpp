#ifndef ENGINE_MATH_HPP
#define ENGINE_MATH_HPP

#include <cmath>
#include <numbers>

template <typename T>
constexpr T PI_v = std::numbers::pi_v<T>;

namespace engine {
    template <typename T>
    struct vec2 {
        T x, y;
        constexpr vec2(T x = 0, T y = 0) : x(x), y(y) {}
        constexpr vec2 operator+(const vec2& v) const { return {x + v.x, y + v.y}; }
        constexpr vec2 operator-(const vec2& v) const { return {x - v.x, y - v.y}; }
        constexpr vec2 operator*(const vec2& v) const { return {x * v.x, y * v.y}; }
        constexpr vec2 operator/(const vec2& v) const { return {x / v.x, y / v.y}; }
        constexpr vec2 operator*(T s) const { return {x * s, y * s}; }
        constexpr vec2 operator/(T s) const { return {x / s, y / s}; }
        constexpr vec2 operator-() const { return {-x, -y}; }
        vec2& operator+=(const vec2& v) { x += v.x; y += v.y; return *this; }
        vec2& operator-=(const vec2& v) { x -= v.x; y -= v.y; return *this; }
        vec2& operator*=(const vec2& v) { x *= v.x; y *= v.y; return *this; }
        vec2& operator/=(const vec2& v) { x /= v.x; y /= v.y; return *this; }
        vec2& operator*=(T s) { x *= s; y *= s; return *this; }
        vec2& operator/=(T s) { x /= s; y /= s; return *this; }
        bool operator==(const vec2& v) const { return x == v.x && y == v.y; }
        bool operator!=(const vec2& v) const { return x != v.x || y != v.y; }
        T dot(const vec2& v) const { return x * v.x + y * v.y; }
        T distance_sq(const vec2& p) const noexcept {
            const T dx = p.x - x;
            const T dy = p.y - y;
            return dx * dx + dy * dy;
        }
        T distance(const vec2& p) const noexcept {
            return std::sqrt(distance_sq(p));
        }
    };
}

#endif //ENGINE_MATH_HPP