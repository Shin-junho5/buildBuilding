#include "Game.h"

bool Game::Initialize(){
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    sdlResult = IMG_Init(IMG_INIT_JPG);
    if(sdlResult != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow(
        "Game Programming in C++ (Chapter 1)",
        100,
        100,
        1024,
        768,
        0
    );
    if(!mWindow){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if(!mRenderer){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    return true;
}
void Game::Shutdown(){
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}
void Game::RunLoop(){
    while(mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}
void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(
        mRenderer,
        0,
        0,
        255,
        255
    );
    SDL_RenderClear(mRenderer);
    auto iter = mSprites.begin();
    for( ; iter != mSprites.end(); ++iter){
        (*iter)->Draw(mRenderer);
    }
    SDL_RenderPresent(mRenderer);
}
void Game::AddActor(Actor* actor){
    if(mUpdatingActors){
        mPendingActors.emplace_back(actor);
    }
    else{
        mActors.emplace_back(actor);
    }
}
void Game::UpdateGame(){
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if(deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
    mUpdatingActors = true;
    for(auto actor : mActors){
        actor-> Update(deltaTime);
    }
    mUpdatingActors = false;
    for(auto pending : mPendingActors){
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;
    for(auto actor : mActors){
        if (actor->GetState() == Actor::EDead){
            deadActors.emplace_back(actor);
        }
    }

    for(auto actor : deadActors){
        delete actor;
    }
}
SDL_Texture* Game::LoadTexture(const char* fileName){
    SDL_Surface* surf = IMG_Load(fileName);
    if(!surf){
        SDL_Log("Failed to load texture file %s", fileName);
        return nullptr;
    }
    SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if(!text)
    {
        SDL_Log("Filed to convert surface to texture for %s", fileName);
        return nullptr;
    }
    return text;
}
SDL_Texture* Game::GetTexture(const std::string& fileName){
    auto it = mTextures.find(fileName);
    if (it != mTextures.end()) {
        return it->second;
    } else {
        // 텍스처가 맵에 존재하지 않는 경우 로드하고 맵에 추가
        SDL_Texture* texture = LoadTexture(fileName.c_str());
        mTextures[fileName] = texture;
        return texture;
    }
}
void Game::AddSprite(SpriteComponent* sprite){
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for( ; iter != mSprites.end(); ++iter){
        if(myDrawOrder < (*iter)->GetDrawOrder()){
            break;
        }
    }
    mSprites.insert(iter,sprite);
}