#ifndef ENGINE_TIMER_HPP
#define ENGINE_TIMER_HPP

#include "core/timer.h"

namespace engine {
    class clock {
        uint64 tick;
        public:
        clock() : tick(0) { reset(); }
        void reset() {
            tick = Core_GetCounter();
        }
        double restart() {
            const uint64 now = Core_GetCounter();
            const uint64 diff = now - tick;
            tick = now;
            return static_cast<double>(diff) / static_cast<double>(Core_GetFrequency());
        }
        [[nodiscard]] double elapsed() const {
            const uint64 now = Core_GetCounter();
            return static_cast<double>(now - tick) / static_cast<double>(Core_GetFrequency());
        }
    };
}

#endif //ENGINE_TIMER_HPP