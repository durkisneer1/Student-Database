#include "../include/SignUpState.hpp"
#include <algorithm>


SignUpState::SignUpState(RenderWindow &window, TTF_Font *font)
: window(window), font(font) {
    generateStudentId();
}

void SignUpState::generateStudentId() {
    studentId = rand() % 999999 + 1000000;
    idText.generateText(window.getRenderer(), font, std::to_string(studentId));
    idText.centerDstRect();
}

void SignUpState::input(SDL_Event &event, States &state) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            state = MENU;
            generateStudentId();
            studentName.clear();
            nameText.generateText(window.getRenderer(), font, "Name: ");
            for (MajorSelect &majorOption : majorOptionsVector) {
                majorOption.selected = false;
            }
        }

    } else if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_BACKSPACE && studentName.length() > 0) {
                studentName.pop_back();
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                std::transform(studentName.begin(), studentName.end(), studentName.begin(), ::toupper);
                std::cout << studentId << " - " << studentName << " in " << selectedMajor << std::endl;
            }
        } else if (event.type == SDL_TEXTINPUT)
            if (studentName.length() < 20)
                studentName += event.text.text;
        nameText.generateText(window.getRenderer(), font, "Name: " + studentName);

    } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        for (MajorSelect &majorOption: majorOptionsVector)
            if (majorOption.collide(RenderWindow::getMousePos())) {
                for (MajorSelect &allOptions: majorOptionsVector)
                    allOptions.selected = false;
                majorOption.selected = true;
                selectedMajor = majorOption.major;
            }
    }
}

void SignUpState::update(SDL_FPoint mousePos) {}

void SignUpState::draw(SDL_Renderer *renderer) {
    idText.draw(renderer);
    nameText.draw(renderer);
    for (MajorSelect &majorOption: majorOptionsVector)
        majorOption.draw(renderer);
}
