#include "PlayState.h"
#include "SceneObject.h"
#include "Game.h"

PlayState::PlayState(Game* g) : GameState(g) {}


void PlayState::update() {
    // update game objects
    GameState::update();
    // update scene objects separately if needed
    for (auto so : sceneObjects) so->update();
}

void PlayState::render() const {
    GameState::render();
    for (auto so : sceneObjects) so->render();
}

void PlayState::handleEvent(const SDL_Event& e) {
    GameState::handleEvent(e);
}

void PlayState::addSceneObject(SceneObject* so) {
    sceneObjects.push_back(so);
    addObject(so);
}

void PlayState::removeSceneObject(SceneObject* so) {
    sceneObjects.remove(so);
    removeObject(so);
}

Collision 
PlayState::checkCollision(const SDL_FRect& rect) const {
    for (auto so : sceneObjects) {
        return so->checkCollision(rect);
    }
}