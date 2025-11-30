#ifndef LABEL_H
#define LABEL_H
#include "GameObject.h"
#include "texture.h"
#include"vector2D.h"
#include <string>
#include <SDL3/SDL.h>


class Label : public GameObject {
public:
    Label(GameState* gs, Game* g, Texture* t, Point2D p): 
        GameObject(g, gs),
        textura(t),
        posicion(p)
    {};
   
    virtual void update() override {}
    virtual void render() const override;

  

protected:
    Texture* textura;
    Point2D posicion;
};

#endif