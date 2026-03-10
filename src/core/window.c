#define MODULE_NAME "WINDOW"
#include "core/window.h"
#include "core/logger.h"
#include "core/utils.h"

static SDL_Window *s_window = NULL;

SDL_Window *Core_GetWindow(void) {
    CORE_INFO("Getting window... (addr: %p)", (void*)s_window);
    return s_window;
}

void Core_SetWindow(SDL_Window *window) {
    if (s_window != window) {
        CORE_INFO("Setting window... (addr: %p)", (void*)window);
        s_window = window;
    }
}

SDL_Window *Core_CreateWindow(const char *title, const int x, const int y, const int w, const int h,
                              const uint flags, int *status) {
    CORE_INFO("Creating window...");
    SDL_Window *window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window == NULL) {
        CORE_ERROR("SDL_CreateWindow failed: %s", SDL_GetError());
        *status = ERROR;
        return NULL;
    }
    if (s_window == NULL) {
        s_window = window;
    }
    CORE_OK("Window created (%dx%d) at address %p.", w, h, (void*)window);
    *status = SUCCESS;
    return window;
}

int Core_DestroyWindow(SDL_Window *window) {
    CORE_INFO("Destroying window... (addr: %p)", (void*)window);
    if (window == NULL) {
        CORE_WARN("Window already destroyed.");
        return WARNING;
    }
    if (window == s_window) s_window = NULL;
    SDL_DestroyWindow(window);
    CORE_OK("Window destroyed.");
    return SUCCESS;
}
