#include "VD.h"
coordinates home_btn[];
void Game::home() {
	bool new_game = true;
	while (true)
	{
		if (new_game)
		{
			makeRectangle(50, 50, 250, 180, "Linked List", 25, "Green", false, true, true);
			makeRectangle(305, 50, 250, 180, "Stack", 25, "Blue", false, true, true);
			makeRectangle(560, 50, 250, 180, "Queue", 25, "Grey", false, true, true);
			makeRectangle(815, 50, 250, 180, "Static Array", 25, "Orange", false, true, true);

			new_game = false;
		}
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			if (mouseX >= 50 && mouseX <= 250 && mouseY >= 50 && mouseY <= 180) // Linked list
			{
				enter_linked_list();
				break;
			}
		}
		
	}
}