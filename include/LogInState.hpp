#pragma once

#include "RenderWindow.hpp"

using json = nlohmann::json;


class LogInState {
public:
    LogInState(RenderWindow &window, TTF_Font *font);

    void input(SDL_Event &event, States &state);
    void update();
    void draw(SDL_Renderer *renderer);
private:
    RenderWindow &window;
    TTF_Font *font;
    std::string studentId;
    std::string studentName;
    std::string studentMajor;

    Text idText = Text(
            Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 8), font, 1.5, window.getRenderer(), "Student ID: " + studentId);
};