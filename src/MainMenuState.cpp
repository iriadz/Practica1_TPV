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
    struct BotonInfo {
        Game::TextureName id;
        Point2D pos;
    };

    std::vector<BotonInfo> datos = {
    {Game::SALIR,      Point2D (Game::WINDOW_WIDTH / 2 - game->getTexture(Game::ORIGINAL)->getFrameWidth() / 3,   350)},
    {Game::LEFT,        {Game::WINDOW_WIDTH / 7,   180}},
    {Game::RIGHT,       {Game::WINDOW_WIDTH / 1.20, 180}},
    };

    std::vector<BotonInfo> maps = {
    {Game::ORIGINAL,   Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::ORIGINAL)->getFrameWidth() / 2),   180)},
    {Game::PRACTICA_1, Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::PRACTICA_1)->getFrameWidth() / 2),   180)},
    {Game::TRIVIAL,    Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::TRIVIAL)->getFrameWidth() / 2),   180)},
    {Game::VELOZ,      Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::VELOZ)->getFrameWidth() / 2),   180)},
    {Game::AVISPADO,   Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::AVISPADO)->getFrameWidth() / 2),   180)},
    };

    for (auto& d : datos) {
        Button* b = new Button(this, game, game->getTexture(d.id), d.pos);
        buttons.push_back(b);
    }

    for (auto& d : maps) {
        Button* b = new Button(this, game, game->getTexture(d.id), d.pos);
        mapas.push_back(b);
    }

    //buttons[1]->swapVisbility();
    for (int i = 1; i < mapas.size(); i++) {
        mapas[i]->swapVisbility();
    }
    Label* eligeUnMapa = new Label(this, game, game->getTexture(Game::ELIGE_UN_MAPA), Point2D(Game::WINDOW_WIDTH/2 - game->getTexture(Game::ELIGE_UN_MAPA)->getFrameWidth()/2, 100));
    labels.push_back(eligeUnMapa);
}



void MainMenuState::update() {
    GameState::update();
}

void MainMenuState::render() const {
    for (auto l : labels) {
        l->render();
    }
    for (auto b : buttons) {
        b->render();
    }
    for (auto m : mapas) {
        m->render();
    }
}

void MainMenuState::handleEvent(const SDL_Event& e) {
    GameState::handleEvent(e);
    // handle keyboard + select
}