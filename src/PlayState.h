#pragma once
#include <list>
#include "GameObject.h"
#include "SceneObject.h"
#include "Collision.h"
#include "Frog.h"
#include "HomedFrog.h"
#include "InfoBar.h"

class InfoBar;

using It = std::list<SceneObject*>::iterator;

class PlayState : public GameState
{
public:
	static constexpr int HOMED_NUM = 5;

	PlayState(Game* g, std::string fileName);

	virtual ~PlayState() override;

	virtual void update() override;
	virtual void render() const override;
	virtual void handleEvent(const SDL_Event& e) override;

	// manejar la lista de sceneObjects (especifica de playstate)
	void loadMap(std::string fileName);
	void addSceneObject(SceneObject* so);
	void setSceneObjectList(std::list<SceneObject*> sol);
	void removeSceneObject(SceneObject* so);

	//reiniciar partida
	void reiniciarMsg();
	void reiniciar();
	//colisiones
	Collision checkCollision(const SDL_FRect& rect) const;

	//avispas
	std::string getFile();

protected:
	//no hay que poner la lista de gameobjects, la hereda de gamestate
	Frog* frog;
	InfoBar* infobar;
	std::vector<HomedFrog*> homesList;
	std::list<SceneObject*> sceneObjects;
	std::string file; // variable para guardar la ruta del mapa actual

	std::list<It> m_toDelete; // it a borrar al final de update
	std::list<It> waspsDel; // avistpas a borrar al final del update
	int numTotalObjects;
	float waspsSpawn = 3;
	int lifeTime = 0;
	bool waspAlive = false;
	/*std::vector<int>homedFrogs;*/
	int homedfrogs;

	std::vector<std::pair<Point2D, bool>> homes;// par con las posiciones de las casas y si estan ocupadas


};

