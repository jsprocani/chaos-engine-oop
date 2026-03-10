#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "engine.hpp"

namespace game {
    enum class entity_type { BALL, BOX };
    class entity {
    protected:
        engine::vec2<float> position;
        engine::vec2<float> velocity;
        engine::color color;
        entity_type type;
        bool active = true;
    public:
        entity(const engine::vec2<float> pos, const engine::vec2<float> vel, const engine::color c, const entity_type t)
            : position(pos), velocity(vel), color(c), type(t) {}
        virtual ~entity() = default;
        virtual void update(float dt, const engine::window& win) = 0;
        virtual void draw(engine::renderer& renderer) = 0;
        [[nodiscard]] engine::vec2<float> get_pos() const { return position; }
        [[nodiscard]] engine::vec2<float> get_vel() const { return velocity; }
        [[nodiscard]] engine::color get_color() const { return color; }
        [[nodiscard]] entity_type get_type() const { return type; }
        [[nodiscard]] bool is_active() const { return active; }
        void set_pos(const engine::vec2<float>& p) { position = p; }
        void set_vel(const engine::vec2<float>& v) { velocity = v; }
        void destroy() { active = false; }
    };
    class ball : public entity {
        engine::d2::circle<float> shape;
    public:
        ball(float x, float y, const float radius, const engine::vec2<float> speed, engine::color c)
            : entity({x, y}, speed, c, entity_type::BALL), shape(x, y, radius) {}
        void update(const float dt, const engine::window& win) override {
            position += velocity * dt;
            shape.set(position.x, position.y);
            const auto w = static_cast<float>(win.get_width());
            const auto h = static_cast<float>(win.get_height());
            if (position.x < shape.radius) {
                position.x = shape.radius; velocity.x *= -1;
            } else if (position.x > w - shape.radius) {
                position.x = w - shape.radius; velocity.x *= -1;
            }
            if (position.y < shape.radius) {
                position.y = shape.radius; velocity.y *= -1;
            } else if (position.y > h - shape.radius) {
                position.y = h - shape.radius; velocity.y *= -1;
            }
        }
        void draw(engine::renderer& renderer) override {
            renderer.draw(shape, true, color);
            renderer.draw(shape, false, engine::colors::BLACK);
        }
        [[nodiscard]] float get_radius() const { return shape.radius; }
    };
    class box : public entity {
        engine::d2::rect<float> shape;
    public:
        box(float x, float y, const float w, const float h, const engine::vec2<float> speed, const engine::color c)
            : entity({x, y}, speed, c, entity_type::BOX), shape(x, y, w, h) {}
        void update(const float dt, const engine::window& win) override {
            position += velocity * dt;
            shape.set(position.x, position.y);
            const auto w_screen = static_cast<float>(win.get_width());
            const auto h_screen = static_cast<float>(win.get_height());
            if (position.x < 0) { position.x = 0; velocity.x *= -1; }
            else if (position.x + shape.w > w_screen) { position.x = w_screen - shape.w; velocity.x *= -1; }
            if (position.y < 0) { position.y = 0; velocity.y *= -1; }
            else if (position.y + shape.h > h_screen) { position.y = h_screen - shape.h; velocity.y *= -1; }
        }
        void draw(engine::renderer& renderer) override {
            renderer.draw(shape, true, color);
        }
        [[nodiscard]] engine::d2::rect<float> get_rect() const { return shape; }
    };
}

#endif //GAME_ENTITY_HPP