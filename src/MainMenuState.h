
#include "GameState.h"
#include "Button.h"
#include "Label.h"
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

private:
    std::vector<std::string> mapNames;
    int selected;
    // objetos de la ui
    std::vector<Button*> buttons;
    std::vector<Button*> mapas;
    std::vector<Label*> labels;
};