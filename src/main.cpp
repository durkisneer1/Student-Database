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

const float WIN_WIDTH = 800;
const float WIN_HEIGHT = 600;


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

    std::vector<std::string> majorList = {"Computer Science", "Business", "Culinary", "Nursing", "Philosophy",
                                          "Criminal Justice"};
    std::map<std::string, std::vector<std::string>> courseList;

    // Courses for one semester
    courseList[majorList[0]] = {"Calculus", "Linear Algebra", "Data Structures and Algorithms", "Discrete Mathematics"};
    courseList[majorList[1]] = {"Statistics", "Economics", "Marketing", "Financing"};
    courseList[majorList[2]] = {"Gastronomy", "Nutrition", "Marketing", "Sanitation and Safety"};
    courseList[majorList[3]] = {"Anatomy", "Biology", "Physical Education", "Statistics"};
    courseList[majorList[4]] = {"Ancient Philosophy", "Ethics", "Metaphysics", "Epistemology"};
    courseList[majorList[5]] = {"Administration", "Ethics", "Eyewitness Testimony", "Constitutional Law"};
    for (auto &student: studentMap) {
        int randomIndex = rand() % courseList.size();
        std::string chosenMajor = majorList[randomIndex];
        student.second.major = chosenMajor;
    }

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


int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO))
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
    if (TTF_Init() < 0)
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
    RenderWindow window("Student Database", (int)WIN_WIDTH, (int)WIN_HEIGHT);

    TTF_Font *font = TTF_OpenFont("../res/fonts/VCR_OSD_Mono.ttf", 24);
    if (!font)
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

    EntityInfo wallpaperEntityInfo = window.loadEntityInfo("../res/wallpaper.png");
    Entity wallpaperEntity(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 2), wallpaperEntityInfo, 2);

    EntityInfo buttonEntityInfo = window.loadEntityInfo("../res/button.png");
    std::vector<Entity> buttonVector;
    buttonVector.emplace_back(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT / 2), buttonEntityInfo, 2);
    buttonVector.emplace_back(Vector2f(WIN_WIDTH * 3/4, WIN_HEIGHT / 2), buttonEntityInfo, 2);

    bool run = true;
    SDL_Event event;
    SDL_Point mousePos = {0, 0};
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = false;
            }
        }
        RenderWindow::getMousePos(mousePos.x, mousePos.y);

        window.cls();
        window.draw(wallpaperEntity);
        for (Entity &buttonEntity : buttonVector) {
            buttonEntity.update(mousePos);
            window.draw(buttonEntity);
        }

        window.flip();
        SDL_Delay(16);
    }

    window.cleanUp();
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();

    return 0;
}
