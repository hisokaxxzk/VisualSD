#include "VD.h"
coordinates home_btn[];
void Game::home(Game* home1) {
	bool new_game = true;
	while (home1->running())
	{
		if (new_game)
		{
			makeRectangle(50, 50, 250, 180, "Linked List", 25, "Light blue", false, true, true);
			makeRectangle(305, 50, 250, 180, "Stack", 25, "Heavy green", false, true, true);
			makeRectangle(560, 50, 250, 180, "Queue", 25, "Light green", false, true, true);
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
				enter_data();
				break;
			}
			if (mouseX >= 305 && mouseX <= 555 && mouseY >= 50 && mouseY <= 180) // Stack
			{
				enter_data_stack();
				break;
			}

		}
		
	}
}