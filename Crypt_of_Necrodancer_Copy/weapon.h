#pragma once
#include "gameNode.h"
#include "weaponType.h"
#include <vector>

class player;
class UIManager;

struct WEAPON
{
	image* img;
	string imageName;
	RECT rc;
	float x, y;
};

struct COLLISION
{
	RECT rc;
	float x, y;		// 타일좌표와 일치 필요
};

class weapon : public gameNode
{
private:


public:
	weaponType* _weaponType;
	WEAPON _weapon;
	COLLISION _collision;
	vector<COLLISION>			_vCollision;
	vector<COLLISION>::iterator _viCollision;

	player* _player;
	UIManager* _UIM;

	weapon();
	~weapon();

	void InputHandle();
	void InputHandle(weaponType* WeaponType);
	virtual HRESULT init();
	virtual	void release();
	virtual	void update();
	virtual	void render();
	void deleteCollision();

	weaponType* getWeaponType() { return _weaponType; }
	string getWeaponName() { return _weapon.imageName; }
	image* getWeaponImage() { return _weapon.img; }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setUIMMemortAddressLink(UIManager* UIM) { _UIM = UIM; }
};

