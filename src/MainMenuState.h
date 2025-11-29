
#include "GameState.h"
#include "Button.h"
#include "Label.h"
#include <vector>
#include <string>

class MainMenuState : public GameState {
public:
    explicit MainMenuState(Game* game);
    virtual void update() override;
    virtual void render() const override;
    virtual void handleEvent(const SDL_Event& e) override;

private:
    std::vector<std::string> mapNames;
    int selected;
    // objetos de la ui
    std::vector<Button*> buttons;
};