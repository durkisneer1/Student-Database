#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../include/RenderWindow.hpp"

const float WIN_WIDTH = 880;
const float WIN_HEIGHT = 640;


struct Student {
    std::string name;
    std::string major;
};


bool assignNames(std::map<std::string, Student> &studentMap) {
    std::ifstream nameFile("../res/names.txt");
    if (!nameFile.is_open()) {
        return false;
    }
    std::string name;
    while (getline(nameFile, name)) {
        Student newStudent;
        newStudent.name = name;
        studentMap[name] = newStudent;
    }
    nameFile.close();
    return true;
}


void originalCode() {
    srand(time(nullptr));

    std::map<std::string, Student> studentMap;
    if (!assignNames(studentMap)) {
        std::cout << "Failed to open names file.\n";
        return;
    }

    std::map<std::string, std::vector<std::string>> courseList;

    // Courses for one semester
    courseList["Computer Science"] = {"Calculus", "Linear Algebra", "Data Structures and Algorithms", "Discrete Mathematics"};
    courseList["Business"] = {"Statistics", "Economics", "Marketing", "Financing"};
    courseList["Culinary"] = {"Gastronomy", "Nutrition", "Marketing", "Sanitation and Safety"};
    courseList["Nursing"] = {"Anatomy", "Biology", "Physical Education", "Statistics"};
    courseList["Philosophy"] = {"Ancient Philosophy", "Ethics", "Metaphysics", "Epistemology"};
    courseList["Criminal Justice"] = {"Administration", "Ethics", "Eyewitness Testimony", "Constitutional Law"};

    std::cout << "\nEnter 'close' to exit.";
    std::string inputName;
    bool searching = true;
    while (searching) {
        std::cout << "\nEnter student name:";
        getline(std::cin, inputName);
        transform(inputName.begin(), inputName.end(), inputName.begin(), ::toupper);
        if (inputName == "CLOSE") {
            searching = false;
        } else if (studentMap.find(inputName) == studentMap.end()) {
            std::cout << "Student Not Found. Try again.\n";
        } else {
            Student searchStudent = studentMap[inputName];
            std::cout << "Name: " << searchStudent.name << "\nMajor: " << searchStudent.major << "\n";
        }
    }
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO))
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
    if (TTF_Init() < 0)
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
    RenderWindow window("Student Database", (int) WIN_WIDTH, (int) WIN_HEIGHT);
    SDL_Renderer *globalRenderer = window.getRenderer();

    TTF_Font *font = TTF_OpenFont("../res/fonts/Daydream.ttf", 21);
    if (!font)
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

    Text titleText(Vector2f(WIN_WIDTH / 2 + 4, WIN_HEIGHT / 4 + 4), font, 2, globalRenderer, "Student Portal");

    EntityInfo wallpaperImageInfo = window.loadImageInfo("../res/wallpaper.png");
    Entity wallpaperEntity(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 2), wallpaperImageInfo, 2);

    EntityInfo buttonImageInfo = window.loadImageInfo("../res/button.png");
    std::vector<Button> buttonImageVector = {
            Button(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, 2),
            Button(Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, 2)
    };

    EntityInfo buttonTextInfoArray[2] = {
            window.loadTextInfo("Log In", font, {0, 43, 54}),
            window.loadTextInfo("Sign Up", font, {0, 43, 54})
    };
    Button buttonTextEntityArray[2] = {
            Button(Vector2f(), buttonTextInfoArray[0], 1.2),
            Button(Vector2f(), buttonTextInfoArray[1], 1.2)
    };

    bool run = true;
    SDL_Event event;
    SDL_FPoint mousePos;
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                run = false;
            }
            for (Button &button: buttonImageVector) {
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_BUTTON_LEFT) {
                    SDL_FPoint p = {(float) event.button.x, (float) event.button.y};
                    if (button.isHovered(p) && !button.clicked && !titleText.hidden) {
                        for (Button &allButtons: buttonImageVector) {
                            allButtons.resetExponent();
                            allButtons.clicked = true;
                        }
                        titleText.resetExponent();
                        titleText.hide = true;
                    }
                } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && button.clicked) {
                    if (button.clicked && titleText.hidden) {
                        for (Button &allButtons: buttonImageVector) {
                            allButtons.clicked = false;
                        }
                        titleText.hide = false;
                        titleText.resetTheta();
                    }
                }
            }
        }
        mousePos = RenderWindow::getMousePos();

        window.cls();

        wallpaperEntity.drawScroll(globalRenderer, 0.5f, 0.5f);
        titleText.hide ? titleText.animateHide() : titleText.animateShow();
        if (!titleText.hidden)
            titleText.animateWave(20.0f, 5.0f, false, true);
        titleText.draw(globalRenderer);
        for (int i = 0; i < buttonImageVector.size(); i++) {
            Button &currButton = buttonImageVector[i];
            if (currButton.clicked) {
                currButton.animateHide(WIN_HEIGHT);
            } else {
                currButton.animateShow();
                if (!currButton.hidden)
                    currButton.animateHover(mousePos);
            }
            currButton.drawStatic(globalRenderer);

            buttonTextEntityArray[i].setPos(currButton.getPos(), currButton.getDstRect());
            buttonTextEntityArray[i].drawStatic(globalRenderer);
        }

        window.flip();
        SDL_Delay(16);
    }

    window.cleanUp();
    SDL_Quit();
    IMG_Quit();
    TTF_CloseFont(font);
    TTF_Quit();

    return 0;
}
