#include "MapSpriteComponent.h"
extern const int VIEW_WIDTH, VIEW_HEIGHT;
MapSpriteComponent::MapSpriteComponent(Camera* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
    ,mCamera(owner)
    ,mMapArray(NULL)
    ,mChipScale(0)
{
}
void MapSpriteComponent::Update(float deltaTime){
    SpriteComponent::Update(deltaTime);
    Vector2 pos = mOwner->GetPosition();

    int mActor_width = 684;
	int mActor_height = 1289;

//        printf("--");
    mCameraPos = mCamera->GetCameraPos();
   // mCameraPos.x -= (CHIP_LENGTH * mChipScale)/ 4.0f ;
   // mCameraPos.y -= (CHIP_LENGTH * mChipScale)/ 2.0f;
    mMapPos.x = VIEW_WIDTH  / 2.0f - mCameraPos.x + CHIP_LENGTH * mChipScale / 2;		// 맵 표시 좌표
	mMapPos.y = VIEW_HEIGHT / 2.0f - mCameraPos.y + CHIP_LENGTH * mChipScale / 2;
    mBaseChip_x = ( int )-mMapPos.x / (CHIP_LENGTH * mChipScale);  // 그릴 좌측 상단 칩 번호
    mBaseChip_y = ( int )-mMapPos.y / (CHIP_LENGTH * mChipScale);
	mBasePos.x = mMapPos.x + mBaseChip_x * (CHIP_LENGTH * mChipScale);	// 그릴 좌측 상단 칩 좌표
	mBasePos.y = mMapPos.y + mBaseChip_y * (CHIP_LENGTH * mChipScale);
	mChipNum_x = VIEW_WIDTH  / (CHIP_LENGTH * mChipScale) + 1 + 2;		// 그릴 칩 수_가로 
	mChipNum_y = VIEW_HEIGHT / (CHIP_LENGTH * mChipScale) + 1 + 2;		// 그릴 칩 수_세로 

}
void MapSpriteComponent::Draw(SDL_Renderer* renderer){
	
    /*
    */
    if(mMapArray == NULL){
        return ;
    }
	mChipPos.y = mBasePos.y;
	for (int i = 0; i < mChipNum_y; i++ ) {
		mChipPos.x = mBasePos.x;
		for (int j = 0; j < mChipNum_x; j++ ) {
            
          //  printf("%d,", mMapArray[(int)((mBaseChip_y + i)*(int)mMapsize_x + (mBaseChip_x + j))]);
            //여기
                if((mBaseChip_y + i)*mMapsize_x + (mBaseChip_x + j)>=mMapsize_x * mMapsize_y || (mBaseChip_y + i)*mMapsize_x + (mBaseChip_x + j) < 0){
                    continue;
                }
                DrawMapChip( mChipPos,
						 mMapArray[(mBaseChip_y + i)*mMapsize_x + (mBaseChip_x + j)],
                         renderer );
		/*	
            printf("%d,%d, %d, %d\n", (mBaseChip_y), (mBaseChip_x), mChipNum_y, mChipNum_x);
                         */
			mChipPos.x += CHIP_LENGTH * mChipScale;
		}
       // printf("\n");
		mChipPos.y += CHIP_LENGTH * mChipScale;
	}

}
void MapSpriteComponent::DrawMapChip(Vector2 pos,int tileMap, SDL_Renderer* renderer){
    if(mTexture){
        SDL_Rect r;
        r.w = static_cast<int>(CHIP_LENGTH * mChipScale);
        r.h = static_cast<int>(CHIP_LENGTH * mChipScale);
        r.x = static_cast<int>(pos.x - r.w / 2);
        r.y = static_cast<int>(pos.y - r.h / 2);
        SDL_Rect src = {static_cast<int>(mSrcMapPos[tileMap].x), static_cast<int>(mSrcMapPos[tileMap].y), CHIP_LENGTH, CHIP_LENGTH};
        SDL_RenderCopyEx(renderer,
        mTexture,
        &src,
        &r,
        -Math::ToDegrees(mOwner->GetRotation()),
        nullptr,
        SDL_FLIP_NONE);
    }
}