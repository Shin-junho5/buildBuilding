#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
#include<string>
#include<random>
#include<ctime>

//#include<iostream>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BALL_SPEED_X 200.0f
#define BALL_SPEED_Y 250.0f

const int BALL_RANDOM_SPEED_MAX = 150;
const int GAP_PADDLE_SCREEN = 20;
const int THICKNESS = 15;
const Uint32 PADDLE_HEIGHT = THICKNESS * 10;
struct Vector2
{
    float x;
    float y;
};
struct Ball{
    Vector2 pos;
    Vector2 vel;    
};
struct GameState {
    int leftScore, rightScore;
    int CurrentMode; //mode 0: Start game, 1: plaing game 2: Left or Right Win
};
class Game
{
public:
    Game(){
        mWindow = 0;
        mIsRunning = true;
        mPaddlePos = {GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
        mPaddlePos2 = {SCREEN_WIDTH-GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
        //mBallPos = {500, 400};
        mTicksCount = 0;
      //  mBallVel = {-200.0f, 235.0f};
//      mGameState.leftScore = 0;
//      mGameState.rightScore = 0;
    }
    bool Initialize();
    void RunLoop();
	SDL_Rect RenderText(std::string text, int x, int y, int sort_method);
    void Shutdown();
	SDL_Texture *GetTextTexture(const char *text);
private:
	
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void ProcessInputLobby();
    void UpdateGameLobby();
    void GenerateOutputLobby();
    Vector2 mPaddlePos, mPaddlePos2;
    std::vector<Ball> ball;
    SDL_Window *mWindow;
    bool mIsRunning;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    int mPaddleDir[2];
    TTF_Font *mFont;
      bool KEYS[322]; 
      
    
};
