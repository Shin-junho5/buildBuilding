#pragma once
#include "Actor.h"
#include<SDL2/SDL.h>
#include "Math.h"
#include "MapSpriteComponent.h"
//유니티의 게임 오브젝트 같은 것.
class Camera : public Actor{
public:
    Camera(class Game* game);
	Camera(class Game* game, class Actor* actor);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	void CameraControll(Vector2& Camera, Vector2& Chara_s, Vector2& Chara, Vector2& BG);

	float GetRightSpeed() const { return mLRSpeed; }
	float GetDownSpeed() const { return mUDSpeed; }
	Vector2 GetCameraPos() const {return mCameraPos;}
	Vector2 GetCharaScreenPos() const {return mCameraPos;}
	Vector2 GetBG_pos() const {return mCameraPos;}
	Vector2 GetCharaPos() const {return mCameraPos;}
private:
    float mLRSpeed;
	float mUDSpeed;
	
	Vector2 mCameraPos, mCharaScreenPos, mBG_pos, mCharaPos;
	class Actor* mActor; // Camera focus on mActor
	int mBG_width, mBG_height;
	int mActor_width, mActor_height;
};