#include "stdafx.h"
#include "shovel.h"
#include "shovelBasic.h"
#include "player.h"

shovel::shovel()
{
}

shovel::~shovel()
{
}

void shovel::InputHandle()
{
	shovelType* newType = _shovelType->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_shovelType);
		deleteCollision();
		_shovelType = newType;
		_shovelType->enter(this);
	}
}

void shovel::InputHandle(shovelType* ShovelType)
{
	_shovelType = ShovelType;

	shovelType* newType = _shovelType->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_shovelType);
		deleteCollision();
		_shovelType = newType;
		_shovelType->enter(this);
	}
}

HRESULT shovel::init()
{
	_shovel.imageName = "shovelTitanium";

	_shovelType = new shovelBasic();
	_shovelType->enter(this);

	ZeroMemory(&_collision, sizeof(SHOVELCOLLISION));

	UIMANAGER->addUI("shovel", _shovel.imageName.c_str(), _shovel.x, _shovel.y);

	return S_OK;
}

void shovel::release()
{
	_shovelType->exit(this);
}

void shovel::update()
{
	InputHandle();
	_shovelType->update(this);

	_shovel.rc = RectMake(_player->getTileRect().left, _player->getTileRect().top,
		TILESIZE, TILESIZE);

	_shovel.x = (_shovel.rc.left + _shovel.rc.right) / 2;
	_shovel.y = (_shovel.rc.top + _shovel.rc.bottom) / 2;
}

void shovel::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
		{
			Rectangle(getMemDC(), (*_viCollision).rc);
		}

		Rectangle(getMemDC(), _shovel.rc);
	}
}

void shovel::deleteCollision() 
{
	if (_vCollision.size() == 0) return;

	_vCollision.clear();
}
