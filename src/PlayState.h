#pragma once
#include <list>
#include "GameObject.h"
#include "SceneObject.h"
#include "Collision.h"
class PlayState:public GameState
{
public:
	PlayState(Game* g);

	virtual void update() override;
	virtual void render() const override;
	virtual void handleEvent(const SDL_Event& e) override;

	// manejar la lista de sceneObjects (especifica de playstate)
	void addSceneObject(SceneObject* so);
	void removeSceneObject(SceneObject* so);

	//colisiones
	Collision checkCollision(const SDL_FRect& rect) const;

private:
	//no hay que poner la lista de gameobjects, la hereda de gamestate
	std::list<SceneObject*> sceneObjects;
};

