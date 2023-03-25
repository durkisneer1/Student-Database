#include "../include/SignUpState.hpp"


SignUpState::SignUpState(RenderWindow &window, TTF_Font *font)
: window(window), font(font) {
    generateStudentId();
}

void SignUpState::generateStudentId() {
    studentId = rand() % 999999 + 1000000;
    titleText.generateText(window.getRenderer(), font, std::to_string(studentId));
    titleText.centerDstRect();
}

void SignUpState::input(SDL_Event &event, States &state) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            state = MENU;
            generateStudentId();
        }
}

void SignUpState::update(SDL_FPoint mousePos) {}

void SignUpState::draw(SDL_Renderer *renderer) {
    titleText.draw(renderer);
}
