#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "player.h"
#include "enemyManager.h"
#include "bomb.h"

class UIManager;
class weapon;
class shovel;

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

	int _playerBeforeX, _playerBeforeY;

	bomb* _bomb;
	UIManager* _UIM;
	weapon* _weapon;
	shovel* _shovel;

	string bodyName;
	string torchName;
	string foodName;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(int tileX, int tileY);

	void setObjectMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setObjectPlayerMemoryAddressLink(player* player) { _player = player; };
	void setObjectEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; };

	//���̳� ���� �� ������Ʈ�� �浹
	void playerObjectCollison();
	void enemyObjectCollison();

	//�ʿ� �ִ� �����۰� �浹
	void playerItemCollision();


	//���� ���� �÷��̾� �����̰� �ϱ�
					//x������ ���� ��, y������ ���Ұ�, �ٲ� ����
	void playerMove(int addTileX, int addTileY, PLAYER_ENEMY_DIRECTION dir);

	void changeMusicSpeed(float speed);

	bomb* getBomb() { return _bomb; }

	string getBodyName() { return bodyName; }
	string getTorchName() { return torchName; }
	string getFoodName() { return foodName; }

	void setUIMMemoryAddressLink(UIManager* UIM) { _UIM = UIM; }
	void setWeaponMemoryAddressLink(weapon* weapon) { _weapon = weapon; }
	void setShovelMemoryAddressLink(shovel* shovel) { _shovel = shovel; }
};

