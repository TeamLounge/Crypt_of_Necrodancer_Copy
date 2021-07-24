#include "stdafx.h"
#include "weapon.h"
#include "dagger.h"
#include "player.h"
#include "UIManager.h"

weapon::weapon()
{
}

weapon::~weapon()
{
}

void weapon::InputHandle()
{
	weaponType* newType = _weaponType->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_weaponType);
		deleteCollision();
		_weaponType = newType;
		_weaponType->enter(this);
	}
}

void weapon::InputHandle(weaponType* WeaponType)
{
	_weaponType = WeaponType;

	weaponType* newType = _weaponType->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_weaponType);
		deleteCollision();
		_weaponType = newType;
		_weaponType->enter(this);
	}
}

HRESULT weapon::init()
{
	_weapon.imageName = "broadSword";

	_weaponType = new dagger();
	_weaponType->enter(this);

	ZeroMemory(&_collision, sizeof(COLLISION));

	UIMANAGER->addUI("weapon", _weapon.imageName.c_str(), _weapon.x, _weapon.y);

	return S_OK;
}

void weapon::release()
{
	_weaponType->exit(this);
}

void weapon::update()
{
	InputHandle();
	_weaponType->update(this);

	_weapon.rc = RectMake(_player->getTileRect().left, _player->getTileRect().top,
		TILESIZE, TILESIZE);

	_weapon.x = (_weapon.rc.left + _weapon.rc.right) / 2;
	_weapon.y = (_weapon.rc.top + _weapon.rc.bottom) / 2;
}

void weapon::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
		{
			Rectangle(getMemDC(), (*_viCollision).rc);
		}
	
		Rectangle(getMemDC(), _weapon.rc);
	}
}

void weapon::deleteCollision()
{
	if (_vCollision.size() == 0) return;

	_vCollision.clear();
}
