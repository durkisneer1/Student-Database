#pragma once

#include <random>
#include "RenderWindow.hpp"

using json = nlohmann::json;


class SignUpState {
public:
    SignUpState(RenderWindow &window, TTF_Font *font);

    void input(SDL_Event &event, States &state);
    void draw(SDL_Renderer *renderer);

    void clearInfo();
    void saveData();
    void generateStudentId();

private:
    RenderWindow &window;
    TTF_Font *font;

    int studentId = 0;
    std::string studentName;
    std::string selectedMajor;

    // Random number generator
    std::random_device rd;
    std::mt19937_64 gen{rd()};

    Text idText = Text(
        Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 8), font, 2.5, window.getRenderer(), std::to_string(studentId)
    );
    Text nameText = Text(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 4), font, 1.5, window.getRenderer(), "Name: ");

    EntityInfo idleOptionImageInfo = window.loadImageInfo("../res/idle_selection.png");
    EntityInfo selectOptionImageInfo = window.loadImageInfo("../res/hovered_selection.png");

    EntityInfo compSciOption = window.loadTextInfo("Comp Sci", font, {0, 43, 54});
    EntityInfo businessOption = window.loadTextInfo("Business", font, {0, 43, 54});
    EntityInfo culinaryOption = window.loadTextInfo("Culinary", font, {0, 43, 54});
    EntityInfo philosophyOption = window.loadTextInfo("Philosophy", font, {0, 43, 54});
    EntityInfo nursingOption = window.loadTextInfo("Nursing", font, {0, 43, 54});
    EntityInfo englishOption = window.loadTextInfo("English", font, {0, 43, 54});

    std::vector<MajorSelect> majorOptionsVector = {
        MajorSelect(
            Vector2f(WIN_WIDTH / 4, WIN_HEIGHT / 3), idleOptionImageInfo, selectOptionImageInfo, compSciOption, 2
        ),
        MajorSelect(
            Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT / 3), idleOptionImageInfo, selectOptionImageInfo, businessOption, 2
        ),
        MajorSelect(
            Vector2f(WIN_WIDTH / 4, WIN_HEIGHT / 2), idleOptionImageInfo, selectOptionImageInfo, culinaryOption, 2
        ),
        MajorSelect(
            Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT / 2), idleOptionImageInfo, selectOptionImageInfo, philosophyOption, 2
        ),
        MajorSelect(
            Vector2f(WIN_WIDTH / 4, WIN_HEIGHT * 2 / 3), idleOptionImageInfo, selectOptionImageInfo, nursingOption, 2
        ),
        MajorSelect(
            Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT * 2 / 3), idleOptionImageInfo, selectOptionImageInfo, englishOption, 2
        )
    };
};
