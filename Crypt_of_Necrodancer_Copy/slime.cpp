#include "stdafx.h"
#include "slime.h"

HRESULT slime::init()
{
	_direction = NONE;
	_isRight = true;

	return S_OK;
}

void slime::release()
{
}

void slime::update()
{
	//플레이어 위치 파악
	//따라가기 혹은 제자리 뛰기
}

void slime::render()
{
}

void slime::slimeMove()
{
}
