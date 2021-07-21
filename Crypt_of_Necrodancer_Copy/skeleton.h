#pragma once
#include "gameNode.h"
#include "aStarTest.h"
#include "mapGenerator.h"


class skeleton : public gameNode
{
protected:

	mapGenerator* _map;
	aStarTest* _astar;
	PLAYER_ENEMY_DIRECTION _direction;

	image* _img;
	RECT _rc;
	
	int _x, _y;
	int _shadowX, _shadowY;
	int _count, _index , _indey;
	int _hp;

	float _movingTime , _renderTime;

	bool isFind;
	bool isTime;
	bool toRender;
public:
	virtual HRESULT init(int playerIndexX, int playerIndexY);
	virtual void update(int playerIndexX, int playerIndexY);
	virtual void release();
	virtual void render();

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
	virtual void setTileMapLinK(mapGenerator* tileMap) { _map = tileMap; }
};