#include "game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();

    if (game->Init("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false)) {
        while (game->IsRunning()) {
            game->HandleEvents();
            game->Update();
            game->Render();
        }
    }

    game->Clean();

    return 0;
}
