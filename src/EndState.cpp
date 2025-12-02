#include "EndState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "Button.h"
#include "Label.h"
#include "game.h"

#include <SDL3/SDL.h>

EndState::EndState(Game* g, bool w)
    : GameState(g), won(w) {


    struct BotonInfo {
        Game::TextureName id;
        Point2D pos;
    };

    std::vector<BotonInfo> datos = {
        {Game::SALIR,  Point2D(Game::WINDOW_WIDTH / 2 - (GameState::game->getTexture(Game::SALIR)->getFrameWidth() / 2),   350)},
        {Game::VOLVER_AL_MENU,  Point2D(Game::WINDOW_WIDTH / 2 - (GameState::game->getTexture(Game::VOLVER_AL_MENU)->getFrameWidth() / 2),   220) },
    };

    for (auto& d : datos) {
        Button* b = new Button(this, game, game->getTexture(d.id), d.pos);
        buttons.push_back(b);
        addObject(b);
        addEventListener(b);
    }

    buttons[0]->connect([this]() {salir();});
    buttons[1]->connect([this]() {volverMenu();});

    if (won)
    {
        Label* hasGanado = new Label(this, game, game->getTexture(Game::HAS_GANADO), Point2D(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::HAS_GANADO)->getFrameWidth() / 2, 100));
        SDL_SetTextureColorMod(hasGanado->getTexture()->getTexture(), 0, 255, 0); // Color normal
        labels.push_back(hasGanado);
        addObject(hasGanado);
    }
    else 
    {
        Label* perdido = new Label(this, game, game->getTexture(Game::GAME_OVER), Point2D(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::GAME_OVER)->getFrameWidth() / 2, 100));
        SDL_SetTextureColorMod(perdido->getTexture()->getTexture(), 255, 0, 0); // Color normal
        labels.push_back(perdido);
        addObject(perdido);
    }
    
}

EndState::~EndState() {
    buttons.clear();
    labels.clear();
}

void EndState::update() {
    GameState::update();
}

void EndState::render() const {
    for (Label* l : labels) {
        l->render();
    }
    for (Button* b : buttons) {
        b->render();
    }
}

void EndState::handleEvent(const SDL_Event& e) {
    GameState::handleEvent(e);
    // TODO: handle restart/return to menu/exit
}

void
EndState::salir() {
    game->exitGame();
}

void
EndState::volverMenu() {
    game->swapState(new MainMenuState(game));
}