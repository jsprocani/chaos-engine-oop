#define MODULE_NAME "RENDER"
#include "core/renderer.h"
#include "core/logger.h"
#include "core/utils.h"
#include <math.h>
#include <stdlib.h>

static SDL_Renderer *s_renderer = NULL;

#define CHECK_RENDERER() \
    if (s_renderer == NULL) { \
        CORE_WARN("No active renderer!"); \
        return WARNING; \
    }

SDL_Renderer *Core_GetRenderer(void) { return s_renderer; }

void Core_SetRenderer(SDL_Renderer *renderer) { s_renderer = renderer; }

SDL_Renderer *Core_CreateRenderer(SDL_Window *window, const uint flags, int *status) {
    CORE_INFO("Creating renderer...");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, flags);
    if (renderer == NULL) {
        CORE_ERROR("SDL_CreateRenderer failed: %s", SDL_GetError());
        *status = ERROR;
        return NULL;
    }
    s_renderer = renderer;
    CORE_OK("Renderer created.");
    *status = SUCCESS;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return renderer;
}

int Core_DestroyRenderer(SDL_Renderer *renderer) {
    if (renderer && renderer == s_renderer) s_renderer = NULL;
    if (renderer) SDL_DestroyRenderer(renderer);
    return SUCCESS;
}

int Core_Present(void) {
    CHECK_RENDERER();
    SDL_RenderPresent(s_renderer);
    return SUCCESS;
}

int Core_Clear(void) {
    CHECK_RENDERER();
    return SDL_RenderClear(s_renderer) < 0 ? ERROR : SUCCESS;
}

int Core_GetDrawColor(uchar *r, uchar *g, uchar *b, uchar *a) {
    CHECK_RENDERER();
    return SDL_GetRenderDrawColor(s_renderer, r, g, b, a) < 0 ? ERROR : SUCCESS;
}

int Core_SetDrawColor(const uchar r, const uchar g, const uchar b, const uchar a) {
    CHECK_RENDERER();
    return SDL_SetRenderDrawColor(s_renderer, r, g, b, a) < 0 ? ERROR : SUCCESS;
}

int Core_DrawRect(const int x, const int y, const int w, const int h, const bool fill) {
    CHECK_RENDERER();
    const SDL_Rect r = {x, y, w, h};
    return fill ? SDL_RenderFillRect(s_renderer, &r) : SDL_RenderDrawRect(s_renderer, &r);
}

int Core_DrawRectF(const float x, const float y, const float w, const float h, const bool fill) {
    CHECK_RENDERER();
    const SDL_FRect r = {x, y, w, h};
    return fill ? SDL_RenderFillRectF(s_renderer, &r) : SDL_RenderDrawRectF(s_renderer, &r);
}

int Core_DrawRects(const int *rects, const int count, const bool fill) {
    CHECK_RENDERER();
    return fill ? SDL_RenderFillRects(s_renderer, (const SDL_Rect*)rects, count) : SDL_RenderDrawRects(s_renderer, (const SDL_Rect*)rects, count);
}
int Core_DrawRectsF(const float *rects, const int count, const bool fill) {
    CHECK_RENDERER();
    return fill ? SDL_RenderFillRectsF(s_renderer, (const SDL_FRect*)rects, count) : SDL_RenderDrawRectsF(s_renderer, (const SDL_FRect*)rects, count);
}

int Core_DrawCircleF(const float x, const float y, const float radius, const bool fill) {
    CHECK_RENDERER();
    if (radius <= 0.0f) return WARNING;
    int segments = (int)(radius * 0.5f);
    if (segments < 20) segments = 20;
    if (segments > 100) segments = 100;
    const float step = 6.2831853f / (float)segments;
    if (fill) {
        SDL_Vertex *verts = malloc(sizeof(SDL_Vertex) * (segments + 2));
        if (!verts) return ERROR;
        SDL_Color c;
        SDL_GetRenderDrawColor(s_renderer, &c.r, &c.g, &c.b, &c.a);
        verts[0] = (SDL_Vertex){{x, y}, c, {0, 0}};
        for (int i = 0; i <= segments; i++) {
            const float angle = step * (float)i;
            verts[i + 1] = (SDL_Vertex){{x + cosf(angle) * radius, y + sinf(angle) * radius}, c, {0, 0}};
        }
        int *indices = malloc(sizeof(int) * segments * 3);
        if (!indices) { free(verts); return ERROR; }
        for (int i = 0; i < segments; i++) {
            indices[i * 3 + 0] = 0;     // Centre
            indices[i * 3 + 1] = i + 1;
            indices[i * 3 + 2] = i + 2;
        }
        const int ret = SDL_RenderGeometry(s_renderer, NULL, verts, segments + 2, indices, segments * 3);
        free(verts);
        free(indices);
        return ret < 0 ? ERROR : SUCCESS;
    }
    SDL_FPoint *points = malloc(sizeof(SDL_FPoint) * (segments + 1));
    if (!points) return ERROR;
    for (int i = 0; i <= segments; i++) {
        const float angle = step * (float)i;
        points[i].x = x + cosf(angle) * radius;
        points[i].y = y + sinf(angle) * radius;
    }
    const int ret = SDL_RenderDrawLinesF(s_renderer, points, segments + 1);
    free(points);
    return ret < 0 ? ERROR : SUCCESS;
}

int Core_DrawCircle(const int x, const int y, const int radius, const bool fill) {
    return Core_DrawCircleF((float)x, (float)y, (float)radius, fill);
}
