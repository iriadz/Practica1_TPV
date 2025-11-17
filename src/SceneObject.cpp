#include "SceneObject.h"
#include "Collision.h"
SceneObject::SceneObject(Game* game, const SDL_FRect& re, Texture* tex)
    : GameObject(game), rect(re), textura(tex) {
}

SceneObject::~SceneObject() {}

void SceneObject::render(SDL_Renderer* renderer) const {
    SDL_FRect r = { posicion.getX(),posicion.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
    textura->render(r);
}

SDL_FRect SceneObject::getBoundingBox() const {
    return rect;
}

Collision 
SceneObject::checkCollision(const SDL_FRect& other) const {
   ///* SDL_FRect a = getBoundingBox();
   // SDL_FRect b = other;
   // bool ch = !(a.x + a.w <= b.x || b.x + b.w <= a.x || a.y + a.h <= b.y || b.y + b.h <= a.y);*/
   
        
   if (SDL_HasRectIntersectionFloat(&other, &getBoundingBox())) {
        Collision col(ENEMY, Vector2D<int>(0, 0));
        return col;
    }

    return Collision(NONE, Vector2D<int>(0, 0));
}

