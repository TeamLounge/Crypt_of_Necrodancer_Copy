#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
//#include "aStarTest.h"

//aStar 필요없다

class slime : public gameNode
{
protected:
	mapGenerator * _map;
	PLAYER_ENEMY_DIRECTION _direction;

	image * _img;
	RECT _rc;

	float _x, _y;	//중점 좌표로
	float _shadowX, _shadowY;
	int _hp;

	int _count;
	int _index;
	int _currentFrameX, _currentFrameY;
	float _elapsedSec; //프레임 움직임 위함

	float _gravity;
	float _jumpPower;


	bool _isRight;	//기본 방향 우측이야?

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void slimeMove();

	void setImage();		//slime들 이미지 set

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
	virtual void setTileMapLink(mapGenerator* tileMap) { _map = tileMap; }
	//virtual void setRect(RECT rc) { _rc = rc; }
};

