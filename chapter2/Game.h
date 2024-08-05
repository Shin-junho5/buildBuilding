#pragma once
#include<vector>
#include "Actor.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<map>
#include "Component.h"
#include<unordered_map>
#include<string>
class Game{
public:
    void AddActor(Actor* actor);
    void AddSprite(SpriteComponent* sprite);
    void UpdateGame();
    Game(){
        mWindow = nullptr;
        mIsRunning = true;
        mTicksCount = 0;
    }
    bool Initialize();
    void RunLoop();
    void Shutdown();
    SDL_Texture* LoadTexture(const char* fileName);
    SDL_Texture* GetTexture(const std::string& fileName);
private:
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    bool mUpdatingActors;
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    SDL_Window* mWindow;
    bool mIsRunning;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::vector<SpriteComponent*> mSprites;
};