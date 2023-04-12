#pragma once

#include "RenderWindow.hpp"
#include <string>

using json = nlohmann::json;


class LogInState {
public:
    LogInState(RenderWindow &window, TTF_Font *font);

    void input(SDL_Event &event, States &state);
    void draw(SDL_Renderer *renderer);

    void getStudentInfo();
private:
    RenderWindow &window;
    TTF_Font *font;
    std::string studentId;
    std::string studentName;
    std::string studentMajor;

    Text idText = Text(
            Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 8), font, 1.5, window.getRenderer(), "Student ID: " + studentId);
    Text nameText = Text(
            Vector2f(WIN_WIDTH / 2, WIN_HEIGHT * 5 / 16), font, 1, window.getRenderer(), " ");
    Text majorText = Text(
            Vector2f(WIN_WIDTH / 2, WIN_HEIGHT * 3 / 8), font, 1, window.getRenderer(), " ");

    std::vector<Text> courseTexts = {
            Text(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 2), font, 1, window.getRenderer(), " "),
            Text(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT * 9 / 16), font, 1, window.getRenderer(), " "),
            Text(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT * 5 / 8), font, 1, window.getRenderer(), " "),
            Text(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT * 11/ 16), font, 1, window.getRenderer(), " ")
    };
};
