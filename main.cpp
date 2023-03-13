#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;


struct Student {
    std::string name;
    std::string major;
};


bool assignNames(std::map<std::string, Student> &studentMap) {
    std::ifstream nameFile("../resources/names.txt");
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


SDL_Texture *LoadTexture(const std::string &file, SDL_Renderer *ren) {
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(file.c_str());
    if (surface == nullptr) {
        std::cout << "LoadTexture Error: " << SDL_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(ren, surface);
        if (texture == nullptr) {
            std::cout << "CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        }
    }
    SDL_FreeSurface(surface);
    return texture;
}


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *window = SDL_CreateWindow("My App", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *image = LoadTexture("../resources/logic.png", renderer);

    bool run = true;
    SDL_Event ev;
    while(run) {
        while(SDL_PollEvent(&ev) != 0) {
            if(ev.type == SDL_QUIT) {
                run = false;
            }
        }
        SDL_RenderClear(renderer) ;
        SDL_RenderCopy(renderer, image, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
