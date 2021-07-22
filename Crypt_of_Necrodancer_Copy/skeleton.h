#pragma once
#include "gameNode.h"
#include "aStarTest.h"
#include "mapGenerator.h"


class skeleton : public gameNode
{
protected:

	mapGenerator* _map;
	aStarTest* _astar;
	PLAYER_ENEMY_DIRECTION _dir;

	image* _img;
	RECT _rc;
	
	float _x, _y;
	float _gravity;
	int _tilex, _tiley;
	int _shadowX, _shadowY;
	int _count, _damageRenderCount,_damageindex, _index , _indey;
	int _hp;

	float _movingTime , _renderTime;

	bool isFind;
	bool isTime , isMove;
	bool toRender, damageRender;
public:
	virtual HRESULT init(int playerIndexX, int playerIndexY);
	virtual void update(int playerIndexX, int playerIndexY);
	virtual void release();
	virtual void render();

	virtual void skeletonMove(bool Time);
	virtual void skeletonTrap();

	virtual image* getImage() { return _img; }
	virtual int getX() { return _tilex; }
	virtual int getY() { return _tiley; }
	virtual RECT getRect() { return _rc; }
	virtual int getShadowX() { return _shadowX; }
	virtual int getShadowY() { return _shadowY; }
	


	virtual void setImage(image* image) { _img = image; }
	virtual void setX(int x) { _tilex = x; }
	virtual void setY(int y) { _tiley = y; }
	virtual void setShadowX(int x) { _shadowX = x; }
	virtual void setShadowY(int y) { _shadowY = y; }
	virtual void setTileMapLinK(mapGenerator* tileMap) { _map = tileMap; }
};