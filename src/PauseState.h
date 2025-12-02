#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include <vector>

class Button;
class Label;
class Game;

class PauseState : public GameState {
public:
    PauseState(Game* g);
    virtual ~PauseState();

    virtual void update() override;
    virtual void render() const override;
    virtual void handleEvent(const SDL_Event& e) override;

private:
    Button* continuar;
    Button* exit;
    Button* backToMenu;

    std::vector<GameObject*> uiElements;
};

#endif