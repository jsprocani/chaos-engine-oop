#define MODULE_NAME "SYSTEM"
#include "core/system.h"
#include "core/logger.h"
#include "core/types.h"
#include "core/utils.h"

static uint s_init_sys = SYS_NONE;

int Core_Init(void) {
    CORE_INFO("Initializing SDL2 subsystems...");
    if (s_init_sys != SYS_NONE) {
        CORE_WARN("Engine subsystems are already initialized.");
        return WARNING;
    }
    if (SDL_Init(SDL_INIT_FLAGS) < 0) {
        CORE_ERROR("SDL_Init failed: %s", SDL_GetError());
        return ERROR;
    }
    s_init_sys |= SYS_SDL;
    CORE_OK("Engine subsystems initialized successfully.");
    return SUCCESS;
}

void Core_Exit(void) {
    CORE_INFO("Shutting down subsystems...");
    if (s_init_sys & SYS_SDL) {
        SDL_Quit();
        s_init_sys &= ~SYS_SDL;
    }
    CORE_OK("Engine shutdown complete.");
}
