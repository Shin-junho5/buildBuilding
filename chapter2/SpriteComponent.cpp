#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(class Actor* owner, int darwOrder = 100){

}
void SpriteComponent::SetTexture(SDL_Texture* texture){
    mTexture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr,
    &mTexWidth, &mTexHeight);
}
void SpriteComponent::Draw(SDL_Renderer* renderer){
    if(mTexture){
        SDL_Rect r;
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
        r.x = static_cast<int>(mOwner->GetPostion().x - r.w / 2);
        r.y = static_cast<int>(mOwner->GetPostion().y - r.h / 2);

        SDL_RenderCopyEx(renderer,
        mTexture,
        nullptr,
        &r,
        -Math::ToDegrees(mOwner->GetRotation()),
        nullptr,
        SDL_FLIP_NONE);
    }
}