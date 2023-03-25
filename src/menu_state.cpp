#include "../include/MenuState.hpp"


MenuState::MenuState(RenderWindow &window, TTF_Font *font)
: window(window), font(font) {}

void MenuState::input(SDL_Event &event, States &state) {
    for (int i = 0; i < buttonVector.size(); i++) {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if (i == 0) {
                state = LOGIN;
            } else if (i == 1) {
                state = SIGNUP;
            }
        }
    }
}

void MenuState::update(SDL_FPoint mousePos) {
    titleText.animateWave(20.0f, 5.0f, false, true);
    for (Button &button: buttonVector)
        button.animateHover(mousePos);
}

void MenuState::draw(SDL_Renderer *renderer) {
    titleText.draw(renderer);
    for (Button &button: buttonVector)
        button.draw(renderer);
}
