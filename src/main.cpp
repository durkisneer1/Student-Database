#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../include/States.hpp"


void launchErrorCheck() {
    if (SDL_Init(SDL_INIT_VIDEO))
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
    if (TTF_Init() < 0)
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
}


void hideObjects(std::vector<Button> &buttonVector, Button &currButton, Text &titleText, SDL_FPoint mousePos) {
    if (currButton.isHovered(mousePos) && !currButton.hidden && !titleText.hidden) {
        for (Button &allButtons: buttonVector) {
            allButtons.resetExponent();
            allButtons.hide = true;
        }
        titleText.resetExponent();
        titleText.hide = true;
    }
}


void showObjects(std::vector<Button> &buttonVector, Button &currButton, Text &titleText) {
    if (currButton.hidden && titleText.hidden) {
        for (Button &allButtons: buttonVector)
            allButtons.hide = false;
        titleText.hide = false;
    }
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    launchErrorCheck();
    RenderWindow window("Student Database", (int) WIN_WIDTH, (int) WIN_HEIGHT);
    SDL_Renderer *globalRenderer = window.getRenderer();
    TTF_Font *font = TTF_OpenFont("../res/fonts/Daydream.ttf", 21);
    if (!font)
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

    MenuState menuState(window, font);

    bool run = true;
    SDL_Event event;
    SDL_FPoint mousePos;
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                run = false;
            for (Button &currButton: menuState.getButtonVector()) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.state == SDL_BUTTON_LEFT)
                        hideObjects(menuState.getButtonVector(), currButton, menuState.getTitleText(), mousePos);
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        showObjects(menuState.getButtonVector(), currButton, menuState.getTitleText());
                }
            }
        }
        mousePos = RenderWindow::getMousePos();
        window.cls();

        menuState.update(mousePos);
        menuState.draw(globalRenderer);

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
