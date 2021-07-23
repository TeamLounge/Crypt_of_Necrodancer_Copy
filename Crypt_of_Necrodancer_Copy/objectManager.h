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

	vector<tagPushedObject> _playerPushedObject; //눌린 오브젝트 복구용

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

	//방향 함정 플레이어 움직이게 하기
					//x축으로 더할 값, y축으로 더할값, 바뀔 방향
	void playerMove(int addTileX, int addTileY, PLAYER_ENEMY_DIRECTION dir);

	void changeMusicSpeed(float speed);

	bomb* getBomb() { return _bomb; }
};

