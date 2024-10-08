#include "Actor.h"
#include "Game.h"
#include "Component.h"
Actor::~Actor()
{
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}
//기본 크기 10배로
Actor::Actor(Game* game) : mState(EActive), 
	mPosition(Vector2(50.0f,50.0f)),
	mScale(10.0f),
	mRotation(0.0f),
	mGame(game)
{
	mGame->AddActor(this);
}

void Actor::Update(float deltaTime){
	if(mState == EActive){
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}
void Actor::UpdateComponents(float deltaTime){
	for(auto comp: mComponents){
		comp->Update(deltaTime);
	}
}
void Actor::UpdateActor(float deltaTime){
}

void Actor::AddComponent(Component* component){
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for(;
		iter != mComponents.end();
		++iter){
			if(myOrder < (*iter)->GetUpdateOrder()){
				break;
			}
		}
	mComponents.insert(iter, component);

}

void Actor::RemoveComponent(Component* component){
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	
	if(iter != mComponents.end()){
		mComponents.erase(iter);
	}
		
}