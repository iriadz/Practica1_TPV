class Button : public Label, public EventHandler {
public:
    using Callback = std::function<void()>;

    Button(GameState* state);
   

    void connect(Callback cb);

    virtual void update(float dt) override;
    virtual void render() const override;
    virtual void handleEvent(const SDL_Event& e) override;

private:
    //no estoy segura de si los callbacks hacen falta
    std::vector<Callback> callbacks;
    bool hover;
};