#pragma once
#include "Actor.h"
#include <SDL2/SDL.h>
class Player : public Actor{
public:
    Player(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mLRSpeed; }
	float GetDownSpeed() const { return mUDSpeed; }
private:
    float mLRSpeed;
	float mUDSpeed;
};