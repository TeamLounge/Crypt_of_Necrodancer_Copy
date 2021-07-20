#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "vision.h"
#include "randomMap.h"



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
	int _tileRenderX;//렌더용 x인덱스
	int _tileRenderY;//렌더용 y인덱스
	RECT _tileRect; //현재 있는 타일 렉트
	string _headImageName; //머리 이미지 이름
	string _bodyImageName; //몸통 이미지 이름
	int _currentFrameX; //현재 프레임x
	int _currentFrameY; //현재 프레임y
	float _gravity;

	mapGenerator* _map;
	
	vision* _vision;

	float _elapsedSec; //프레임 움직임 위해서
	bool _isMove;

	PLAYER_ENEMY_DIRECTION _playerDirection;

	//zOrder용
	string _imgHeadName;
	string _imgBodyName;
	string _imgShadowName;

	int _alpha;

public:
	virtual HRESULT init(int tileX, int tileY);
	virtual void release();
	virtual void update();
	virtual void render();

	PLAYER_ENEMY_DIRECTION getDirection() { return _playerDirection; }
	void setDirection(PLAYER_ENEMY_DIRECTION dir) { _playerDirection = dir; }

	void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };

	void setupPlayerRect();

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }

	void setTileX(int x) { _tileX = x; }
	void setTileY(int y) { _tileY = y; }

	bool getIsMove() { return _isMove; }
	void setIsMove(bool b) { _isMove = b; }

	int getRenderX() { return _tileRenderX; }
	int getRenderY() { return _tileRenderY; }

};

