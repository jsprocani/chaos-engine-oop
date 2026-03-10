#ifndef CORE_CORE_H
#define CORE_CORE_H

#include <SDL2/SDL.h>

#define SDL_INIT_FLAGS (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO)

typedef enum {
    SYS_NONE = 0,
    SYS_SDL = 1 << 0,
} SystemFlags;

#ifdef __cplusplus
extern "C" {
#endif

int Core_Init(void);
void Core_Exit(void);

#ifdef __cplusplus
}
#endif

#endif //CORE_CORE_H