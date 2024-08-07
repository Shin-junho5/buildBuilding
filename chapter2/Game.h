#pragma once
#include<vector>
#include "Actor.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<map>
#include "Component.h"
#include<unordered_map>
#include<string>
#include "SpriteComponent.h"
#include<algorithm>
class Game{
public:
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

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
    void LoadData();
    void UnloadData();
    SDL_Window* mWindow;
    bool mIsRunning;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::vector<SpriteComponent*> mSprites;
};