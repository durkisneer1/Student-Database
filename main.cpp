#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "MenuState.hpp"
#include "SignUpState.hpp"
#include "LogInState.hpp"
#include "Wallpaper.hpp"

void launchErrorCheck()
{
    if (SDL_Init(SDL_INIT_VIDEO))
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
    if (TTF_Init() < 0)
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    SDL_StartTextInput();
}

void quitInit()
{
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_StopTextInput();
}

int main()
{
    launchErrorCheck();
    RenderWindow window("Student Database", (int)WIN_WIDTH, (int)WIN_HEIGHT);
    SDL_Renderer *globalRenderer = window.getRenderer();
    TTF_Font *font = TTF_OpenFont("../res/fonts/Daydream.ttf", 21);
    if (!font)
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

    Wallpaper wallpaper(window.loadImageInfo("../res/wallpaper.png"), 2);
    MenuState menuState(window, font);
    SignUpState signUpState(window, font);
    LogInState logInState(window, font);
    States currState = MENU;

    bool run = true;
    SDL_Event event;
    while (run)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                run = false;

            switch (currState)
            {
            case MENU:
                menuState.input(event, currState);
                break;
            case SIGNUP:
                signUpState.input(event, currState);
                break;
            case LOGIN:
                logInState.input(event, currState);
            }
        }

        window.cls();
        wallpaper.animateScroll(globalRenderer, 0.5f, 0.5f);

        switch (currState)
        {
        case MENU:
            menuState.update();
            menuState.draw(globalRenderer);
            break;
        case SIGNUP:
            signUpState.draw(globalRenderer);
            break;
        case LOGIN:
            logInState.draw(globalRenderer);
        }

        window.flip();
        SDL_Delay(16);
    }

    window.cleanUp();
    TTF_CloseFont(font);
    quitInit();

    return 0;
}
