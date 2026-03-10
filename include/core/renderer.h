#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "types.h"

#define RENDER_FLAGS (SDL_RENDERER_ACCELERATED)

#ifdef __cplusplus
extern "C" {
#endif

Core_Renderer Core_GetRenderer(void);
void Core_SetRenderer(Core_Renderer renderer);
Core_Renderer Core_CreateRenderer(Core_Window window, uint flags, int *status);
int Core_DestroyRenderer(Core_Renderer renderer);

int Core_Present(void);
int Core_Clear(void);
int Core_SetDrawColor(uchar r, uchar g, uchar b, uchar a);
int Core_GetDrawColor(uchar *r, uchar *g, uchar *b, uchar *a);

int Core_DrawRect(int x, int y, int w, int h, bool fill);
int Core_DrawRectF(float x, float y, float w, float h, bool fill);
int Core_DrawRects(const int *rects, int count, bool fill);
int Core_DrawRectsF(const float *rects, int count, bool fill);

int Core_DrawCircle(int x, int y, int radius, bool fill);
int Core_DrawCircleF(float x, float y, float radius, bool fill);

#ifdef __cplusplus
}
#endif

#endif //CORE_RENDERER_H