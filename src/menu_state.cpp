#include "MenuState.hpp"
#include <SDL_ttf.h>

MenuState::MenuState(RenderWindow &window, TTF_Font *font)
    : window(window), font(font) {}

void MenuState::input(SDL_Event &event, States &state)
{
    if (event.type != SDL_MOUSEBUTTONDOWN || event.button.button != SDL_BUTTON_LEFT)
        return;

    for (auto &button : buttonVector)
        if (button.collide(RenderWindow::getMousePos()))
        {
            state = (&button == &buttonVector[0]) ? LOGIN : SIGNUP;
            return;
        }
}

void MenuState::update()
{
    titleText.animateWave(20.0f, 5.0f, false, true);
    for (Button &button : buttonVector)
        button.animateHover(RenderWindow::getMousePos());
}

void MenuState::draw(SDL_Renderer *renderer)
{
    titleText.draw(renderer);
    for (Button &button : buttonVector)
        button.draw(renderer);
}
