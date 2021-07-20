#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "randomMap.h"
#include "whiteSkeleton.h"
#include "playerTestScene.h"

//#include "slimeBlue.h"
//#include "slimeGreen.h"
//#include "slimeGold.h"

////카메라테스트용==========================
//struct tagPlayer
//{
//	image* img;
//	RECT rc;
//	int rc_width, rc_height;
//	float x, y;
//	bool isJump;
//	bool isGround;
//	float jumpPower;
//};
//
//struct tagCameraMove
//{
//	RECT rc;
//
//	float x, y;
//};
//========================================


#include "player.h"
class playGround : public gameNode
{
private:
	/*mapTool* _mapTool;
	randomMap* _map;
	whiteSkeleton* _skeleton;*/
	//slime* _slime;

	////카메라테스트용
	//tagPlayer _player;
	//tagPlayer _test;

	//player* _player;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
};

