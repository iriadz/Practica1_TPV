#ifndef BUTTON_H
#define BUTTON_H
#include <functional>
#include <vector>
#include <SDL3/SDL.h>

// Forward declarations
class GameState;
class Texture;

#include "Label.h"
#include "EventHandler.h"   // Necesario para heredar correctamente

class Button : public Label {
public:
    using Callback = std::function<void()>;

    Button(GameState* gs, Game* g, Texture* t, Point2D p) :
        Label(gs, g, t, p),
        visible(true)
    {};
    virtual ~Button();

    void connect(Callback cb);

    virtual void update() override {};
    virtual void render() const override;
    //virtual void handleEvent(const SDL_Event& e) override;

    void swapVisbility();
private:
    std::vector<Callback> m_callbacks;
    bool m_hover;
    bool visible;
};

#endif
