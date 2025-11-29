#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


// forward
class Game; 
class GameState;

class GameObject {
public:
    explicit GameObject(Game* g, GameState* gs) : game(g), gameState(gs) {}
    virtual ~GameObject() = default;

    // render debe ser const según enunciado
    virtual void render() const = 0;
    virtual void update() = 0;

protected:
    Game* game;
    GameState* gameState;
};

#endif // GAMEOBJECT_H
//Clase GameObject : esta clase abstracta es la raíz de la jerarquía de objetos del juego y reúne la funcionalidad común a todos ellos.Su declaración incluye los métodos virtuales puros render y update, además
//de una destructora virtual, un atributo con un puntero al juego y un constructor protegido que reciba ese
//puntero.

