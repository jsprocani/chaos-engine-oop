#include "core/input.h"
#include <SDL2/SDL.h>

int Core_PollEvent(Event* event) {
    SDL_Event sdl_event;
    if (SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_QUIT) {
            event->type = EVENT_QUIT;
        } else {
            event->type = EVENT_UNKNOWN;
        }
        return 1;
    }
    return 0;
}
