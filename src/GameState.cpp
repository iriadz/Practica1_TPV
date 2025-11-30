#include "GameState.h"

void GameState::update() {
    for (auto p : gameObjects) p->update();
    // run delayed callbacks at end of update
    for (auto& cb : callBacks) cb();
    callBacks.clear();
}

void GameState::render() const {
    for (auto p : gameObjects) p->render();
}

void GameState::handleEvent(const SDL_Event& e) {
    for (auto h : events) h->handleEvent(e);
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
    events.push_back(h);
}

void GameState::removeEventListener(EventHandler* h) {
    events.remove(h);
}

void GameState::runLater(DelayedCallBack cb) {
    callBacks.push_back(cb);
}