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
	RECT _tileRect; //현재 있는 타일 렉트
	string _headImageName; //머리 이미지 이름
	string _bodyImageName; //몸통 이미지 이름
	int _currentFrameX; //현재 프레임x
	int _currentFrameY; //현재 프레임y

	mapGenerator* _map;

	float _elapsedSec; //프레임 움직임 위해서

public:
	virtual HRESULT init(int tileX, int tileY);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setupPlayerRect();
};

