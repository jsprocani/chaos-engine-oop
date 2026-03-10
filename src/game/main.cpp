#include "game/engine.hpp"
#include "game/entity.hpp"
#include "game/physics.hpp"

#include <vector>
#include <memory>
#include <algorithm>

using namespace engine;
using namespace engine::colors;

constexpr int WIN_W = 1280;
constexpr int WIN_H = 720;
constexpr int BALL_COUNT = 10;
constexpr int BOX_COUNT = 2;
constexpr float FPS = 60.0f;
constexpr float SMOOTH = 0.1f;

int main(const int argc, char* argv[]) {
    (void)argc; (void)argv;
    random::init();
    engine::system engine(FPS, SMOOTH);
    const window win("CHAOS DEMO", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, WIN_W, WIN_H);
    renderer render(win);
    std::vector<std::unique_ptr<game::entity>> entities;
    for (int i = 0; i < BALL_COUNT; ++i) {
        float radius = random::range(30.0f, 60.0f);
        float x = random::range(radius + 10, WIN_W - radius - 10);
        float y = random::range(radius + 10, WIN_H - radius - 10);
        vec2 vel = {
            random::range(-400.f, 400.f),
            random::range(-400.f, 400.f)
        };
        entities.push_back(std::make_unique<game::ball>(
            x, y, radius, vel, random::random_color()
        ));
    }
    int boxes_spawned = 0;
    int attempts = 0;
    while (boxes_spawned < BOX_COUNT && attempts < 2000) {
        attempts++;
        float w = random::range(80.0f, 250.0f);
        float h = random::range(80.0f, 250.0f);
        float x = random::range(50.0f, WIN_W - w - 50.0f);
        float y = random::range(50.0f, WIN_H - h - 50.0f);
        game::box candidate(x, y, w, h, {0,0}, WHITE);
        bool collision = false;
        for (const auto& existing : entities) {
            if (existing->get_type() == game::entity_type::BOX) {
                const auto& other_box = static_cast<const game::box&>(*existing);
                d2::rect<float> expanded_rect = candidate.get_rect();
                expanded_rect.x -= 10; expanded_rect.y -= 10;
                expanded_rect.w += 20; expanded_rect.h += 20;
                if (expanded_rect.intersects(other_box.get_rect())) {
                    collision = true; break;
                }
            }
            else if (existing->get_type() == game::entity_type::BALL) {
                if (const auto& ball = static_cast<const game::ball&>(*existing); candidate.get_rect().contains(ball.get_pos())) { // Test grossier
                    collision = true; break;
                }
            }
        }
        if (!collision) {
            vec2 vel = {
                random::range(-80.f, 80.f),
                random::range(-80.f, 80.f)
            };
            entities.push_back(std::make_unique<game::box>(x, y, w, h, vel, WHITE));
            boxes_spawned++;
        }
    }
    bool running = true;
    event e{};
    render.clear(color(20, 20, 25));
    for (const auto& ent : entities) {
        ent->draw(render);
    }
    render.present();
    system::delay(500);
    engine.reset_timer();
    while (running) {
        while (input::poll(e)) {
            if (e.type == event_type::QUIT) running = false;
        }
        engine.update_clock();
        const float dt = engine.get_time();
        for (const auto& ent : entities) {
            ent->update(dt, win);
        }
        std::vector<std::unique_ptr<game::entity>> new_borns;
        for (size_t i = 0; i < entities.size(); ++i) {
            for (size_t j = i + 1; j < entities.size(); ++j) {
                if (!entities[i]->is_active() || !entities[j]->is_active()) continue;
                game::physics::solve(*entities[i], *entities[j], new_borns);
            }
        }
        if (!new_borns.empty()) {
            for (auto& new_ent : new_borns) {
                entities.push_back(std::move(new_ent));
            }
        }
        std::erase_if(entities, [](const auto& ent) {
            return !ent->is_active();
        });
        render.clear(color(20, 20, 25));
        for (const auto& ent : entities) {
            ent->draw(render);
        }
        render.present();
    }
    return 0;
}