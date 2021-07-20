#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "vision.h"
#include "randomMap.h"



class player : public gameNode
{
private:
	RECT _head; //��
	RECT _body; //����
	RECT _shadow; //�׸���
	float _x, _y; //�÷��̾� ���� �߽� ��ǥ
	float _headX, _headY;	//�÷��̾� �Ӹ� ��ǥ
	float _shadowX1, _shadowY1;	//�÷��̾� �׸���1 ��ǥ
	float _shadowX2, _shadowY2;	//�÷��̾� �׸���2 ��ǥ
	int _tileX; //�÷��̾ ���� �ִ� Ÿ�� x�ε���
	int _tileY; //�÷��̾ ���� �ִ� Ÿ�� y�ε���
	int _tileRenderX;//������ x�ε���
	int _tileRenderY;//������ y�ε���
	RECT _tileRect; //���� �ִ� Ÿ�� ��Ʈ
	string _headImageName; //�Ӹ� �̹��� �̸�
	string _bodyImageName; //���� �̹��� �̸�
	int _currentFrameX; //���� ������x
	int _currentFrameY; //���� ������y
	float _gravity;

	mapGenerator* _map;
	
	vision* _vision;

	float _elapsedSec; //������ ������ ���ؼ�
	bool _isMove;

	PLAYER_ENEMY_DIRECTION _playerDirection;

	//zOrder��
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

