#pragma once
#include "gameNode.h"
#include "randomMap.h"
//#include "aStarTest.h"

//aStar �ʿ����

enum DIRECTION
{
	NONE,
	LEFT,
	UP,
	RIGHT,
	DOWN
};

class slime : public gameNode
{
private:
	randomMap * _map;
	DIRECTION _direction;

	image * _img;
	RECT _rc;

	float _x, _y;	//���� ��ǥ��
	float _shadowX, _shadowY;
	int _hp;

	int _count;
	int _index;
	int _currentFrameX, _currentFrameY;

	bool _isRight;	//�⺻ ���� �����̾�?

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void slimeMove();

	//get
	///////////////////////////////////////////////
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }
	virtual float getShadowX() { return _shadowX; }
	virtual float getShadowY() { return _shadowY; }
	virtual image * getImage() { return _img; }
	inline RECT getRect() { return _rc; }

	//set
	///////////////////////////////////////////////
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }
	virtual void setShadowX(float shadowX) { _shadowX = shadowX; }
	virtual void setShadowY(float shadowY) { _shadowY = shadowY; }
	virtual void setImage(image * image) { _img = image; }
	//virtual void setRect(RECT rc) { _rc = rc; }

	//���� ���� �����൵ �ǳ�?
	virtual void setTimeMapMemoryAddressLink(randomMap * map) { _map = map; }
};

