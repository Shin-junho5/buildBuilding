#include "Game.h"

int WINAPI WinMain(){
    Game game;
    bool success = game.Initialize();
    if(success){
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
