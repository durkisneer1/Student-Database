#pragma once

#include "RenderWindow.hpp"


struct GameState {
    virtual void update(SDL_FPoint mousePos) = 0;
    virtual void draw(SDL_Renderer *renderer) = 0;
};


class MenuState : public GameState {
public:
    MenuState(RenderWindow &window, TTF_Font *font);
    void update(SDL_FPoint mousePos) override;
    void draw(SDL_Renderer *renderer) override;

    std::vector<Button> &getButtonVector() { return buttonVector; };
    Text &getTitleText() { return titleText; };
private:
    RenderWindow window;
    TTF_Font *font;

    Text titleText = Text(Vector2f(WIN_WIDTH / 2 + 4, WIN_HEIGHT / 4 + 4), font, 2.5, window.getRenderer(), "Student Portal");

    EntityInfo wallpaperImageInfo = window.loadImageInfo("../res/wallpaper.png");
    Wallpaper wallpaperEntity = Wallpaper(wallpaperImageInfo, 2);

    EntityInfo buttonImageInfo = window.loadImageInfo("../res/button.png");
    EntityInfo logInTextInfo = window.loadTextInfo("Log In", font, {0, 43, 54});
    EntityInfo signUpTextInfo = window.loadTextInfo("Sign Up", font, {0, 43, 54});

    std::vector<Button> buttonVector = {
            Button(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, logInTextInfo, 2),
            Button(Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, signUpTextInfo, 2)
    };
};
