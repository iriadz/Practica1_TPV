#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL3/SDL.h>

class EventHandler {
public:
    virtual void handleEvent(const SDL_Event &e);
};

#endif

