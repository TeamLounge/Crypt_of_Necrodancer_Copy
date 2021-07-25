#include "stdafx.h"
#include "apple.h"
#include "cheese.h"
#include "food.h"
#include "player.h"

food::food()
{
}

food::~food()
{
}

void food::InputHandle()
{
	foodType* newType = _foodType->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_foodType);
		_foodType = newType;
		_foodType->enter(this);
	}
}

HRESULT food::init()
{
	_food.imageName = "cheese";

	_foodType = new apple();
	_foodType->enter(this);

	_playerBeforeX = 0;
	_playerBeforeY = 0;

	UIMANAGER->addUI("food", _food.imageName.c_str(), _food.x, _food.y);

	return S_OK;
}

void food::release()
{
	_foodType->exit(this);
}

void food::update()
{
	InputHandle();
	_foodType->update(this);

	if (_player->getTileX() != _playerBeforeX || _player->getTileY() != _playerBeforeY)
	{
		_playerBeforeX = _player->getTileX();
		_playerBeforeY = _player->getTileY();
	}

	_food.rc = RectMake(_player->getTileRect().left, _player->getTileRect().top,
		TILESIZE, TILESIZE);

	_food.x = (_food.rc.left + _food.rc.right) / 2;
	_food.y = (_food.rc.top + _food.rc.bottom) / 2;
}

void food::render()
{
}
