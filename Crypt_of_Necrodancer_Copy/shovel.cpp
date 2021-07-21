#include "stdafx.h"
#include "shovel.h"
#include "shovelBasic.h"

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
	return S_OK;
}

void shovel::release()
{
}

void shovel::update()
{
}

void shovel::render()
{
}

void shovel::deleteCollision()
{
}
