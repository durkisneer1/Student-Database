#include <fstream>
#include "LogInState.hpp"

LogInState::LogInState(RenderWindow &window, TTF_Font *font)
    : window(window), font(font) {}

void LogInState::renderIdNotFound()
{
    nameText.generateText(window.getRenderer(), font, "ID not found.");
    nameText.centerDstRect();
}

void LogInState::getStudentInfo()
{
    std::ifstream studentFile("../res/students.json");
    std::ifstream courseFile("../res/courses.json");
    json studentData;
    json courseData;

    if (studentFile.is_open() && studentFile.peek() == std::ifstream::traits_type::eof())
    {
        renderIdNotFound();
        return;
    }
    studentFile >> studentData;
    courseFile >> courseData;
    studentFile.close();
    courseFile.close();
    if (!studentData.contains(studentId))
    {
        nameText.clear(window.getRenderer(), font);
        majorText.clear(window.getRenderer(), font);
        for (Text &courseText : courseTexts)
            courseText.clear(window.getRenderer(), font);
        renderIdNotFound();
        return;
    }

    // student ID found, display their information
    json studentObject = studentData[studentId];
    std::string name = studentObject["name"];
    std::string major = studentObject["major"];

    std::vector<std::string> courseTaken;
    std::vector<std::string> timeSchedules;
    std::vector<std::string> creditHours;

    for (auto &course : courseData[major].items())
    {
        courseTaken.push_back(course.key());
        timeSchedules.push_back(course.value()[0]);
        int creditHoursInt = course.value()[1];
        creditHours.push_back(std::to_string(creditHoursInt));
    }

    // Generate student information
    nameText.generateText(
        window.getRenderer(), font, "Name: " + name);
    nameText.centerDstRect();

    majorText.generateText(
        window.getRenderer(), font, "Major: " + major);
    majorText.centerDstRect();

    for (size_t i = 0; i < courseTexts.size(); i++)
    {
        courseTexts[i].generateText(
            window.getRenderer(), font,
            courseTaken[i] + " @ " + timeSchedules[i] + " - " + creditHours[i] + " CH.");
        courseTexts[i].centerDstRect();
    }
}

void LogInState::input(SDL_Event &event, States &state)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        state = MENU;
    else if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_BACKSPACE && studentId.length() > 0)
                studentId.pop_back();
            else if (event.key.keysym.sym == SDLK_RETURN)
                getStudentInfo();
        }
        else if (event.type == SDL_TEXTINPUT)
            if (studentId.length() < 7)
                studentId += event.text.text;
        idText.generateText(window.getRenderer(), font, "Enter Student ID: " + studentId);
    }
}

void LogInState::draw(SDL_Renderer *renderer)
{
    idText.draw(renderer);
    nameText.draw(renderer);
    majorText.draw(renderer);
    for (Text &courseText : courseTexts)
        courseText.draw(renderer);
}