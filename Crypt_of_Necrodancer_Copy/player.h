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
	RECT _head; //��
	RECT _body; //����
	RECT _shadow; //�׸���
	float _x, _y; //�÷��̾� ���� �߽� ��ǥ
	float _headX, _headY;	//�÷��̾� �Ӹ� ��ǥ
	float _shadowX1, _shadowY1;	//�÷��̾� �׸���1 ��ǥ
	float _shadowX2, _shadowY2;	//�÷��̾� �׸���2 ��ǥ
	int _tileX; //�÷��̾ ���� �ִ� Ÿ�� x�ε���
	int _tileY; //�÷��̾ ���� �ִ� Ÿ�� y�ε���
	RECT _tileRect; //���� �ִ� Ÿ�� ��Ʈ
	string _headImageName; //�Ӹ� �̹��� �̸�
	string _bodyImageName; //���� �̹��� �̸�
	int _currentFrameX; //���� ������x
	int _currentFrameY; //���� ������y
	float _gravity;
	int alpha;

	mapGenerator* _map;
	vision* _vision;

	float _elapsedSec; //������ ������ ���ؼ�
	bool _isPlayerMove;

	PLAYER_DIRECTION _playerDirection;

	//zOrder��
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

