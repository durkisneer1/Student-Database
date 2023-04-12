#include "../include/LogInState.hpp"


LogInState::LogInState(RenderWindow &window, TTF_Font *font)
        : window(window), font(font) {}

void LogInState::getStudentInfo() {
    std::ifstream readStudents("../res/students.json");
    std::ifstream readCourses("../res/courses.json");
    json studentData;
    json courseData;
    if (readStudents.is_open() && readStudents.peek() != std::ifstream::traits_type::eof()) {
        readStudents >> studentData;
        readCourses >> courseData;
        if (studentData.contains(studentId)) {
            // student ID found, display their information
            json studentHash = studentData[studentId];
            std::string name = studentHash["name"];
            std::string major = studentHash["major"];
            std::vector<std::string> courses;
            std::vector<std::string> timeSchedules;
            std::vector<std::string> creditHours;
            for (auto& course : courseData[major].items()) {
                courses.push_back(course.key());
                timeSchedules.push_back(course.value()[0]);
                int creditHoursInt = course.value()[1];
                creditHours.push_back(std::to_string(creditHoursInt));
            }

            nameText.generateText(
                    window.getRenderer(), font, "Name: " + name);
            nameText.centerDstRect();
            majorText.generateText(
                    window.getRenderer(), font, "Major: " + major);
            majorText.centerDstRect();

            for (int i = 0; i < courseTexts.size(); i++) {
                courseTexts[i].generateText(
                        window.getRenderer(), font,
                        courses[i] + " @ " + timeSchedules[i] + " - " + creditHours[i] + " CH.");
                courseTexts[i].centerDstRect();
            }
        } else {
            // student ID not found
            nameText.generateText(window.getRenderer(), font, "ID not found.");
            nameText.centerDstRect();
        }
    }
    readStudents.close();
    readCourses.close();
}

void LogInState::input(SDL_Event &event, States &state) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            state = MENU;
    } else if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_BACKSPACE && studentId.length() > 0) {
                studentId.pop_back();
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                getStudentInfo();
            }
        } else if (event.type == SDL_TEXTINPUT)
            if (studentId.length() < 7)
                studentId += event.text.text;
        idText.generateText(window.getRenderer(), font, "Enter Student ID: " + studentId);
    }
}

void LogInState::draw(SDL_Renderer *renderer) {
    idText.draw(renderer);
    nameText.draw(renderer);
    majorText.draw(renderer);
    for (Text& courseText : courseTexts)
        courseText.draw(renderer);
}