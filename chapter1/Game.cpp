#include "Game.h"

bool Game::Initialize(){
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
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
    ball = {
        Ball{
            Vector2{500, 400},
            Vector2{-200.0f, 235.0f}
        },
        Ball{
            Vector2{500, 500},
            Vector2{+200.0f, 235.0f}
        },
        Ball{
            Vector2{300, 500},
            Vector2{+250.0f, 235.0f}
        }
    };
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
void Game::ProcessInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        
        default:
            break;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
    mPaddleDir[0] = 0;
    if(state[SDL_SCANCODE_W]){
        mPaddleDir[0] -= 1;
    }
    if(state[SDL_SCANCODE_S]){
        mPaddleDir[0] += 1;
    }
    mPaddleDir[1] = 0;
    if(state[SDL_SCANCODE_UP]){
        mPaddleDir[1] -= 1;
    }
    if(state[SDL_SCANCODE_DOWN]){
        mPaddleDir[1] += 1;
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
    if(mPaddleDir[0] != 0) {
        mPaddlePos.y += mPaddleDir[0] * 300.0f * deltaTime;
        if(mPaddlePos.y < (paddleH/2.0f + thickness)){
            mPaddlePos.y = paddleH/2.0f + thickness;
        }
        else if(mPaddlePos.y > (768.0f - paddleH/2.0f - thickness)){
            mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
        }
    }
    if(mPaddleDir[1] != 0) {
        mPaddlePos2.y += mPaddleDir[1] * 300.0f * deltaTime;
        if(mPaddlePos2.y < (paddleH/2.0f + thickness)){
            mPaddlePos2.y = paddleH/2.0f + thickness;
        }
        else if(mPaddlePos2.y > (768.0f - paddleH/2.0f - thickness)){
            mPaddlePos2.y = 768.0f - paddleH/2.0f - thickness;
        }
    }
    //ball의 충돌 처리
    for(std::vector<Ball>::iterator ptr=ball.begin(); ptr != ball.end();ptr++){
        (*ptr).pos.x += (*ptr).vel.x * deltaTime;
        (*ptr).pos.y += (*ptr).vel.y * deltaTime;
        if((*ptr).pos.x <= thickness/2 && (*ptr).vel.x < 0.0f){
            (*ptr).pos.x = 500;
            (*ptr).pos.y = 300;
            (*ptr).vel.x *= -1;
        }
        else if((*ptr).pos.x >= 1024-thickness/2 && (*ptr).vel.x > 0.0f){
            (*ptr).pos.x = 500;
            (*ptr).pos.y = 300;
            (*ptr).vel.x *= -1;
        }
        if((*ptr).pos.y <= thickness && (*ptr).vel.y < 0.0f){
            (*ptr).vel.y *= -1;
        }
        else if((*ptr).pos.y >= 768-thickness && (*ptr).vel.y > 0.0f){
            (*ptr).vel.y *= -1;
        }
        int diff = mPaddlePos.y - (*ptr).pos.y;
        if (diff<0)
            diff*=-1;
        if(
            diff <= paddleH / 2.0f &&
            (*ptr).pos.x <= 27.5f && 
            (*ptr).pos.x >= 12.5f &&
            (*ptr).vel.x < 0.0f
        ){
            (*ptr).vel.x *= -1.0f;
        }

        diff = mPaddlePos2.y - (*ptr).pos.y;
        if (diff<0)
           diff*=-1;
        if(
           diff <= paddleH / 2.0f &&
          (*ptr).pos.x <= 1024-20+7.5f && 
          (*ptr).pos.x >= 1024-20-7.5f &&
          (*ptr).vel.x > 0.0f
        ){
         (*ptr).vel.x *= -1.0f;
         }
    }
   // mBallPos.x += mBallVel.x * deltaTime;
   // mBallPos.y += mBallVel.y * deltaTime;
    // else if(mBallPos.x >= 1024-thickness && mBallVel.x > 0.0f){
    //     mBallVel.x *= -1;
    // // }

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
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect wall{
        0,
        0,
        1024,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &wall);
    wall = {
        0,
        768-15,
        1024,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &wall);
    for(std::vector<Ball>::iterator ptr=ball.begin(); ptr != ball.end();ptr++){
    SDL_Rect ball{
        static_cast<int>((*ptr).pos.x - thickness/2),
        static_cast<int>((*ptr).pos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);
    }
    SDL_Rect paddle{
        static_cast<int>(mPaddlePos.x - thickness/2),
        static_cast<int>(mPaddlePos.y - thickness*10/2),
        thickness,
        paddleH
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    SDL_Rect paddle2 = {
        static_cast<int>(mPaddlePos2.x - thickness/2),
        static_cast<int>(mPaddlePos2.y - thickness*10/2),
        thickness,
        paddleH
    };
    SDL_RenderFillRect(mRenderer, &paddle2);
    SDL_RenderPresent(mRenderer);
}