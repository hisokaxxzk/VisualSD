#include "VD.h"
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    color["Green"] = { 60,179,113 };
    color["Black"] = { 0,0,0 };
    color["White"] = { 255,255,255 };
    color["Blue"] = { 100,149,237 };
    color["Orange"] = { 255,165,0 };
    color["Grey"] = { 100,100,100 };
    color["Yellow"] = { 251,177,23 };
    color["Purple"] = { 178,164,255 };
    color["Light red"] = { 255,180,180 };
    color["Light orange"] = { 244,177,131 };
    color["Light yellow"] = { 255,217,102 };
    color["Heavy blue"] = { 0, 66, 90 };
    color["Heavy green"] = { 31,138,112 };
    color["Light green"] = { 191,219,56 };
    color["Light blue"] = { 80, 150, 171 };
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            std::cout << "Renderer created" << std::endl;

        }
        isRunning = true;
    }
    else {
        isRunning = false;
    }
    SDL_RenderClear(renderer);
}