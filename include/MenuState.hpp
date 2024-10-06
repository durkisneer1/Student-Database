#pragma once

#include <vector>
#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Button.hpp"
#include "Text.hpp"

class MenuState
{
public:
    MenuState(RenderWindow &window, TTF_Font *font);

    void input(SDL_Event &event, States &state);
    void update();
    void draw(SDL_Renderer *renderer);

private:
    RenderWindow &window;
    TTF_Font *font;

    Text titleText = Text(
        Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 4), font, 2.5, window.getRenderer(), "Student Portal");

    EntityInfo buttonImageInfo = window.loadImageInfo("../res/button.png");
    EntityInfo logInTextInfo = window.loadTextInfo("Log In", font, {0, 43, 54});
    EntityInfo signUpTextInfo = window.loadTextInfo("Sign Up", font, {0, 43, 54});

    std::vector<Button> buttonVector = {
        Button(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, logInTextInfo, 2),
        Button(Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, signUpTextInfo, 2),
    };
};
