#pragma once
#include "game.h"
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



class Game; // forward

class GameObject {
public:
    explicit GameObject(Game* g) : game(g) {}
    virtual ~GameObject() = default;

    // render debe ser const según enunciado
    virtual void render(SDL_Renderer* renderer) const;
    virtual void update(float dt);

protected:
    Game* game;
};

#endif // GAMEOBJECT_H
//Clase GameObject : esta clase abstracta es la raíz de la jerarquía de objetos del juego y reúne la funcionalidad común a todos ellos.Su declaración incluye los métodos virtuales puros render y update, además
//de una destructora virtual, un atributo con un puntero al juego y un constructor protegido que reciba ese
//puntero.

