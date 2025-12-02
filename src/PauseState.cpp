#include "PauseState.h"
#include "MainMenuState.h"
#include "game.h"
#include "Button.h"
#include "gameStateMachine.h"
#include "Label.h"
#include "texture.h"
#include "EndState.h"

#include <SDL3/SDL.h>

PauseState::PauseState(Game* g, PlayState* ps)
    : GameState(g), playState(ps)
{
    SDL_Renderer* r = g->getRenderer();

    // Botón continuar
    continuar = new Button(this, game, game->getTexture(Game::CONTINUAR), Point2D(Game::WINDOW_WIDTH / 2 -game->getTexture(Game::CONTINUAR)->getFrameWidth() / 2, 200));
    continuar->connect([this]() {
       game->popState();   // volver al PlayState
       
        });
    uiElements.push_back(continuar);
    addObject(continuar);
    addEventListener(continuar);

    // Botón salir
    exit = new Button(this, game, game->getTexture(Game::SALIR) , Point2D(Game::WINDOW_WIDTH / 2 -game->getTexture(Game::SALIR)->getFrameWidth() / 2, 250));
    exit->connect([this]() {
       
        game->exitGame();
    uiElements.push_back(exit);
    addObject(exit);
    addEventListener(exit);

    // Botón menu
    backToMenu = new Button(this, game, game->getTexture(Game::VOLVER_AL_MENU), Point2D(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::VOLVER_AL_MENU)->getFrameWidth() / 2, 300));
    backToMenu->connect([this]() {
        game->swapState(new MainMenuState(game));
        });
    uiElements.push_back(backToMenu);
    addObject(backToMenu);
    addEventListener(backToMenu);

    // Botón menu
    reiniciar = new Button(this, game, game->getTexture(Game::REINICIAR), Point2D(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::REINICIAR)->getFrameWidth() / 2, 350));
    reiniciar->connect([this]() {
       
        game->swapState(new PlayState(game, playState->getFile()) );
        });
    uiElements.push_back(reiniciar);
    addObject(reiniciar);
    addEventListener(reiniciar);
}

PauseState::~PauseState() {
    // Los GameObjects se destruyen en GameState::~GameState()
    uiElements.clear();
}

void PauseState::update() {
    GameState::update();
}

void PauseState::render() const {

    // Dibujamos un overlay oscuro encima del PlayState
    SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 150);
    SDL_FRect overlay = { 0, 0,
                          (float)game->WINDOW_WIDTH,
                          (float)game->WINDOW_HEIGHT };
    SDL_RenderFillRect(game->getRenderer(), &overlay);
    

    SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_NONE);

    // Ahora dibujamos la UI
    GameState::render();
}

void PauseState::handleEvent(const SDL_Event& e) {

    GameState::handleEvent(e);

    if (e.type == SDL_EVENT_KEY_DOWN) {
        switch (e.key.key) {
        case SDL_SCANCODE_ESCAPE:
        case SDL_SCANCODE_P:
            game->popState(); // reanudar
            break;
        }
    }
}