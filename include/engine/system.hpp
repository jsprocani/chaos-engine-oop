#ifndef ENGINE_SYSTEM_HPP
#define ENGINE_SYSTEM_HPP

#include "timer.hpp"

namespace engine {
    class system {
        clock dt_clock;
        double delta_time;
        double prev_delta_time;
        double target_time;
        double smoothing;
    public:
        explicit system(float fps, float smooth);
        system();
        ~system();
        system(const system&) = delete;
        system& operator=(const system&) = delete;
        static system& get() {
            static system instance;
            return instance;
        }
        static int init();
        static void exit();
        static void delay(uint ms);
        static void sleep(float s);
        void clamp_time(float dt);
        void limit_time() const;
        void print_fps() const;
        void update_clock();
        void reset_timer();
        static bool is_active();
        [[nodiscard]] float get_time() const;
        void set_fps(uint fps);
    };
}

#endif //ENGINE_SYSTEM_HPP