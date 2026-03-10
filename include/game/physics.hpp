#ifndef GAME_PHYSICS_HPP
#define GAME_PHYSICS_HPP

#include "entity.hpp"
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

namespace game {
    class physics {
    public:
        static void split_ball(const ball* victim, std::vector<std::unique_ptr<entity>>& new_entities) {
            float new_r = victim->get_radius() / 2.0f;
            if (new_r < 5.0f) return;
            const engine::vec2 pos = victim->get_pos();
            const engine::vec2 vel = victim->get_vel();
            engine::vec2 offset = {-vel.y, vel.x};
            if (const float len = std::sqrt(offset.x*offset.x + offset.y*offset.y); len > 0) {
                offset = offset / len * (new_r + 2.0f);
            }
            new_entities.push_back(std::make_unique<ball>(pos.x + offset.x, pos.y + offset.y, new_r, vel + offset * 2.0f, victim->get_color()));
            new_entities.push_back(std::make_unique<ball>(pos.x - offset.x, pos.y - offset.y, new_r, vel - offset * 2.0f, victim->get_color()));
        }
        static void solve(entity& a, entity& b, std::vector<std::unique_ptr<entity>>& new_queue) {
            const entity_type type_a = a.get_type();
            const entity_type type_b = b.get_type();
            if (type_a == entity_type::BALL && type_b == entity_type::BALL) {
                auto* b1 = static_cast<ball*>(&a);
                auto* b2 = static_cast<ball*>(&b);
                const engine::vec2 dir = b1->get_pos() - b2->get_pos();
                const float dist_sq = dir.x*dir.x + dir.y*dir.y;
                if (const float r_sum = b1->get_radius() + b2->get_radius(); dist_sq < r_sum * r_sum) {
                    float dist = std::sqrt(dist_sq);
                    if (dist == 0) { dist = 0.01f; }
                    const float overlap = r_sum - dist;
                    const engine::vec2 correction = dir / dist * (overlap * 0.5f);
                    b1->set_pos(b1->get_pos() + correction);
                    b2->set_pos(b2->get_pos() - correction);
                    if (b1->get_radius() > b2->get_radius() * 1.2f) {
                        b1->destroy(); split_ball(b1, new_queue);
                    } else if (b2->get_radius() > b1->get_radius() * 1.2f) {
                        b2->destroy(); split_ball(b2, new_queue);
                    } else {
                        const engine::vec2 n = dir / dist;
                        if (const engine::vec2 v_rel = b1->get_vel() - b2->get_vel(); v_rel.dot(n) < 0) {
                             const float impulse = v_rel.dot(n);
                             b1->set_vel(b1->get_vel() - n * impulse);
                             b2->set_vel(b2->get_vel() + n * impulse);
                        }
                    }
                }
            }
            else if (type_a == entity_type::BOX && type_b == entity_type::BOX) {
                auto* box1 = static_cast<box*>(&a);
                auto* box2 = static_cast<box*>(&b);
                const auto r1 = box1->get_rect();
                const auto r2 = box2->get_rect();
                if (r1.intersects(r2)) {
                    const float overlap_x = std::min(r1.x + r1.w, r2.x + r2.w) - std::max(r1.x, r2.x);
                    const float overlap_y = std::min(r1.y + r1.h, r2.y + r2.h) - std::max(r1.y, r2.y);
                    if (overlap_x < overlap_y) {
                        const float separation = overlap_x * 0.5f;
                        if (r1.x < r2.x) {
                            box1->set_pos({box1->get_pos().x - separation, box1->get_pos().y});
                            box2->set_pos({box2->get_pos().x + separation, box2->get_pos().y});
                        } else {
                            box1->set_pos({box1->get_pos().x + separation, box1->get_pos().y});
                            box2->set_pos({box2->get_pos().x - separation, box2->get_pos().y});
                        }
                        box1->set_vel({-box1->get_vel().x, box1->get_vel().y});
                        box2->set_vel({-box2->get_vel().x, box2->get_vel().y});
                    } else {
                        const float separation = overlap_y * 0.5f;
                        if (r1.y < r2.y) {
                            box1->set_pos({box1->get_pos().x, box1->get_pos().y - separation});
                            box2->set_pos({box2->get_pos().x, box2->get_pos().y + separation});
                        } else {
                            box1->set_pos({box1->get_pos().x, box1->get_pos().y + separation});
                            box2->set_pos({box2->get_pos().x, box2->get_pos().y - separation});
                        }
                        box1->set_vel({box1->get_vel().x, -box1->get_vel().y});
                        box2->set_vel({box2->get_vel().x, -box2->get_vel().y});
                    }
                }
            }
            else {
                const auto ba = static_cast<ball*>(type_a == entity_type::BALL ? &a : &b);
                const auto bo = static_cast<box*> (type_a == entity_type::BOX  ? &a : &b);
                const engine::d2::rect<float> r = bo->get_rect();
                const engine::vec2<float> c = ba->get_pos();
                const float closest_x = std::clamp(c.x, r.x, r.x + r.w);
                const float closest_y = std::clamp(c.y, r.y, r.y + r.h);
                const float dx = c.x - closest_x;
                const float dy = c.y - closest_y;
                const float dist_sq = dx * dx + dy * dy;
                if (const float radius = ba->get_radius(); dist_sq < radius * radius) {
                    const float dist = std::sqrt(dist_sq);
                    engine::vec2<float> normal;
                    float penetration;
                    if (dist < 0.0001f) {
                        float d_left = std::abs(c.x - r.x);
                        float d_right = std::abs(c.x - (r.x + r.w));
                        float d_top = std::abs(c.y - r.y);
                        float d_bottom = std::abs(c.y - (r.y + r.h));
                        const float min_dist = std::min({d_left, d_right, d_top, d_bottom});
                        if (min_dist == d_left) normal = {-1, 0};
                        if (min_dist == d_right) normal = {1, 0};
                        if (min_dist == d_top) normal = {0, -1};
                        if (min_dist == d_bottom) normal = {0, 1};
                        penetration = radius + min_dist;
                    } else {
                        normal = {dx / dist, dy / dist};
                        penetration = radius - dist;
                    }
                    ba->set_pos(ba->get_pos() + normal * penetration);
                    const engine::vec2 v = ba->get_vel();
                    if (const float dot = v.dot(normal); dot < 0) {
                        ba->set_vel(v - normal * (2.0f * dot));
                    }
                }
            }
        }
    };
}

#endif // GAME_PHYSICS_HPP