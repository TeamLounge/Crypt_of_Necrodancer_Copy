#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

class mapGenerator;

class aStarTest : public gameNode
{
private:
	//전체 타일 담을 벡터
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;
	//갈 수 있는 타일 담을 벡터
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;
	//가장 가까운 경로를 담을 벡터
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile; //시작타일 
	tile* _endTile; //끝타일
	tile* _currentTile; //현재 타일

	mapGenerator* _map;
	PLAYER_ENEMY_DIRECTION _dir;

	int _count;// 그냥렌더용
	int _damagecount;
	float time;
	bool _start; // 그냥 시작용
	bool ismove;
	bool damage;
	bool isMiniboss;
	int _TotaltileX,_TotaltileY;

public:
	aStarTest();
	~aStarTest();

	HRESULT init(int enemyX, int enemyY, int playerX, int playerY ,bool miniboss = false);
	void release();
	void update();
	void render();
	//타일 셋팅 함수
	void setTile(int enemyX, int enemyY, int playerX, int playerY);
	//갈 수 있는 길을 찾아 담아줄 함수
	vector<tile*> addOpenList(tile* currentTile);
	//길 찾는 함수
	void pathFinder(tile* currentTile);
	void endmove(int playerIndexX, int playerIndexY);
	void start();
	void move(int X ,int Y);
	void actionMove(int X, int Y);
	void callPathFinder(int x, int y);
	void enemyAttack();

	void setLinkrandomMap(mapGenerator* map) { _map = map; }

	//겟터
	int getEnemyTileX() { return _startTile->getIdX(); }
	int getEnemyTileY() { return _startTile->getIdY(); }
	bool getDamage() { return damage; }
	bool getStart() { return _start; }
	PLAYER_ENEMY_DIRECTION getDirection() { return _dir; };
	int getCloseListsize() { return _vCloseList.size(); }
	int getClosebackX() { return _vCloseList.back()->getIdX(); }
	int getClosebackY() { return _vCloseList.back()->getIdY(); }


	//셋터
	void setDamage(bool _damage) { damage = _damage; }
	void clear() { _vCloseList.clear(); _vOpenList.clear(); }
};

