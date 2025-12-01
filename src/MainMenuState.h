
#include "GameState.h"
#include "gameStateMachine.h"
#include "Button.h"
#include "Label.h"
#include "game.h"
#include "texture.h"
#include <vector>
#include <string>
#include <unordered_map>


class MainMenuState : public GameState {
public:
    explicit MainMenuState(Game* game);
    ~MainMenuState();
    virtual void update() override;
    virtual void render() const override;
    virtual void handleEvent(const SDL_Event& e) override;

    // Metodos Callback para los buttons
    void left();
    void right();
    void salir();
    void mapSelected();

private:
    std::vector<std::string> mapFiles;
    int selected;
    // objetos de la ui
    std::vector<Button*> buttons;
    std::vector<std::pair<Button*, std::string>> mapas;
    std::vector<Label*> labels;
};