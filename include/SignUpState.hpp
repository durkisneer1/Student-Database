#pragma once

#include "RenderWindow.hpp"


class SignUpState : public AppState {
public:
    SignUpState(RenderWindow &window, TTF_Font *font);

    void input(SDL_Event &event, States &state) override;
    void update(SDL_FPoint mousePos) override;
    void draw(SDL_Renderer *renderer) override;

    void generateStudentId();

    std::vector<Button> &getButtonVector() { return buttonVector; };
private:
    RenderWindow &window;
    TTF_Font *font;
    int studentId = 0;

    std::vector<Button> buttonVector = {};
    Text titleText = Text(Vector2f(WIN_WIDTH / 2 + 4, WIN_HEIGHT / 4 + 4), font, 2.5, window.getRenderer(),
                          std::to_string(studentId));
};
