#include "SceneObject.h"
#include "Collision.h"

SceneObject::SceneObject(Game* g, GameState* gs, PlayState* ps, std:: istream &is) : GameObject(g, gs)
{
    playState = ps;
    int x, y;
    is >> x >> y;
    posicion = Point2D((int)x, (int)y);
}

SceneObject::~SceneObject() {}

void SceneObject::render() const {
    SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->render(r);
}

SDL_FRect SceneObject::getBoundingBox() const {
    SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() / 2 };
    return r;
}

Collision 
SceneObject::checkCollision(const SDL_FRect& other) const {
    SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    if (SDL_HasRectIntersectionFloat(&other, &r)) {
        Collision col(ENEMY, Vector2D<float>(0, 0));
        return col;
    }

    return Collision(NONE, Vector2D<float>(0, 0));
}

