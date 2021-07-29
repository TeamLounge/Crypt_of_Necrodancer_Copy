#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "aStarTest.h"
struct FIRE
{
	RECT rc;
	image * img;	//불 담을 이미지
	
	int tileX, tileY;
	bool isAttack;	//충돌 판정용
};
class minotaurAndDragon : public gameNode
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
	int _count, _damageRenderCount, _damageindex, _index, _indey;
	int _fireRenderCount, _fireIndex;		//드래곤
	int _hp;

	int _playerindex, _playerindey;


	float _movingTime, _renderTime;
	float _beatspeed;
	bool isFind;
	bool isTime, isMove;
	bool attack;
	bool isRun, toRender, damageRender;		//미노

	bool isFire, fireRender;	//드래곤
public:
	virtual HRESULT init(int playerIndexX, int playerIndexY);
	virtual void update(int playerIndexX, int playerIndexY);
	virtual void release();
	virtual void render();

	virtual void minotaurAndDragonMove(bool Time);
	virtual void minotaurActionMove(bool Time);
	virtual void redDragonActionMove();
	virtual void moveMotion();
	virtual image* getImage() { return _img; }
	virtual int getX() { return _tilex; }
	virtual int getY() { return _tiley; }
	virtual RECT getRect() { return _rc; }
	virtual int getShadowX() { return _shadowX; }
	virtual int getShadowY() { return _shadowY; }
	virtual int getHp() { return _hp; }
	virtual float getBeatSpeed() { return _beatspeed; }
	virtual bool getAttck() { return attack; }
	virtual bool getIsFire() { return isFire; }

	virtual void setImage(image* image) { _img = image; }
	virtual void setX(int x) { _tilex = x; }
	virtual void setY(int y) { _tiley = y; }
	virtual void setShadowX(int x) { _shadowX = x; }
	virtual void setShadowY(int y) { _shadowY = y; }
	virtual void setTileMapLinK(mapGenerator* tileMap) { _map = tileMap; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void setBeatSpeed(float speed) { _beatspeed = speed; }
	virtual void setAttck(bool b) { attack = b; }

	vector<FIRE>			_vFire;
	vector<FIRE>::iterator	_viFire;

};

