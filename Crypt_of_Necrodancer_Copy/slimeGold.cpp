#include "stdafx.h"
#include "slimeGold.h"

HRESULT slimeGold::init()
{
	slime::init();	//���

	_img = IMAGEMANAGER->findImage("slimeGold");

	return S_OK;
}

void slimeGold::update()
{
}

void slimeGold::release()
{
}

void slimeGold::render()
{
}
