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
	
	int _count;// 그냥렌더용
	int _damagecount;
	float time;
	bool _start; // 그냥 시작용
	bool ismove;
	bool hp;
	int _TotaltileX,_TotaltileY;

public:
	aStarTest();
	~aStarTest();

	HRESULT init(int enemyX, int enemyY, int playerX, int playerY);
	void release();
	void update(bool istime);
	void render();
	//타일 셋팅 함수
	void setTile(int enemyX, int enemyY, int playerX, int playerY);
	//갈 수 있는 길을 찾아 담아줄 함수
	vector<tile*> addOpenList(tile* currentTile);
	//길 찾는 함수
	void pathFinder(tile* currentTile);
	void endmove(int playerIndexX, int playerIndexY);
	void startmove();
	void setLinkrandomMap(mapGenerator* map) { _map = map; }

	int getenemyTileX() { return _startTile->getIdX(); }
	int getenemyTileY() { return _startTile->getIdY(); }
};

