#pragma once
#include "SpriteComponent.h"
#include<vector>
class AnimSpriteComponent : public SpriteComponent{
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
    void Update(float deltaTime) override;
    enum State{
        EMultiImage,
        EOneLineSheet,
        EMultiLineSheet
    };


    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
    float GetAnimFPS() const {return mAnimFPS;}
    void SetAnimFPS(float fps) {mAnimFPS = fps;}
    
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    void SetHorizonLength(Uint16 length) {mHorizonLength = length;}
    Uint16 GetHorizonLength() {return mHorizonLength;}
    void SetVerticalLength(Uint16 length) {mAnimFPS = length;}
    Uint16 GetVerticalLength() {return mVerticalLength;};
private:
    std::vector<SDL_Texture*> mAnimTextures;
    float mCurrFrame;
    float mAnimFPS;
    State mState;
    Uint16 mHorizonLength;
    Uint16 mVerticalLength;
};