#include "Game.h"
SDL_Color White = {255, 255, 255};
GameState mGameState;
SDL_Rect START_TEXT_RECT;
SDL_Rect RESTART_TEXT_RECT;
Uint32 setBallPosStartPoint(Uint32 time, void* ballParam) {
	Ball *ball = static_cast<Ball *>(ballParam);
	if(time == 1000){
		
	(*ball).vel.x = -1*(BALL_SPEED_X + (rand()%BALL_RANDOM_SPEED_MAX));      
	(*ball).vel.y = -1*(BALL_SPEED_Y + (rand()%BALL_RANDOM_SPEED_MAX));
	}
	else{
//		fprintf(stderr, "hi: not 1000 speed x: %d y: %d\n", (*ball).pos.x, (*ball).pos.y);
		(*ball).vel.x = (BALL_SPEED_X + (rand()%BALL_RANDOM_SPEED_MAX));
        (*ball).vel.y = (BALL_SPEED_Y + (rand()%BALL_RANDOM_SPEED_MAX));
	}
  
  return 0;
}
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
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
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
    if (TTF_Init() < 0)
	{
   		SDL_Log("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
  	  	exit(1);
	}
    mFont = TTF_OpenFont("arial.ttf", 40);
	if (!mFont) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
		return false;
	}	
srand(static_cast<unsigned int>(time(NULL))); 

    ball.push_back(	Ball{
            Vector2{500, 400},
            Vector2{0,0}
        });
    setBallPosStartPoint(1000+(rand()%2), (void *)&ball[0]);
//    ball.push_back(
//	
//        Ball{
//            Vector2{500, 500},
//            Vector2{+200.0f, 235.0f}
//        });
//    ball.push_back(
//	
//        Ball{
//            Vector2{300, 500},
//            Vector2{+250.0f, 235.0f}
//        });
    mGameState.leftScore = 0;
      mGameState.rightScore = 0;
     // 322 is the number of SDLK_DOWN events
    
	for(int i = 0; i < 322; i++) { // init them all to false
	    KEYS[i] = false;
	}
	mGameState.CurrentMode = 0;
	
