#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "mapGenerator.h"
#include "playerTestScene.h"
#include "slimeGreen.h"

//#include "slimeBlue.h"
//#include "slimeGold.h"

////ī�޶��׽�Ʈ��==========================
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
	mapTool* _mapTool;
	mapGenerator* _map;
	slimeGreen* _slime;

	////ī�޶��׽�Ʈ��
	//tagPlayer _player;
	//tagPlayer _test;

	player* _player;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addImage();
};

