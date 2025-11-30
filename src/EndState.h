
#include "GameState.h"
#include <string>

class EndState : public GameState {
public:
    explicit EndState(Game* game, bool win, const std::string& message = "");
    virtual ~EndState();

    virtual void update() override;
    virtual void render() const override;
    virtual void handleEvent(const SDL_Event& e) override;

private:
    bool m_win;
    std::string m_message;
};
