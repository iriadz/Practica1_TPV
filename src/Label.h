#ifndef LABEL_H
#define LABEL_H
#include "GameObject.h"
#include <string>


class Label : public GameObject {
public:
    Label(GameState* gs, Game* g): GameObject(g, gs) {};
   
    virtual void update() override {}
    virtual void render() const override {};

  

protected:
};

#endif