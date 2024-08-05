#include "AnimSpriteComponent.h"

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures){
    mCurrFrame = 0;
    this->SetTexture();
}