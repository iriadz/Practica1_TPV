#include "MainMenuState.h"
#include "Game.h"
#include "Button.h"
#include "Label.h"
#include <filesystem>
#include <iostream>



MainMenuState::MainMenuState(Game* g) : GameState(g), selected(0) {
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
    {Game::LEFT,        {Game::WINDOW_WIDTH / 7,   270}},
    {Game::RIGHT,       {Game::WINDOW_WIDTH / 1.20, 270}},
    };

    std::vector<BotonInfo> maps = {
    {Game::ORIGINAL,   Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::ORIGINAL)->getFrameWidth() / 2),   270)},
    {Game::PRACTICA_1, Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::PRACTICA_1)->getFrameWidth() / 2),   270)},
    {Game::TRIVIAL,    Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::TRIVIAL)->getFrameWidth() / 2),   270)},
    {Game::VELOZ,      Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::VELOZ)->getFrameWidth() / 2),   270)},
    {Game::AVISPADO,   Point2D ((Game::WINDOW_WIDTH / 2 - game->getTexture(Game::AVISPADO)->getFrameWidth() / 2),   270)},
    };

    for (auto& d : datos) {
        Button* b = new Button(this, game, game->getTexture(d.id), d.pos);
        buttons.push_back(b);
        addObject(b);
    }


    for (auto& m : maps) {
        Button* b = new Button(this, game, game->getTexture(m.id), m.pos);
        mapas.push_back(b);
        addObject(b);
    }

    Label* eligeUnMapa = new Label(this, game, game->getTexture(Game::ELIGE_UN_MAPA), Point2D(Game::WINDOW_WIDTH/2 - game->getTexture(Game::ELIGE_UN_MAPA)->getFrameWidth()/2, 200));
    labels.push_back(eligeUnMapa);
    addObject(eligeUnMapa);
}

MainMenuState::~MainMenuState() {
    labels.clear();
    mapas.clear();
    buttons.clear();
}

void MainMenuState::update() {
    GameState::update();

}

void MainMenuState::render() const {
    int left = 0, right = 1, salir = 2; // Puramente por comprension de codigo

    Texture* t = game->getTexture(Game::MENUBACKGROUND);
    t->render();

    for (auto l : labels) {
        l->render();
    }

    if (selected == 0) { // Depende de si esta al principio o al final de la lista de mapas
        buttons[left]->render();
    }
    else if (selected == mapas.size() - 1) {
        buttons[right]->render();
    }
    else {
        buttons[left]->render();
        buttons[right]->render();
    }
    buttons[salir]->render();

    mapas[selected]->render();
}

void MainMenuState::handleEvent(const SDL_Event &e) {
    GameState::handleEvent(e);
}