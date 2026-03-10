#ifndef CORE_TIME_H
#define CORE_TIME_H

#include <SDL2/SDL.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

inline uint Core_GetTicks() {
    return SDL_GetTicks();
}

inline uint64 Core_GetCounter() {
    return SDL_GetPerformanceCounter();
}

inline uint64 Core_GetFrequency() {
    return SDL_GetPerformanceFrequency();
}

inline void Core_Delay(const uint ms) {
    SDL_Delay(ms);
}

inline void Core_Sleep(const float s) {
    SDL_Delay((uint)(s * 1000.0f));
}

#ifdef __cplusplus
}
#endif

#endif //CORE_TIME_H