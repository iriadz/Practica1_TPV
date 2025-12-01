
#include "GameState.h"
#include "Button.h"
#include "Label.h"
#include <string>
#include <vector>

class EndState : public GameState {
public:
    explicit EndState(Game* game);
    virtual ~EndState();

    virtual void update() override;
    virtual void render() const override;
    virtual void handleEvent(const SDL_Event& e) override;

    void salir();
    void volverMenu();

private:
    std::string m_message;
    std::vector<Button*> buttons;
    std::vector<Label*> labels;
};
