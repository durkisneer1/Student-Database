#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../include/MenuState.hpp"
#include "../include/SignUpState.hpp"


void launchErrorCheck() {
    if (SDL_Init(SDL_INIT_VIDEO))
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
    if (TTF_Init() < 0)
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
    SDL_StartTextInput();
}


void quitInit() {
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_StopTextInput();
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    launchErrorCheck();
    RenderWindow window("Student Database", (int) WIN_WIDTH, (int) WIN_HEIGHT);
    SDL_Renderer *globalRenderer = window.getRenderer();
    TTF_Font *font = TTF_OpenFont("../res/fonts/Daydream.ttf", 21);
    if (!font)
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

    Wallpaper wallpaper(window.loadImageInfo("../res/wallpaper.png"), 2);
    MenuState menuState(window, font);
    SignUpState signUpState(window, font);
    States currState = MENU;

    bool run = true;
    SDL_Event event;
    SDL_FPoint mousePos;
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                run = false;

            if (currState == MENU) {
                menuState.input(event, currState);
            } else if (currState == SIGNUP) {
                signUpState.input(event, currState);
            }
        }
        mousePos = RenderWindow::getMousePos();

        window.cls();
        wallpaper.animateScroll(globalRenderer, 0.5f, 0.5f);

        if (currState == MENU) {
            menuState.update(mousePos);
            menuState.draw(globalRenderer);
        } else if (currState == SIGNUP) {
            signUpState.update(mousePos);
            signUpState.draw(globalRenderer);
        }

        window.flip();
        SDL_Delay(16);
    }

    window.cleanUp();
    TTF_CloseFont(font);
    quitInit();

    return 0;
}
