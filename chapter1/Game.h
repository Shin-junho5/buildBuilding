#include<SDL2/SDL.h>
#include<vector>
const int thickness = 15;
const Uint32 paddleH = thickness*10;
struct Vector2
{
    float x;
    float y;
};
struct Ball{
    Vector2 pos;
    Vector2 vel;
};
class Game
{
public:
    Game(){
        mWindow = nullptr;
        mIsRunning = true;
        mPaddlePos = {20, 350};
        mPaddlePos2 = {1024-20, 350};
        //mBallPos = {500, 400};
        mTicksCount = 0;
      //  mBallVel = {-200.0f, 235.0f};
    }
    bool Initialize();
    void RunLoop();

    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    Vector2 mPaddlePos, mPaddlePos2;
    std::vector<Ball> ball;
    SDL_Window* mWindow;
    bool mIsRunning;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    int mPaddleDir[2];
    
};