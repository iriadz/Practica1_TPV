#include "MainMenuState.h"
#include "Game.h"
#include "Button.h"
#include "Label.h"
#include <filesystem>
#include <iostream>

MainMenuState::MainMenuState(Game* game) : GameState(game), selected(0) {
    // discover maps
    namespace fs = std::filesystem;
    try {
        for (auto& entry : fs::directory_iterator("assets/maps")) {
            mapNames.push_back(entry.path().stem().string());
        }
    }
    catch (...) {
    }
    //CREAR UI
}

MainMenuState::~MainMenuState() {
    for (auto b : buttons) delete b;
}

void MainMenuState::update() {
    GameState::update();
}

void MainMenuState::render() const {
    GameState::render();
    // render 
}

void MainMenuState::handleEvent(const SDL_Event& e) {
    GameState::handleEvent(e);
    // handle keyboard + select
}