#include "GameState.h"
#include <iostream>

void GameState::update() {
    for (auto p : gameObjects) p->update();
    // run delayed callbacks at end of update
    for (auto& cb : callBacks) cb();
    callBacks.clear();
}

GameState::~GameState() {
    for (auto obj : gameObjects) delete obj;
    gameObjects.clear();

    for (auto h : listeners) delete h;
    listeners.clear();

    callBacks.clear();
}

void GameState::render() const {
    for (auto p : gameObjects) p->render();
}

void GameState::handleEvent(const SDL_Event& e) {
    for (auto h : listeners) h->handleEvent(e);
}

void GameState::addObject(GameObject* obj) {
    gameObjects.push_back(obj);
}

void GameState::setObjectList(std::list<GameObject*> obj) {
    gameObjects = obj;
}

void GameState::removeObject(GameObject* obj) {
    gameObjects.remove(obj);
    delete obj;
}

void GameState::addEventListener(EventHandler* h) {
    listeners.push_back(h);
}

void GameState::removeEventListener(EventHandler* h) {
    listeners.remove(h);
}

void GameState::runLater(DelayedCallBack cb) {
    callBacks.push_back(cb);
}