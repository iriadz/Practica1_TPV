#include "EndState.h"
EndState::EndState(Game* game, bool win, const std::string& message)
    : GameState(game), m_win(win), m_message(message) {
}

EndState::~EndState() {}

void EndState::update() {
    GameState::update();
}

void EndState::render() const {
    GameState::render();
    // TODO: draw end screen with m_message
}

void EndState::handleEvent(const SDL_Event& e) {
    GameState::handleEvent(e);
    // TODO: handle restart/return to menu/exit
}