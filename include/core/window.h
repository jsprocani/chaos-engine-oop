#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <SDL2/SDL.h>
#include "types.h"

#define WINDOW_FLAGS SDL_WINDOW_SHOWN

#ifdef __cplusplus
extern "C" {
#endif

Core_Window Core_GetWindow(void);
void Core_SetWindow(Core_Window window);
Core_Window Core_CreateWindow(const char *title, int x, int y, int w, int h, uint flags, int *status);
int Core_DestroyWindow(Core_Window window);

#ifdef __cplusplus
}
#endif

#endif //CORE_WINDOW_H