
#include "VD.h"
Game* gaem = nullptr;

int main(int argc, char* argv[])
{
	int a = 1;
	gaem = new Game();
	gaem->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 800, false);
	gaem->edge.x = 50;
	gaem->edge.y = 50;
	while (gaem->running()) {
			gaem->handleEvents();			
			gaem->render();
		}

	gaem->clean();
	return 0;
}