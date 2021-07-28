#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "vision.h"
#include "randomMap.h"
#include "enemyManager.h"
#include "UIManager.h"
#include "bomb.h"

#define SHADOWMARGIN 30
#define BODYMARGIN 17
#define BASICVISION 5
#define EFFECTVOLUME 0.6f

class weapon;
class shovel;
class enemyManager;

class player : public gameNode
{
private:
	RECT _head; //��
	RECT _body; //����
	RECT _shadow; //�׸���
	float _x, _y; //�÷��̾� ���� �߽� ��ǥ

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

	image* _miss;	//�̽��̹��� ��Ͽ�
	bool _isMiss;	//�̽��߳�?
	float _missRange; //�̽��Ÿ�..
	float _missSpeed; //�̽��ӵ�

	bool _isThrow; //������??

	mapGenerator* _map;
	
	vision* _vision;

	float _elapsedSec; //������ ������ ���ؼ�
	bool _isMove;
	bool _isRush;
	bool _attack;
	PLAYER_ENEMY_DIRECTION _playerDirection;

	//zOrder��
	string _imgHeadName;
	string _imgBodyName;
	string _imgShadowName;

	//��ũ��
	weapon* _weapon;
	shovel* _shovel;

	bomb* _bomb;

	float _shopkeeperDistance;
	
	UIManager* _uiManager;

	int _alpha;
	bool _isAttacked;
	float _attackedElapsedTime;
	int _alphaCount;

	bool _isWall;
	bool _isTouchWall;

	float _shovelEffectElapsedTime;

	float _attackElapsedTime;

public:
	enemyManager* _em; //���ʹ� ���� ��������

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(int tileX, int tileY);
	virtual void render();

	void damaged();
	void miss();

	PLAYER_ENEMY_DIRECTION getDirection() { return _playerDirection; }
	void setDirection(PLAYER_ENEMY_DIRECTION dir) { _playerDirection = dir; }


	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
	void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setPlayerUIMemoryAddressLink(UIManager* ui) { _uiManager = ui; };
	void setupPlayerRect();

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }

	void setTileX(int x) { _tileX = x; }
	void setTileY(int y) { _tileY = y; }

	bool getIsMove() { return _isMove; }
	void setIsMove(bool b) { _isMove = b; }

	int getRenderX() { return _tileRenderX; }
	int getRenderY() { return _tileRenderY; }

	RECT getTileRect() { return _tileRect; }

	bomb* getBomb() { return _bomb; }

	//��Ÿ�� ����
	OBJECT getOBJ(int tileX, int tileY) { return _map->getTileObject(tileX, tileY); }

	//�����۸�ũ
	void setWeaponMemoryAddressLink(weapon* weapon) { _weapon = weapon; }
	void setShovelMemoryAddressLink(shovel* shovel) { _shovel = shovel; }

	//�ٵ� �̹��� ������ ������
	string getBodyImageName() { return _bodyImageName; }
	void setBodyImageName(string s) { _bodyImageName = s; }

	vision* getVision() { return _vision; }
	
	bool getAttack() { return _attack; }
	void setAttack(bool attack) { _attack = attack; }

	void renderShovelEffect(int tileX, int tileY);

	bool getIsThrow() { return _isThrow; }
	void setIsThrow(bool isThrow) { _isThrow = isThrow; }
};

