#include "stdafx.h"
#include "slimeGreen.h"

HRESULT slimeGreen::init()
{
	slime::init();	//���

	_img = IMAGEMANAGER->findImage("slimeGreen");	//protected!!

	//���� ��ġ
	while (true)
	{

		//�����濡 ��ġ
		int random = RND->getInt(_map->getRoom().size());
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;	// �� ���� �÷��̾���̰ų� �����̸� ��Ƽ��

		//_map->getTileObject	//object�� �� �޾ƿ���
		//_map->getTileTerrain	//terrain�� �� �޾ƿ���
		//_map->getRect			//Ÿ�� rect �޾ƿ���
		//��� �پ��� ���� �޾ƿ� �� ������ �� ����!!!!


		//�����ϰ� ���� ����� ��ǥ �� ���� �־ ��Ƽ��
		_x = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_y = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_x, _y) != OBJ_NONE || _map->getTileTerrain(_x, _y) != DIRT1)
			continue;
		break;		//// ��� ��Ƽ�� �������� ����ٸ� ���� ������

	}

	_rc = _map->getRect(_x, _y);


	return S_OK;
}

void slimeGreen::update()
{
	slimeMove();
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

	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom - _rc.top) / 2, 0, 0);
}
