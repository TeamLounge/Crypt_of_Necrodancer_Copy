#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "player.h"
#include "enemyManager.h"
#include "bomb.h"

struct tagPushedObject
{
	int tileX;
	int tileY;
};
class objectManager : public gameNode
{
	mapGenerator* _map;
	player* _player;
	enemyManager* _em;

	vector<tagPushedObject> _playerPushedObject; //���� ������Ʈ ������

	bool _isMusicSpeedChanged;
	float _elapsedSec;

	tagPushedObject _music;

	bomb* _bomb;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(int tileX, int tileY);

	void setObjectMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setObjectPlayerMemoryAddressLink(player* player) { _player = player; };
	void setObjectEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; };

	void playerObjectCollison();
	void enemyObjectCollison();

	//���� ���� �÷��̾� �����̰� �ϱ�
					//x������ ���� ��, y������ ���Ұ�, �ٲ� ����
	void playerMove(int addTileX, int addTileY, PLAYER_ENEMY_DIRECTION dir);

	void changeMusicSpeed(float speed);

	bomb* getBomb() { return _bomb; }
};