//	SDL_EnableKeyRepeat(0,0); 
std::string startText = "START";
    START_TEXT_RECT = RenderText(startText, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1);
    startText = "RESTART";
    RESTART_TEXT_RECT = RenderText(startText, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1);
    return true;
}
SDL_Texture *Game::GetTextTexture(const char *text){
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(mFont, text, White); 
	if (!surfaceMessage) {
		
   		SDL_Log("Couldn't make SDL_Surface: %s\n", SDL_GetError());
  	  	exit(1);
  	  	return NULL;
			
	}
// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	return Message;
}
void Game::Shutdown(){
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    TTF_CloseFont(mFont);
    TTF_Quit();
    SDL_Quit();
}
void Game::RunLoop(){
    while(mIsRunning){
    	if(mGameState.CurrentMode == 1){
    		
        ProcessInput();
        UpdateGame();
        GenerateOutput();
		}
		else{
		ProcessInputLobby();
        UpdateGameLobby();
        GenerateOutputLobby();	
		}
    }
}
void Game::ProcessInput(){
    SDL_Event event;
    Uint32 currentTime = SDL_GetTicks();
    static Uint32 leftLastUpDownPressTime[2] = {0,0};
    static Uint32 rightLastUpDownPressTime[2] = {0,0};
    static bool isLeftUpDownPress[2] = {0,0};
    static bool isRightUpDownPress[2] = {0,0};
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        case SDL_KEYDOWN:
            KEYS[event.key.keysym.scancode] = true;
            switch(event.key.keysym.scancode){
            	case SDL_SCANCODE_W:
            		if(leftLastUpDownPressTime[0] == 0){
			       	 	leftLastUpDownPressTime[0] =  currentTime;
					}
					else if (isLeftUpDownPress[0] && currentTime - leftLastUpDownPressTime[0] < 300) {  
			            mPaddlePos.y -= 100;
			            isLeftUpDownPress[0] = false;
			            leftLastUpDownPressTime[0] =  0;
			        }
			        
            		break;
            	case SDL_SCANCODE_S:
            		if(leftLastUpDownPressTime[1] == 0){
			       	 	leftLastUpDownPressTime[1] =  currentTime;
					}
            		else if (isLeftUpDownPress[1] && currentTime - leftLastUpDownPressTime[1] < 300) {  
			            mPaddlePos.y += 100;
			            isLeftUpDownPress[1] = false;
			            leftLastUpDownPressTime[1] =  0;
			        }
			        
			        //
            		break;
            	case SDL_SCANCODE_UP:
            		if(rightLastUpDownPressTime[0] == 0){
			       	 	rightLastUpDownPressTime[0] =  currentTime;
					}
            		else if (isRightUpDownPress[0] && currentTime - rightLastUpDownPressTime[0] < 300) {  
			            mPaddlePos2.y -= 100;
			            isRightUpDownPress[0] = false;
			            rightLastUpDownPressTime[0] =  0;
			        }
			        
			       // 
            		break;
            	case SDL_SCANCODE_DOWN:
            		if(rightLastUpDownPressTime[1] == 0){
			       	 	rightLastUpDownPressTime[1] =  currentTime;
					}
            		   else if (isRightUpDownPress[1] && currentTime - rightLastUpDownPressTime[1] < 300) {  
				            mPaddlePos2.y += 100;
				            isRightUpDownPress[1] = false;
				            rightLastUpDownPressTime[1] =  0;
				        }
				        
				       // 
            		break;
            	default:
            		break;
			}
            break;
        case SDL_KEYUP:
            KEYS[event.key.keysym.scancode] = false;
            switch(event.key.keysym.scancode){
            	case SDL_SCANCODE_W:
            		 if (currentTime - leftLastUpDownPressTime[0] < 300) {  
			            isLeftUpDownPress[0] = true;
			            leftLastUpDownPressTime[0] =  currentTime;
			        }
			        else if (currentTime - leftLastUpDownPressTime[0] >= 300) {  
			            isLeftUpDownPress[0] = false;
			            leftLastUpDownPressTime[0] =  0;
			        }
            		break;
            	case SDL_SCANCODE_S:
            		if (currentTime - leftLastUpDownPressTime[1] < 300) {  
			            isLeftUpDownPress[1] = true;
			            leftLastUpDownPressTime[1] =  currentTime;
			        }
			        else if (currentTime - leftLastUpDownPressTime[1] >= 300) {  
			            isLeftUpDownPress[1] = false;
			            leftLastUpDownPressTime[1] =  0;
			        }
            		break;
            	case SDL_SCANCODE_UP:
            		if (currentTime - rightLastUpDownPressTime[0] < 300) {  
			            isRightUpDownPress[0] = true;
			            rightLastUpDownPressTime[0] =  currentTime;
			        }
			        else if (currentTime - rightLastUpDownPressTime[0] >= 300) {  
			            isRightUpDownPress[0] = false;
			            rightLastUpDownPressTime[0] =  0;
			        }
            		break;
            	case SDL_SCANCODE_DOWN:
            		
            		   	if (currentTime - rightLastUpDownPressTime[1] < 300) {  
				            isRightUpDownPress[1] = true;
				            rightLastUpDownPressTime[1] =  currentTime;
				        }
				        else if (currentTime - rightLastUpDownPressTime[1] >= 300) {  
				            isRightUpDownPress[1] = false;
				            rightLastUpDownPressTime[1] =  0;
				        }
            		break;
            	default:
            		break;
			}
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

SDL_Rect Game::RenderText(std::string text, int x, int y, int sort_method) {
//	mGameState.rightScore = 0;
    
    //fprintf(stderr, scoreText.c_str());
    //const char *s = scoreText.c_str();
    //fprintf(stderr, "\n");
	SDL_Texture* textTexture = GetTextTexture(text.c_str());
    SDL_Color textColor = {255, 255, 255}; 
	int w, h;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);

    SDL_Rect renderQuad = {x, y, w, h}; 
    if(sort_method == 1){
    	renderQuad.x -=renderQuad.w/2;
    	renderQuad.y -=renderQuad.h/2;
	}
    SDL_RenderCopy(mRenderer, textTexture, NULL, &renderQuad);
    SDL_DestroyTexture(textTexture);
    return renderQuad;
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
        if(mPaddlePos.y < (PADDLE_HEIGHT/2.0f + THICKNESS)){
            mPaddlePos.y = PADDLE_HEIGHT/2.0f + THICKNESS;
        }
        else if(mPaddlePos.y > (SCREEN_HEIGHT - PADDLE_HEIGHT/2.0f - THICKNESS)){
            mPaddlePos.y = SCREEN_HEIGHT - PADDLE_HEIGHT/2.0f - THICKNESS;
        }
    }
    if(mPaddleDir[1] != 0) {
        mPaddlePos2.y += mPaddleDir[1] * 300.0f * deltaTime;
        if(mPaddlePos2.y < (PADDLE_HEIGHT/2.0f + THICKNESS)){
            mPaddlePos2.y = PADDLE_HEIGHT/2.0f + THICKNESS;
        }
        else if(mPaddlePos2.y > (SCREEN_HEIGHT - PADDLE_HEIGHT/2.0f - THICKNESS)){
            mPaddlePos2.y = SCREEN_HEIGHT - PADDLE_HEIGHT/2.0f - THICKNESS;
        }
    }
    //ball의 충돌 처리
    for(std::vector<Ball>::iterator ptr=ball.begin(); ptr != ball.end();ptr++){
        (*ptr).pos.x += (*ptr).vel.x * deltaTime;
        (*ptr).pos.y += (*ptr).vel.y * deltaTime;
//        Ball* tmpBall = &(*ptr);
        if((*ptr).pos.x <= THICKNESS/2 && (*ptr).vel.x < 0.0f){
            (*ptr).pos.x = SCREEN_WIDTH/2.0f;
            (*ptr).pos.y = SCREEN_HEIGHT/2.0f;
            (*ptr).vel.x *= -1; 
            mGameState.rightScore++;
            mPaddlePos = {GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
        mPaddlePos2 = {SCREEN_WIDTH-GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
            if(mGameState.rightScore>=5){
            	mGameState.CurrentMode = 2;
			}
			
			SDL_AddTimer(1001,setBallPosStartPoint,(void *)&(*ptr));
			
            (*ptr).vel.x = 0;
            (*ptr).vel.y = 0;
        }
        else if((*ptr).pos.x >= SCREEN_WIDTH-THICKNESS/2 && (*ptr).vel.x > 0.0f){
            (*ptr).pos.x = SCREEN_WIDTH/2.0f;
            (*ptr).pos.y = SCREEN_HEIGHT/2.0f;
//            fprintf(stderr, "ball speed x: %f\n", (*ptr).vel.x);
//            (*ptr).vel.x *= -1;
//            fprintf(stderr, "ball speed x: %f\n", (*ptr).vel.x);
            mGameState.leftScore++;
            mPaddlePos = {GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
        mPaddlePos2 = {SCREEN_WIDTH-GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
            if(mGameState.leftScore>=5){
            	mGameState.CurrentMode = 2;
			}
			
			SDL_AddTimer(1000,setBallPosStartPoint,(void *)&(*ptr));
			
            (*ptr).vel.x = 0;
            (*ptr).vel.y = 0;
        }
        if((*ptr).pos.y <= THICKNESS && (*ptr).vel.y < 0.0f){
            (*ptr).vel.y *= -1;
        }
        else if((*ptr).pos.y >= SCREEN_HEIGHT-THICKNESS && (*ptr).vel.y > 0.0f){
            (*ptr).vel.y *= -1;
        }
//        int diff = mPaddlePos.y - (*ptr).pos.y;
//        if (diff<0)
//            diff*=-1;
//        if(
//            diff <= PADDLE_HEIGHT / 2.0f &&
//            (*ptr).pos.x <= GAP_PADDLE_SCREEN+THICKNESS/2.0f && 
//            (*ptr).pos.x >= GAP_PADDLE_SCREEN-THICKNESS/2.0f &&
//            (*ptr).vel.x < 0.0f
//        ){
//            (*ptr).vel.x *= -1.0f;
//            (*ptr).vel.x *= 1.25f;
//            (*ptr).vel.y *= 1.25f;
//        }
        if(
		(mPaddlePos.y - PADDLE_HEIGHT / 2.0f <= (*ptr).pos.y - THICKNESS/2.0f &&
        mPaddlePos.y + PADDLE_HEIGHT / 2.0f >= (*ptr).pos.y - THICKNESS/2.0f) ||
        (mPaddlePos.y - PADDLE_HEIGHT / 2.0f <= (*ptr).pos.y + THICKNESS/2.0f &&
        mPaddlePos.y + PADDLE_HEIGHT / 2.0f >= (*ptr).pos.y + THICKNESS/2.0f) &&
        (*ptr).vel.x < 0.0f
		)
		{
        	if(
			(GAP_PADDLE_SCREEN-THICKNESS/2.0f <= (*ptr).pos.x - THICKNESS/2.0f && 
			GAP_PADDLE_SCREEN+THICKNESS/2.0f >= (*ptr).pos.x - THICKNESS/2.0f  ) ||
			(GAP_PADDLE_SCREEN-THICKNESS/2.0f <= (*ptr).pos.x + THICKNESS/2.0f && 
			GAP_PADDLE_SCREEN+THICKNESS/2.0f >= (*ptr).pos.x + THICKNESS/2.0f  )
			){
				
//            	SDL_Log("velocity %f = %f * %f\n", (*ptr).vel.x * 1.25f, (*ptr).vel.x, 1.25f);
        		(*ptr).vel.x *= -1.0f;
            	(*ptr).vel.x *= 1.25f;
            	(*ptr).vel.y *= 1.25f;
			}
		}
		if(
		(mPaddlePos2.y - PADDLE_HEIGHT / 2.0f <= (*ptr).pos.y - THICKNESS/2.0f &&
        mPaddlePos2.y + PADDLE_HEIGHT / 2.0f >= (*ptr).pos.y - THICKNESS/2.0f) ||
        (mPaddlePos2.y - PADDLE_HEIGHT / 2.0f <= (*ptr).pos.y + THICKNESS/2.0f &&
        mPaddlePos2.y + PADDLE_HEIGHT / 2.0f >= (*ptr).pos.y + THICKNESS/2.0f) &&
        (*ptr).vel.x > 0.0f
		)
		{
        	if(
			(SCREEN_WIDTH-GAP_PADDLE_SCREEN-THICKNESS/2.0f <= (*ptr).pos.x - THICKNESS/2.0f && 
			SCREEN_WIDTH-GAP_PADDLE_SCREEN+THICKNESS/2.0f >= (*ptr).pos.x - THICKNESS/2.0f  ) ||
			(SCREEN_WIDTH-GAP_PADDLE_SCREEN-THICKNESS/2.0f <= (*ptr).pos.x + THICKNESS/2.0f && 
			SCREEN_WIDTH-GAP_PADDLE_SCREEN+THICKNESS/2.0f >= (*ptr).pos.x + THICKNESS/2.0f  )
			){
//				SDL_Log("velocity %f = %f * %f\n", (*ptr).vel.x * 1.25f, (*ptr).vel.x, 1.25f);
        		(*ptr).vel.x *= -1.0f;
            	(*ptr).vel.x *= 1.25f;
            	(*ptr).vel.y *= 1.25f;
			}
		}

//        diff = mPaddlePos2.y - (*ptr).pos.y;
//        if (diff<0)
//           diff*=-1;
//        if(
//           diff <= PADDLE_HEIGHT / 2.0f &&
//          (*ptr).pos.x <= SCREEN_WIDTH-GAP_PADDLE_SCREEN+THICKNESS/2.0f && 
//          (*ptr).pos.x >= SCREEN_WIDTH-GAP_PADDLE_SCREEN-THICKNESS/2.0f &&
//          (*ptr).vel.x > 0.0f
//        ){
//         (*ptr).vel.x *= -1.0f;
//         (*ptr).vel.x *= 1.25f;
//         (*ptr).vel.y *= 1.25f;
//         }
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
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_Rect wall{
        0,
        0,
        SCREEN_WIDTH,
        THICKNESS
    };
    SDL_RenderFillRect(mRenderer, &wall);
    wall = {
        0,
        SCREEN_HEIGHT-THICKNESS,
        SCREEN_WIDTH,
        THICKNESS
    };
    SDL_RenderFillRect(mRenderer, &wall);
    for(std::vector<Ball>::iterator ptr=ball.begin(); ptr != ball.end();ptr++){
    SDL_Rect ball{
        static_cast<int>((*ptr).pos.x - THICKNESS/2),
        static_cast<int>((*ptr).pos.y - THICKNESS/2),
        THICKNESS,
        THICKNESS
    };
    SDL_RenderFillRect(mRenderer, &ball);
    }
    SDL_Rect paddle{
        static_cast<int>(mPaddlePos.x - THICKNESS/2),
        static_cast<int>(mPaddlePos.y - PADDLE_HEIGHT/2),
        THICKNESS,
        PADDLE_HEIGHT
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    SDL_Rect paddle2 = {
        static_cast<int>(mPaddlePos2.x - THICKNESS/2),
        static_cast<int>(mPaddlePos2.y - PADDLE_HEIGHT/2),
        THICKNESS,
        PADDLE_HEIGHT
    };
    SDL_RenderFillRect(mRenderer, &paddle2);
    std::string scoreText = "Score " + std::to_string(mGameState.leftScore) + " : " + std::to_string(mGameState.rightScore); 
    
    RenderText(scoreText, SCREEN_WIDTH/2, 50, 1);
    SDL_RenderPresent(mRenderer);
}
void Game::ProcessInputLobby(){
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
	int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        if(mGameState.CurrentMode == 0 &&
		mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) &&
		mouseX <= SCREEN_WIDTH /2+ START_TEXT_RECT.w/2 &&
		mouseX >= SCREEN_WIDTH /2- START_TEXT_RECT.w/2 &&
		mouseY <= SCREEN_HEIGHT /2+ START_TEXT_RECT.h/2 &&
		mouseY >= SCREEN_HEIGHT /2- START_TEXT_RECT.h/2){
//			fprintf(stderr, "button clicked\n");
			mGameState.CurrentMode = 1;
		}
		else if(mGameState.CurrentMode == 2 &&
		mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) &&
		mouseX <= SCREEN_WIDTH /2+ RESTART_TEXT_RECT.w/2 &&
		mouseX >= SCREEN_WIDTH /2- RESTART_TEXT_RECT.w/2 &&
		mouseY <= SCREEN_HEIGHT /2+ RESTART_TEXT_RECT.h/2 &&
		mouseY >= SCREEN_HEIGHT /2- RESTART_TEXT_RECT.h/2){
//			fprintf(stderr, "button clicked\n");
			mGameState.leftScore = 0;
			mGameState.rightScore = 0;
			mGameState.CurrentMode = 1;
			mPaddlePos = {GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
        mPaddlePos2 = {SCREEN_WIDTH-GAP_PADDLE_SCREEN, SCREEN_HEIGHT/2.0f};
		}
//        std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;

}
void Game::UpdateGameLobby(){
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if(deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
	
}
void Game::GenerateOutputLobby(){
	SDL_SetRenderDrawColor(
        mRenderer,
        0,
        0,
        0,
        255
    );
    SDL_RenderClear(mRenderer);
    TTF_Font *tmp_ttf;
    tmp_ttf = TTF_OpenFont("arial.ttf", 100);
	if (!tmp_ttf) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
		return ;
	}
	if(mGameState.CurrentMode == 0){
    	SDL_SetRenderDrawColor(
        mRenderer,
        255,
        0,
        0,
        255
	    );//TODO : not required code exist 
	    SDL_RenderFillRect(mRenderer, &START_TEXT_RECT);
	    std::string text = "PINGPONG";
	    RenderText(text, SCREEN_WIDTH/2, SCREEN_HEIGHT/2-100, 1);
	    std::string startText = "START";
	    RenderText(startText, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1);
	}
	else if(mGameState.CurrentMode == 2){
		SDL_SetRenderDrawColor(
        mRenderer,
        255,
        0,
        0,
        255
	    );//TODO : not required code exist 
	    SDL_RenderFillRect(mRenderer, &RESTART_TEXT_RECT);
	    std::string scoreText = "Score " + std::to_string(mGameState.leftScore) + " : " + std::to_string(mGameState.rightScore);
	    RenderText(scoreText, SCREEN_WIDTH/2, SCREEN_HEIGHT/2-170, 1);
	    
	    std::string winnerText = "Winner is " ;
	    if(mGameState.leftScore >=5){
	    	winnerText += "Left Player";
		}
		else{
			winnerText += "Right Player";
		}
	    RenderText(winnerText, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 120, 1);
	    std::string restartText = "RESTART" ;
	    RenderText(restartText, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1);
	}
    SDL_RenderPresent(mRenderer);
}
