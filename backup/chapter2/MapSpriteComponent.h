#pragma once
#include "SpriteComponent.h"
#include<vector>
#include"Game.h"
#include "Camera.h"
class MapSpriteComponent : public SpriteComponent{
public:
    MapSpriteComponent(class Camera* owner, int drawOrder = 100);
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetMapPos(std::vector<Vector2> mapPos){ mSrcMapPos = mapPos;} // 필수 1
    void SetMap(int* mapArray, Uint16 mapSize_x, Uint16 mapSize_y) {mMapArray = mapArray; 
                                                                mMapsize_x = mapSize_x; 
                                                                mMapsize_y = mapSize_y;} //필수 2
    void SetChipSize(Uint16 chipSize) {CHIP_LENGTH = chipSize;}
    void SetChipScale(int chipScale) {mChipScale = chipScale;}
    int GetChipScale()  const {return mChipScale;}


    void DrawMapChip(Vector2 chipPos, int tileIndex, SDL_Renderer* renderer);

private:
    class Camera* mCamera;
    std::vector<Vector2> mSrcMapPos;
    Uint16 mMapsize_x, mMapsize_y, CHIP_LENGTH;
    int* mMapArray;
    Vector2 mMapPos, mCameraPos, mChipPos, mBasePos;
    int mChipNum_x,mChipNum_y, mBaseChip_x,mBaseChip_y;
    int mChipScale;
};