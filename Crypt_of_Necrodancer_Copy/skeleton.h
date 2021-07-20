#pragma once
#include "gameNode.h"
#include "aStarTest.h"
#include "randomMap.h"


class skeleton : public gameNode
{
protected:
	enum DIRECTRION
	{
		NONE,
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

	randomMap* _map;
	aStarTest* _astar;
	DIRECTRION _direction;

	image* _img;
	RECT _rc;
	
	int _x, _y;
	int _shadowX, _shadowY;
	int _conut, _index;
	int _hp;

	bool isRight;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void aStar();

	virtual void skeletonMove();

	virtual image* getImage() { return _img; }
	virtual int getX() { return _x; }
	virtual int getY() { return _y; }
	virtual RECT getRect() { return _rc; }
	virtual int getShadowX() { return _shadowX; }
	virtual int getShadowY() { return _shadowY; }
	
	virtual void setImage(image* image) { _img = image; }
	virtual void setX(int x) { _x = x; }
	virtual void setY(int y) { _y = y; }
	virtual void setShadowX(int x) { _shadowX = x; }
	virtual void setShadowY(int y) { _shadowY = y; }
	virtual void setTileMapLinK(randomMap* tileMap) { _map = tileMap; }
};