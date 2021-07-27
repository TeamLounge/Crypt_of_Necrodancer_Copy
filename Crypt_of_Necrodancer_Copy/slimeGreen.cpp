#include "stdafx.h"
#include "slimeGreen.h"

HRESULT slimeGreen::init()
{
	slime::init();	//���

	_img = IMAGEMANAGER->findImage("slimeGreen");	//protected!!
	_map->setIsEnemy(_tileX, _tileY, true);	//���ʹ� Ÿ�� �Ӽ� ON		//���ʹ̳��� �� ��ġ��		//������ Ÿ���� �����ϱ� �̷��� �ʱ�ȭ�� ���ְ� ���Ƶ� ��.
	_indexSwitch = false;
	_hp = 1;
	return S_OK;
}

void slimeGreen::update()
{
	setSlimeFrame();
	moveSlimeGreen();	//�׸������Ӹ��� ������


}

void slimeGreen::release()
{
}

void slimeGreen::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	if (_map->getAlpha(_tileX, _tileY) <= 255 && _map->getAlpha(_tileX, _tileY) > 150) {
		_img = IMAGEMANAGER->findImage("slimeGreen");
		_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	}
	else if (_map->getAlpha(_tileX, _tileY) <= 150 && _map->getAlpha(_tileX, _tileY) > 0)
	{
		_img = IMAGEMANAGER->findImage("slimeGreen_dark");
		_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	}
}

void slimeGreen::setSlimeFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > _beatSpeed / 2)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	_frameCount++;
	if (_frameCount % 8 == 0)
	{
		_frameCount = 0;
		if (_currentFrameX >= IMAGEMANAGER->findImage("slimeGreen")->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else
		{
			_currentFrameX++;
		}
	}
}

void slimeGreen::moveSlimeGreen()
{
	

	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatSpeed / 2)
	{
		_movingTime = TIMEMANAGER->getWorldTime();
		if (_isTime)
		{
			_isTime = false;
			_isMove = true;
		}
		else
		{
			_isTime = true;
			_isMove = true;
		}
	}

	//����
	if (_isMove)
	{
		
		_gravity += 0.965f;
		_y += -sinf(7 * PI / 9) * 9 + _gravity;

		if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
		{
			_y = _rc.top - (_rc.bottom - _rc.top) / 2;
			_isMove = false;
			_gravity = 0;
		}
	}
}
