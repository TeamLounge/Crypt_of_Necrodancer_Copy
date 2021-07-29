#pragma once
#include "gameNode.h"
#include "weaponType.h"
#include <vector>

class player;
class UIManager;
class objectManager;
class mapGenerator;
class enemyManager;

struct WEAPON
{
	image* img;
	string imageName;
	RECT rc;
	bool isThrow; // ���� �� �ִ��� Ȯ���ϴ� ��ġ
	float x, y;
};

struct COLLISION
{
	RECT rc;
	int  tileX, tileY;		// Ÿ����ǥ�� ��ġ �ʿ�
};

struct WEAPONEFFECT
{
	image* img;
	string imageName;
	RECT rc;
	float x, y;
	int currentFrameX, currentFrameY;
};

class weapon : public gameNode
{
private:


public:
	weaponType* _weaponType;
	WEAPON _weapon;
	COLLISION _collision;
	WEAPONEFFECT _weaponEffect;
	vector<COLLISION>			_vCollision;
	vector<COLLISION>::iterator _viCollision;

	vector<WEAPONEFFECT>			_vWeaponEffect;
	vector<WEAPONEFFECT>::iterator _viWeaponEffect;

	player* _player;
	UIManager* _UIM;
	objectManager* _om;
	mapGenerator* _map;
	enemyManager* _em;

	int _playerBeforeX;
	int	_playerBeforeY;

	int _throwTileX;
	int _throwTileY;

	bool _isThrowRender; // ������ ������ ���� ���ϰ� �ϱ� ���� ��ġ
	bool _isEffectOn; //����Ʈ ������?
	bool _effectDirection; //������ ������?

	weapon();
	~weapon();

	void InputHandle();
	void InputHandle(weaponType* WeaponType);
	virtual HRESULT init();
	virtual	void release();
	virtual	void update();
	virtual	void render();
	void deleteCollision();
	void deleteWeaponEffect();

	weaponType* getWeaponType() { return _weaponType; }
	string getWeaponName() { return _weapon.imageName; }
	image* getWeaponImage() { return _weapon.img; }
	bool getIsThrowRender() { return _isThrowRender; }

	void setWeaponName(string weaponName) { _weapon.imageName = weaponName; }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setUIMMemortAddressLink(UIManager* UIM) { _UIM = UIM; }
	void setOMMemoryAddressLink(objectManager* om) { _om = om; }
	void setMGMemoryAddressLink(mapGenerator* map) { _map = map; }
	void setEMMemoryAddressLink(enemyManager* em) { _em = em; }

	vector<COLLISION> getVCollision() { return _vCollision; }
	vector<COLLISION>::iterator getVICollision() { return _viCollision; }
};

