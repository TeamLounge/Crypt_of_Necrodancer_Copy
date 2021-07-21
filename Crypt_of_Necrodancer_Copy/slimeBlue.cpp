#include "stdafx.h"
#include "slimeBlue.h"

HRESULT slimeBlue::init()
{
	slime::init();	//»ó¼Ó

	_img = IMAGEMANAGER->findImage("slimeBlue");

	return S_OK;
}

void slimeBlue::update()
{
}

void slimeBlue::release()
{
}

void slimeBlue::render()
{
}
