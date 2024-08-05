#pragma once
#include <vector>
struct Vector2
{
    float x;
    float y;
};

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
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    State GetState() const { return mState; }
    float GetScale(){ return mScale;}
    Vector2 GetPostion(){ return mPosition;}
    float GetRotation(){ return mRotation; }
private:
    State mState;
    Vector2 mPosition;
    float mScale;
    float mRotation;
    std::vector<class Component*> mComponents;
    class Game* mGame;
    
};