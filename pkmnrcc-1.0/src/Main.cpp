#include <iostream>
#include "./Constants.h"
#include "./Game.h"

int main(int argc, char *args[]) {

    Game* game = new Game();

    while (game->IsRunning()) {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    if (game != nullptr) {
        delete game;
        game = nullptr;
    }

    return 0;
}
