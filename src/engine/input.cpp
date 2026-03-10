#include "engine/input.hpp"

namespace engine {
    bool input::poll(event& e) {
        Event core_event;
        if (Core_PollEvent(&core_event)) {
            e.type = static_cast<event_type>(core_event.type);
            return true;
        }
        return false;
    }
}