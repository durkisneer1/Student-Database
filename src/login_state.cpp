#include "../include/LogInState.hpp"


LogInState::LogInState(RenderWindow &window, TTF_Font *font)
: window(window), font(font) {}

void LogInState::input(SDL_Event &event, States &state) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            state = MENU;
    } else if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_BACKSPACE && studentId.length() > 0) {
                studentId.pop_back();
            }
        } else if (event.type == SDL_TEXTINPUT)
            if (studentId.length() < 7)
                studentId += event.text.text;
        idText.generateText(window.getRenderer(), font, "Enter Student ID: " + studentId);
    }
}

void LogInState::update() {}

void LogInState::draw(SDL_Renderer *renderer) {
    idText.draw(renderer);
}