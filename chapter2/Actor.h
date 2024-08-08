#pragma once
#include <vector>

#include "Math.h"

//유니티의 게임 오브젝트 같은 것.
class Actor
{
    public:
    enum State{
        EActive,
        EPaused,
        EDead
    };
    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);
    
    //하이브리드 방식으로 컴포넌트 추가 제거
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

    //Getter와 Setter    
    State GetState() const { return mState; }
    float GetScale(){ return mScale;}
    Vector2 GetPosition(){ return mPosition;}
    float GetRotation(){ return mRotation; }

    const void SetPosition(const Vector2& pos) {mPosition = pos;}
    void SetScale(float scale) {mScale = scale; }
    void SetRotation(float rotation) {mRotation = rotation;}
    void SetState(State state) { mState = state; }

    class Game * GetGame() {return mGame;}

private:
    State mState;
    Vector2 mPosition;
    float mScale;
    float mRotation;
    std::vector<class Component*> mComponents;
    class Game* mGame;
    
};
