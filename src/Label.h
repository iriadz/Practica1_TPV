#include "GameObject.h"
#include <string>


class Label : public GameObject
{
public:
    Label(GameState* gs);
    virtual void update(float dt) override {};
    virtual void render() const override;
};