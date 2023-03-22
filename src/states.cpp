#include "../include/States.hpp"


MenuState::MenuState(RenderWindow &window, TTF_Font *font)
: window(window), font(font) {}

void MenuState::update(SDL_FPoint mousePos) {
    titleText.hide ? titleText.animateHide() : titleText.animateShow();
    if (!titleText.hidden)
        titleText.animateWave(20.0f, 5.0f, false, true);
    for (Button &button : buttonVector) {
        button.hide ? button.animateHide(WIN_HEIGHT) : button.animateShow();
        if (!button.hide)
            button.animateHover(mousePos);
    }
}

void MenuState::draw(SDL_Renderer *renderer) {
    wallpaperEntity.animateScroll(renderer, 0.5f, 0.5f);
    if (!titleText.hidden)
        titleText.draw(renderer);
    for (Button &button : buttonVector) {
        if (!button.hidden)
            button.draw(renderer);
    }
}

