#ifndef CROSSER_H
#define CROSSER_H

#include "SceneObject.h"
//#include <SDL.h>

class Crosser : public SceneObject {
public:
   // Crosser(Game* game, const SDL_FRect& rect, float vx, Texture* tex = nullptr);
    Crosser(Game* g);
    virtual ~Crosser();

    virtual void update(float dt) override;

    float getSpeed() const { return velocidad.getX(); }
    void setSpeed(float s) { velocidad = Vector2D<float>(s, 0); }

    Collision checkCollision(const SDL_FRect& other) const override;

protected:
    Vector2D<float> velocidad;
    int ancho; // desplazamiento para reaparecer por el lado opuesto (seteado por mapa)
};


#endif // CROSSER_H
