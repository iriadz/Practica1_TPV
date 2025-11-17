#ifndef PLATFORM_H
#define PLATFORM_H

#include "Crosser.h"
#include "Collision.h"

class Platform : public Crosser {
public:
   using Crosser::Crosser;
    virtual ~Platform() = default;
    virtual Collision checkCollision(const SDL_FRect& other) const override;
};

#endif // PLATFORM_H
