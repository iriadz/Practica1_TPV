#include "SceneObject.h"
#include "Collision.h"
//SceneObject::SceneObject(Game* game, const SDL_FRect& re, Texture* tex)
//    : GameObject(game), rect(re), textura(tex) {
//}

SceneObject::SceneObject(Game* g) : GameObject(g)
{
  /*  int x, y, tipo;
    float vel;
    is >> x >> y >> vel >> tipo;
    posicion = Point2D((int)x, (int)y);*/
}

SceneObject::~SceneObject() {}

void SceneObject::render() const {
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
   
    SDL_FRect _rect = getBoundingBox();
        
    if (SDL_HasRectIntersectionFloat(&other, &_rect)) {
        Collision col(ENEMY, Vector2D<float>(0, 0));
        return col;
    }

    return Collision(NONE, Vector2D<float>(0, 0));
}

