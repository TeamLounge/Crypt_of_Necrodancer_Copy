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
	image* _imageName;	  // UI �̹���
	RECT _rc;			  // ��Ʈ
	ITEMTYPE _itemType;
	int _numMax;
	float _range;
	int _alpha;


	int _currentFrameX;
	int _currentFrameY;   // ������ ��ȣ ����

	float _elapsedSec;    // ������ ������

	float _centerX, _centerY;		  // ��Ʈ �߽���ǥ Ȯ�ο�
	float _positionX, _positionY;
	float _rectX;					//ī�޶� ��� ��ǥ Ȯ�ο�
	float _cameraCenterX;			//ī�޶� �߽���ǥ�κ��� ��Ʈ�� �Ÿ� (������)
	float _cameraLeftX;
	float _cameraRectX;

	float _moveSpeed;

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
	void moveY(float speed);
	void draw();
	void imgDraw();
	void alphaRender();

	image* getImg() { return _imageName; }

	void setCenterX(float centerX) { _centerX = centerX; }
	void setCenterY(float centerY) { _centerY = centerY; }
	float getCenterX() { return _centerX; }
	float getCenterY() { return _centerY; }

	void setPositionX(float positionX) { _positionX = positionX; }
	void setPositionY(float positionY) { _positionY = positionY; }
	float getPositionX() { return _positionX; }
	float getPositionY() { return _positionY; }

	void setRect(RECT rc) { _rc = rc; }
	RECT getRect() { return _rc; }

	void setCurrentFrameX(int currentFrameX) { _currentFrameX = currentFrameX; }
	int getCurrentFrameX() { return _currentFrameX; }

	void setCurrentFrameY(int currentFrameY) { _currentFrameY = currentFrameY; }
	int getCurrentFrameY() { return _currentFrameY; }

	void setRectX(float rectX) { _rectX = rectX; }
	void setCameraLeftX(float cameraLeftX) { _cameraLeftX = cameraLeftX; }
	void setCameraCenterX(float cameraCenterX) { _cameraCenterX = cameraCenterX; }
	
	float getRectX() { return _rectX; }
	float getCameraLeftX() { return _cameraLeftX; }
	float getCameraCenterX() { return _cameraCenterX; }

	void setItemType(ITEMTYPE itemtype) { _itemType = itemtype; }
	ITEMTYPE getItemType() { return _itemType; }

	int getAlpha() { return _alpha; }
	void setAlpha(int alpha) { _alpha = alpha; }

	float getRange() { return _range; }
	void setRange(float range) { _range = range; }

	int getNumMax() { return _numMax; }
	void setNumMax(int numMax) { _numMax = numMax; }

	float getMoveSpeed() { return _moveSpeed; }
	void setMoveSpeed(float moveSpeed) { _moveSpeed = moveSpeed; }
};

