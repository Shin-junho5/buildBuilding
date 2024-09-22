#include "Player.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
Player::Player(Game* game)
    :Actor(game)
	,mLRSpeed(0.0f)
	,mUDSpeed(0.0f)
{
    AnimSpriteComponent* asc = new AnimSpriteComponent(this, 100000);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/player.png"),\
	};
	asc->SetAnimTextures(anims);
	SetScale(0.1f);
	//printf("player: %d\n", asc->GetDrawOrder());
}
void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mLRSpeed * deltaTime;
	pos.y += mUDSpeed * deltaTime;
	// Restrict position to left half of screen
	//SetPosition(pos);
}

void Player::ProcessKeyboard(const uint8_t* state)
{
	mLRSpeed = 0.0f;
	mUDSpeed = 0.0f;
	// right/left
	if(state[SDL_SCANCODE_Q]){
			printf("player: %f\n", GetScale());
	
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
