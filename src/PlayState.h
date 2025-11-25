#pragma once
#include <list>
#include "GameObject.h"
#include "SceneObject.h"
class PlayState
{
public:
	PlayState(std::list<GameObject*> o, std::list<SceneObject*> s) :
		objects(o),
		sceneObjects(s)
	{ }
private:
	std::list<GameObject*> objects;
	std::list<SceneObject*> sceneObjects;
};

