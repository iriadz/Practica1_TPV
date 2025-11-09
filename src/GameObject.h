#pragma once
#include "game.h"
class GameObject
{
public:
	GameObject() {};
	void render();
	void update();

private:
	Game* g;

protected:
	GameObject(Game* game);
};

//Clase GameObject : esta clase abstracta es la raíz de la jerarquía de objetos del juego y reúne la funcionalidad común a todos ellos.Su declaración incluye los métodos virtuales puros render y update, además
//de una destructora virtual, un atributo con un puntero al juego y un constructor protegido que reciba ese
//puntero.