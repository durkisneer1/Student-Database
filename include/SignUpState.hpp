#pragma once

#include "RenderWindow.hpp"


class SignUpState : public AppState {
public:
    SignUpState(RenderWindow &window, TTF_Font *font);

    void input(SDL_Event &event, States &state) override;
    void update(SDL_FPoint mousePos) override;
    void draw(SDL_Renderer *renderer) override;

    void saveData();
    void generateStudentId();
private:
    RenderWindow &window;
    TTF_Font *font;
    int studentId = 0;
    std::string studentName;
    std::string selectedMajor;

    Text idText = Text(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 8), font, 2.5, window.getRenderer(),
                          std::to_string(studentId));
    Text nameText = Text(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 4), font, 1.5, window.getRenderer(), "Name: ");

    EntityInfo idleOptionImageInfo = window.loadImageInfo("../res/idle_selection.png");
    EntityInfo selectOptionImageInfo = window.loadImageInfo("../res/hovered_selection.png");

    EntityInfo compSci = window.loadTextInfo("Comp Sci", font, {0, 43, 54});
    EntityInfo business = window.loadTextInfo("Business", font, {0, 43, 54});
    EntityInfo culinary = window.loadTextInfo("Culinary", font, {0, 43, 54});
    EntityInfo philosophy = window.loadTextInfo("Philosophy", font, {0, 43, 54});
    EntityInfo nursing = window.loadTextInfo("Nursing", font, {0, 43, 54});
    EntityInfo english = window.loadTextInfo("English", font, {0, 43, 54});

    std::vector<MajorSelect> majorOptionsVector = {
            MajorSelect(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT / 3), idleOptionImageInfo, selectOptionImageInfo, compSci, 2),
            MajorSelect(Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT / 3), idleOptionImageInfo, selectOptionImageInfo, business, 2),
            MajorSelect(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT / 2), idleOptionImageInfo, selectOptionImageInfo, culinary, 2),
            MajorSelect(Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT / 2), idleOptionImageInfo, selectOptionImageInfo, philosophy, 2),
            MajorSelect(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT * 2 / 3), idleOptionImageInfo, selectOptionImageInfo, nursing, 2),
            MajorSelect(Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT * 2 / 3), idleOptionImageInfo, selectOptionImageInfo, english, 2)
    };
};
