#pragma once
#include "gameNode.h"

enum ITEMTYPE
{
	SHOVEL, ATTACK, BODY, HEAD, FEET, TORCH,
	RING, KEY, ITEM, PACK, PACK2, BOMB, ONOFF,
	RELOAD, SPELL, SPELL2, SPELL3, THROW, PRESS,
	HOLSTER, HOLSTER2, NONE_TYPE
};

class UI : public gameNode
{
protected:
	image* _imageName;	  // UI 이미지
	RECT _rc;			  // 렉트
	ITEMTYPE _itemType;

	int _currentFrameX;
	int _currentFrameY;   // 프레임 번호 변수

	float _elapsedSec;    // 프레임 돌릴용

	float _centerX, _centerY;		  // 렉트 중심좌표 확인용
	float _positionX, _positionY;
	float _rectX;					//카메라 대비 좌표 확인용
	float _cameraCenterX;
	float _cameraLeftX;
	float _cameraRectX;

public:
	UI();
	~UI();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float frameSpeed);
	void render();

	void frameMove();
	void move(float speed);
	void draw();
	void imgDraw();

	image* getImg() { return _imageName; }

	void setCenterX(float centerX) { _centerX = centerX; }
	float getCenterX() { return _centerX; }
	float getCenterY() { return (_rc.top + _rc.bottom) / 2; }

	void setPositionX(float positionX) { _positionX = positionX; }
	void setPositionY(float positionY) { _positionY = positionY; }
	float getPositionX() { return _positionX; }
	float getPositionY() { return _positionY; }

	void setRect(RECT rc) { _rc = rc; }
	RECT getRect() { return _rc; }

	void setCurrentFrameX(int currentFrameX) { _currentFrameX = currentFrameX; }
	int getCurrentFrameX() { return _currentFrameX; }

	void setRectX(float rectX) { _rectX = rectX; }
	void setCameraLeftX(float cameraLeftX) { _cameraLeftX = cameraLeftX; }
	void setCameraCenterX(float cameraCenterX) { _cameraCenterX = cameraCenterX; }
	
	float getRectX() { return _rectX; }
	float getCameraLeftX() { return _cameraLeftX; }
	float getCameraCenterX() { return _cameraCenterX; }

	void setItemType(ITEMTYPE itemtype) { _itemType = itemtype; }
	ITEMTYPE getItemType() { return _itemType; }
};

