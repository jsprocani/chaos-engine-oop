#ifndef CORE_INPUT_H
#define CORE_INPUT_H

typedef enum {
    EVENT_UNKNOWN = 0,
    EVENT_QUIT = 1,
} EventType;

typedef struct {
    int type;
} Event;

#ifdef __cplusplus
extern "C" {
#endif

int Core_PollEvent(Event* event);

#ifdef __cplusplus
}
#endif

#endif //CORE_INPUT_H