#include "Camera.h"
#include "SpriteComponent.h"
#include "Game.h"

extern  const int VIEW_WIDTH;
extern  const int VIEW_HEIGHT;
Camera::Camera(Game* game)
    :Actor(game)
	,mLRSpeed(0.0f)
	,mUDSpeed(0.0f)
	,mActor(NULL)
{
    SpriteComponent* asc = new SpriteComponent(this, 0);
	SDL_Texture* BGs = \
		game->GetTexture("Assets/background.png");
	asc->SetTexture(BGs);
    SetScale(1.0f);
	mBG_width = asc->GetTexWidth();
    printf("--%d\n", mBG_width);
}
int mapTile[] = {
			   0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
			   6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8
			   };
std::vector<Vector2> mapPos = {Vector2(0, 0), Vector2(16, 0), Vector2(32,0 ),
								Vector2(0, 16), Vector2(16, 16), Vector2(32, 16),
								Vector2(0, 32), Vector2(16, 32), Vector2(32, 32)
								};
Camera::Camera(Game* game, Actor* actor)
    :Actor(game)
	,mLRSpeed(0.0f)
	,mUDSpeed(0.0f)
	,mActor(actor)
{
	MapSpriteComponent* map = new MapSpriteComponent(this);
	SDL_Texture* mapTexture = game->GetTexture("Assets/Grass.png");
	map->SetTexture(mapTexture);
	
	map->SetMap(mapTile,(Uint16)50,(Uint16)50);
	map->SetMapPos(mapPos);
	map->SetChipSize((Uint16)16);
	int mapChipScale = 3;
	map->SetChipScale(mapChipScale);
	/*
    SpriteComponent* bg = new SpriteComponent(this, 0);
	SDL_Texture* BGs = \
		game->GetTexture("Assets/background.png");
	bg->SetTexture(BGs);
	mBG_width = bg->GetTexWidth();
	mBG_height = bg->GetTexHeight();
	*/
    SetScale(1.0f);
	mBG_width = 16 *50 * mapChipScale;
	mBG_height =16 *50 * mapChipScale;
	mActor_width = 684;
	mActor_height = 1289;

	mCameraPos.x = VIEW_WIDTH / 2.0f;				// 카메라 초기 위치 
	mBG_pos.x = 0.0f;							// 배경 초기 위치 
	mCharaScreenPos.x = VIEW_WIDTH / 2.0f;
	mCharaPos.x = VIEW_WIDTH / 2.0f;

	mCameraPos.y = VIEW_HEIGHT / 2.0f;				// 카메라 초기 위치 
	mBG_pos.y = 0.0f;							// 배경 초기 위치 
	mCharaScreenPos.y = VIEW_HEIGHT / 2.0f;
	mCharaPos.y = VIEW_HEIGHT / 2.0f;

}
const float SCROLL_DIF = 80.0f;
const float SCROLL_DIF_Y = 40.0f;
void Camera::CameraControll(Vector2& vCamera, Vector2& vChara_s, Vector2& vChara, Vector2& vBG){
	int ActorLength, VIEW_LENGTH, BG_length;
	float Camera, Chara_s, Chara, BG;
	for(int i=0; i<2; i++){
		if(i==0){
			ActorLength = (mActor->GetScale()*mActor_width) / 2.0f;
			VIEW_LENGTH = VIEW_WIDTH;
			BG_length = mBG_width;
			Camera = vCamera.x;
			Chara_s = vChara_s.x;
			Chara = vChara.x;
			BG = vBG.x;
		}
		else{
			ActorLength = (mActor->GetScale()*mActor_height) / 2.0f;
			VIEW_LENGTH = VIEW_HEIGHT;
			BG_length = mBG_height;
			Camera = vCamera.y;
			Chara_s = vChara_s.y;
			Chara = vChara.y;
			BG = vBG.y;
		}

		if(Chara_s < 0.0f + ActorLength){//캐릭터 필드상 위치 조정. 최대 배경의 길이 까지
			Chara_s = 0.0f + ActorLength;
		}
		else if(Chara_s > (float)BG_length - ActorLength){
			Chara_s = (float)BG_length - ActorLength;
		}

		if ( SCROLL_DIF < Chara_s - Camera ) {		// 카메라가 왼쪽으로 접근하는지 체크 
			Camera = Chara_s - SCROLL_DIF;
		}
		else if ( Camera - Chara_s > SCROLL_DIF ) {		// 카메라가 오른쪽으로 접근하는지 체크 
			Camera = Chara_s + SCROLL_DIF;
		}
		if ( Camera < VIEW_LENGTH / 2.0f ) {					// 카메라 왼쪽 이동 한계 
			Camera = VIEW_LENGTH / 2.0f;
		}
		if ( Camera > BG_length- VIEW_LENGTH / 2.0f ) {	// 카메라 오른쪽 이동 한계
			Camera = BG_length - VIEW_LENGTH / 2.0f;
		}
		Chara = Chara_s - Camera + VIEW_LENGTH / 2.0f;
		BG = BG_length / 2.0f - (Camera - VIEW_LENGTH / 2.0f);
		if(i==0){
			vCamera.x = Camera;
			vChara_s.x = Chara_s;
			vChara.x = Chara;
			vBG.x = BG;
		}
		else{
			vCamera.y = Camera ;
			vChara_s.y = Chara_s ;
			vChara.y = Chara;
			vBG.y = BG;
		}
	}
}
void Camera::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	mCharaScreenPos.x += mLRSpeed * deltaTime;
	mCharaScreenPos.y += mUDSpeed * deltaTime;

	CameraControll(mCameraPos, mCharaScreenPos, mCharaPos, mBG_pos);
	
	mActor->SetPosition(mCharaPos);
	SetPosition(mBG_pos);

}
const int CHARAC_SPEED = 10;
void Camera::ProcessKeyboard(const uint8_t* state)
{
	mLRSpeed = 0.0f;
	mUDSpeed = 0.0f;
	if (state[SDL_SCANCODE_Q])
	{
		printf("x: %f y: %f\n", mCharaScreenPos.x, mCharaScreenPos.y);
		printf("height: %f\n", mActor_height* mActor->GetScale());
		/*
		SDL_Rect r;
	 	r.w = static_cast<int>(mBG_width * GetScale());
        r.h = static_cast<int>(mBG_height * GetScale());
        r.x = static_cast<int>(GetPosition().x - r.w / 2);
        r.y = static_cast<int>(GetPosition().y - r.h / 2);
		printf("r.x r.y r.w r.h %d %d %d %d\n", r.x, r.y, r.w, r.h);
		printf("mCamera_x :%f\n", mCamera_x);
		printf("mActor_y :%f\n", mActor->GetPosition().y);
		printf("BG_y: %f\n", GetPosition().y);
		*/
	}
	if (state[SDL_SCANCODE_D])
	{
		mLRSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mLRSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mUDSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mUDSpeed -= 300.0f;
	}
}
