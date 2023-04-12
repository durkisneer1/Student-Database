#include "../include/SignUpState.hpp"
#include <algorithm>

SignUpState::SignUpState(RenderWindow &window, TTF_Font *font)
: window(window), font(font) {
    generateStudentId();
}

void SignUpState::clearInfo() {
    generateStudentId();
    selectedMajor.clear();
    studentName.clear();
    nameText.generateText(window.getRenderer(), font, "Name: ");
    for (MajorSelect &majorOption : majorOptionsVector) {
        majorOption.selected = false;
    }
}

void SignUpState::saveData() {
    std::ifstream readFile("../res/students.json");
    json data;
    if (readFile.is_open() && readFile.peek() != std::ifstream::traits_type::eof()) {
        readFile >> data;
    } else {
        data = {{std::to_string(studentId), json::array()}};
    }
    readFile.close();

    json newData = {
            {"name", studentName},
            {"major", selectedMajor}
    };
    data[std::to_string(studentId)] = newData;

    std::ofstream writeFile("../res/students.json");
    writeFile << data.dump(4);
    writeFile.close();
}

void SignUpState::generateStudentId() {
    std::uniform_int_distribution<> dis(1000000, 1999999);
    studentId = dis(gen);

    std::ifstream readFile("../res/students.json");
    json data;
    if (readFile.is_open() && readFile.peek() != std::ifstream::traits_type::eof()) {
        readFile >> data;
        for (json::iterator it = data.begin(); it != data.end(); ++it)
            if (studentId == std::stoi(it.key())) {
                studentId = dis(gen);
                it = data.begin();
            }
    }

    idText.generateText(window.getRenderer(), font, std::to_string(studentId));
    idText.centerDstRect();
    readFile.close();
}

void SignUpState::input(SDL_Event &event, States &state) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            state = MENU;

    } else if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_BACKSPACE && studentName.length() > 0) {
                studentName.pop_back();
            } else if (event.key.keysym.sym == SDLK_RETURN && !studentName.empty() && !selectedMajor.empty()) {
                std::transform(studentName.begin(), studentName.end(), studentName.begin(), ::toupper);
                saveData();
                clearInfo();
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

void SignUpState::draw(SDL_Renderer *renderer) {
    idText.draw(renderer);
    nameText.draw(renderer);
    for (MajorSelect &majorOption: majorOptionsVector)
        majorOption.draw(renderer);
}
