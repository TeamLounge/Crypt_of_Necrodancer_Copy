#pragma once
#include "gameNode.h"
#include "mapGenerator.h"

class player : public gameNode
{
private:
	RECT _head; //얼굴
	RECT _body; //몸통
	RECT _shadow; //그림자
	int _tileX; //플레이어가 현재 있는 타일 x인덱스
	int _tileY; //플레이어가 현재 있는 타일 y인덱스

	mapGenerator* _map;
public:
	virtual HRESULT init(int tileX, int tileY);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setupPlayerRect();
};

