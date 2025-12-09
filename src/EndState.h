
#include "GameState.h"
#include "Button.h"
#include "Label.h"
#include <string>
#include <vector>

class EndState : public GameState {
public:
    explicit EndState(Game* game, bool w);
    virtual ~EndState();

    virtual void update();
    virtual void render() const override;
    virtual void handleEvent(const SDL_Event& e) override;

    void salir();
    void volverMenu();

private:
   
    std::string msg;
    std::vector<Button*> buttons;
    std::vector<Label*> labels;
    bool won;
};
