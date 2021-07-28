#pragma once
#include "gameNode.h"
#include "aStarTest.h"
#include "mapGenerator.h"

class deathMetal : public gameNode
{

protected:
	mapGenerator* _map;
	aStarTest* _astar;
	PLAYER_ENEMY_DIRECTION _dir, _judgmentdir;

	image* _img;
	RECT _rc;

	float _x, _y;
	float _gravity;
	int _tilex, _tiley;
	int _responeCount, _count, _damageRenderCount, _damageindex, _index, _indey;
	int actionCount;
	int _hp, _phase;

	int _playerindex, _playerindey;


	float _movingTime, _renderTime;
	float _beatSpeed, _beat;

	bool isFind;
	bool isTime, isMove;
	bool isAction, damageRender, toRender;
	bool attack, isdamaged;

public:
	virtual HRESULT init(int playerIndexX, int playerIndexY);
	virtual void update(int playerIndexX, int playerIndexY);
	virtual void release();
	virtual void render();

	virtual void phaseOneMove(bool Time);
	virtual void phaseTwoThreeMove(bool Time);
	virtual void phaseFourMove(bool Time);
	virtual void TrapMove();
	virtual void fire();

	virtual image* getImage() { return _img; }
	virtual int getX() { return _tilex; }
	virtual int getY() { return _tiley; }
	virtual RECT getRect() { return _rc; }
	virtual int getHp() { return _hp; }
	virtual int getResponeCount() { return _responeCount; }
	virtual int getPhase() { return _phase; }
	virtual bool getAttck() { return attack; }
	virtual PLAYER_ENEMY_DIRECTION getJudgMundetDirection() { return _judgmentdir; }
	virtual bool getIsAction() { return isAction; }
	virtual float getBeatSpeed() { return _beatSpeed; }

	virtual void setImage(image* image) { _img = image; }
	virtual void setX(int x) { _tilex = x; }
	virtual void setY(int y) { _tiley = y; }
	virtual void setTileMapLinK(mapGenerator* tileMap) { _map = tileMap; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void setResponeCount(int count) { _responeCount = count; }
	virtual void setAttck(bool b) { attack = b; }
	virtual void setIsDamaged(bool b) { isdamaged = b; }
	virtual void setIsAction(bool b) { isAction = b; }
	virtual void setBeatSpeed(float beatspeed) { _beatSpeed = beatspeed; }

};
