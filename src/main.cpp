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

    Text titleText(Vector2f(WIN_WIDTH / 2 + 4, WIN_HEIGHT / 4 + 4), font, 2.5, globalRenderer, "Student Portal");

    EntityInfo wallpaperImageInfo = window.loadImageInfo("../res/wallpaper.png");
    Entity wallpaperEntity(Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 2), wallpaperImageInfo, 2);

    EntityInfo buttonImageInfo = window.loadImageInfo("../res/button.png");
    std::vector<Button> buttonImageVector = {
            Button(Vector2f(WIN_WIDTH / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, 2),
            Button(Vector2f(WIN_WIDTH * 3 / 4, WIN_HEIGHT * 2 / 3), buttonImageInfo, 2)
    };

    std::vector<Button> buttonTextVector = {
            Button(Vector2f(), window.loadTextInfo("Log In", font, {0, 43, 54}), 1.2),
            Button(Vector2f(), window.loadTextInfo("Sign Up", font, {0, 43, 54}), 1.2)
    };

    bool run = true;
    SDL_Event event;
    SDL_FPoint mousePos;
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                run = false;
            }
            for (Button &currButton: buttonImageVector) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.state == SDL_BUTTON_LEFT) {
                        hideObjects(buttonImageVector, currButton, titleText, mousePos);
                    }
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        showObjects(buttonImageVector, currButton, titleText);
                    }
                }
            }
        }
        mousePos = RenderWindow::getMousePos();

        window.cls();
        wallpaperEntity.animateScroll(globalRenderer, 0.5f, 0.5f);

        titleText.hide ? titleText.animateHide() : titleText.animateShow();
        if (!titleText.hidden) {
            titleText.animateWave(20.0f, 5.0f, false, true);
            titleText.draw(globalRenderer);
        }

        for (int i = 0; i < buttonImageVector.size(); i++) {
            Button &currButton = buttonImageVector[i];
            currButton.hide ? currButton.animateHide(WIN_HEIGHT) : currButton.animateShow();
            if (!currButton.hide)
                currButton.animateHover(mousePos);
            if (!currButton.hidden)
                currButton.draw(globalRenderer);

            buttonTextVector[i].setPos(currButton.getPos(), currButton.getDstRect());
            buttonTextVector[i].draw(globalRenderer);
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
