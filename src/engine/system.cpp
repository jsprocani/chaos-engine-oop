#include "engine/logger.hpp"
#include "engine/system.hpp"
#include "core/system.h"
#include <iostream>

static engine::logger log{"SYSTEM"};

int engine::system::init() { return Core_Init(); }
void engine::system::exit() { Core_Exit(); }
void engine::system::delay(const uint ms) { Core_Delay(ms); }
void engine::system::sleep(const float s) { Core_Sleep(s); }

void engine::system::clamp_time(const float dt = 0.05f) {
    if (delta_time > dt) delta_time = dt;
}

void engine::system::limit_time() const {
    if (target_time > 0.0) {
        if (const double elapsed = dt_clock.elapsed(); elapsed < target_time) {
            sleep(static_cast<float>(target_time - elapsed));
        }
    }
}

void engine::system::update_clock() {
    limit_time();
    if (delta_time == 0.0) {
        delta_time = dt_clock.restart();
    } else {
        prev_delta_time = delta_time;
        delta_time = smoothing * prev_delta_time + (1 - smoothing) * dt_clock.restart();
    }
    clamp_time();
}

void engine::system::reset_timer() { dt_clock.reset(); }

[[nodiscard]] float engine::system::get_time() const { return static_cast<float>(delta_time); }

void engine::system::set_fps(const uint fps) {
    if (fps == 0) {
        target_time = 0.0;
    } else {
        target_time = 1.0 / fps;
        log.info("FPS Limiter set to %d", fps);
    }
}

engine::system::system(const float fps, const float smooth)
    : dt_clock(clock()), delta_time(0.0), prev_delta_time(0.0), target_time(1.0 / fps), smoothing(smooth) {
    log_system::init(LOG_INFO, true);
    if (init() < 0) {
        log.error("Engine initialization failed.");
        std::exit(EXIT_FAILURE);
    }
    log.ok("Engine initialized.");
}

engine::system::system() : system(60.0, 0.0) {}

engine::system::~system() {
    log.info("Engine shutting down.");
    exit();
}