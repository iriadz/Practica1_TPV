#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "Collision.h"
#include "texture.h"

class SceneObject : public GameObject {
public:
   /* SceneObject(Game* game, const SDL_FRect& rect, Texture* tex = nullptr);*/
    SceneObject(Game* game);
    virtual ~SceneObject();

    virtual void render() const override;
    virtual void update(float dt) override = 0;

    // devuelve true si colisiona con la caja pasada
    virtual Collision checkCollision(const SDL_FRect& other) const;

    // acceso
    const SDL_FRect& getRect() const { return rect; }
   

protected:
    SDL_FRect rect;
    Point2D posicion;
    Texture* textura;
    virtual SDL_FRect getBoundingBox() const;
};

#endif // SCENEOBJECT_H
