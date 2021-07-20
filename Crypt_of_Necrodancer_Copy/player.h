#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "vision.h"

enum PLAYER_DIRECTION
{
	PLAYER_DIRECTION_LEFT,
	PLAYER_DIRECTION_RIGHT,
	PLAYER_DIRECTION_UP,
	PLAYER_DIRECTION_DOWN
};

class player : public gameNode
{
private:
	RECT _head; //얼굴
	RECT _body; //몸통
	RECT _shadow; //그림자
	float _x, _y; //플레이어 몸통 중심 좌표
	float _headX, _headY;	//플레이어 머리 좌표
	float _shadowX1, _shadowY1;	//플레이어 그림자1 좌표
	float _shadowX2, _shadowY2;	//플레이어 그림자2 좌표
	int _tileX; //플레이어가 현재 있는 타일 x인덱스
	int _tileY; //플레이어가 현재 있는 타일 y인덱스
	RECT _tileRect; //현재 있는 타일 렉트
	string _headImageName; //머리 이미지 이름
	string _bodyImageName; //몸통 이미지 이름
	int _currentFrameX; //현재 프레임x
	int _currentFrameY; //현재 프레임y
	float _gravity;
	int alpha;

	mapGenerator* _map;
	vision* _vision;

	float _elapsedSec; //프레임 움직임 위해서
	bool _isPlayerMove;

	PLAYER_DIRECTION _playerDirection;

	//zOrder용
	string _imgHeadName;
	string _imgBodyName;
	string _imgShadowName;

public:
	virtual HRESULT init(int tileX, int tileY);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setupPlayerRect();
};

