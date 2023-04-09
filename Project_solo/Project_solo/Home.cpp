#include "VD.h"
void Game::home() {
	bool new_game = true;
	while (true)
	{
		if (new_game)
		{
			SDL_Surface* imageSurface = IMG_Load("Assets/linkedlist.png");
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
			SDL_FreeSurface(imageSurface);
            SDL_Rect dstRect;
            dstRect.x = 100;
            dstRect.y = 100;
            dstRect.w = 200;
            dstRect.h = 200;

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_RenderPresent(renderer);

            // Vòng lặp chính
            SDL_Event event;
            bool quit = false;
            while (!quit) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }

            // Giải phóng bộ nhớ
            SDL_DestroyTexture(texture);
            IMG_Quit();
			//makeRectangle(50, 50, 200, 150, "Linked List", 25, "Green", false, true, true);
			//makeRectangle(255, 50, 200, 150, "Stack", 25, "Green", false, true, true);
		}
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		
	}
}