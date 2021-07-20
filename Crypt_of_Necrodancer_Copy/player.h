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
	int _tileX; //�÷��̾ ���� �ִ� Ÿ�� x�ε���
	int _tileY; //�÷��̾ ���� �ִ� Ÿ�� y�ε���
	RECT _tileRect; //���� �ִ� Ÿ�� ��Ʈ
	string _headImageName; //�Ӹ� �̹��� �̸�
	string _bodyImageName; //���� �̹��� �̸�
	int _currentFrameX; //���� ������x
	int _currentFrameY; //���� ������y
	float _gravity;

	//mapGenerator* _map;
	randomMap* _map;
	vision* _vision;

	float _elapsedSec; //������ ������ ���ؼ�
	bool _isPlayerMove;

	PLAYER_ENEMY_DIRECTION _playerDirection;

public:
	virtual HRESULT init(int tileX, int tileY);
	virtual void release();
	virtual void update();
	virtual void render();

	PLAYER_ENEMY_DIRECTION getDirection() { return _playerDirection; }

	//void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setLinkMap(randomMap* map) { _map = map; }
	void setupPlayerRect();

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
};

