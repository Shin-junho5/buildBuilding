#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
    , mState(EMultiImage)
    , mHorizonLength(1)
    , mVerticalLength(1)
{
}
void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures){
    mAnimTextures = textures;
    if(mAnimTextures.size() > 0){
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}
void AnimSpriteComponent::Update(float deltaTime){
    SpriteComponent::Update(deltaTime);

    if(mAnimTextures.size() > 0){
        mCurrFrame += mAnimFPS * deltaTime;

        while(mCurrFrame >= mAnimTextures.size())
        {
            mCurrFrame -= mAnimTextures.size();
        }
        switch(mState)
        {
            case EMultiImage:
                SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
                break;
            case EOneLineSheet:
                break;
            case EMultiLineSheet:
                break;
            default:
                break;
        }
        
    }
}