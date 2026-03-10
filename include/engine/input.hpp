#ifndef ENGINE_INPUT_HPP
#define ENGINE_INPUT_HPP

#include "core/input.h"

namespace engine {
    enum class event_type {
        UNKNOWN = 0,
        QUIT = 1
    };
    struct event {
        event_type type;
    };
    class input {
    public:
        static bool poll(event& e);
    };
}

#endif //ENGINE_INPUT_HPP