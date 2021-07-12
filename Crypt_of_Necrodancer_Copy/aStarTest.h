#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILENUMX  (800/TILEWIDTH)
#define TILENUMY  (800/TILEHEIGHT)

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

	int _count;// 그냥렌더용
	bool _start; // 그냥 시작용


public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	void release();
	void update();
	void render();
	//타일 셋팅 함수
	void setTile();
	//갈 수 있는 길을 찾아 담아줄 함수
	vector<tile*> addOpenList(tile* currentTile);
	//길 찾는 함수
	void pathFinder(tile* currentTile);
	void endmove();
};

