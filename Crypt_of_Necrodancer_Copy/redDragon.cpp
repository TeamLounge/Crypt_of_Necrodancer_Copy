#include "stdafx.h"
#include "redDragon.h"

HRESULT redDragon::init(int playerIndexX, int playerIndexY)
{
	//_toRender = _damageRender = false;
	//_direction = LEFT;	//���� ���� �¾
	//_frameCount = 0;
	//_frameIndex = 0;

	//_isMove = false;		//�������ڸ��� ������
	//_isTime = false;

	//_gravity = 0;

	//_worldTime = TIMEMANAGER->getWorldTime();

	////�ʿ� �ѷ��ֱ�
	//setArrangement();	//Ÿ�Ͽ� ���� �Ѹ���

	//_img = IMAGEMANAGER->findImage("redDragon");	//�ڽ�
	//_rc = _map->getRect(_tileX, _tileY);
	//_map->setIsEnemy(_tileX, _tileY, true);
	//_x = _rc.left;
	//_y = _rc.top - (_rc.bottom - _rc.top) / 2;


	return S_OK;
}

void redDragon::update(int playerIndexX, int playerIndexY)
{
	setRedDragonFrame();
	moveRedDragon();
}

void redDragon::render()
{
	/*if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}

	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);*/
}

void redDragon::setArrangement()
{
	////���� ��ġ
	//while (true)
	//{
	//	//�����濡 ��ġ
	//	int random = RND->getInt(_map->getRoom().size());
	//	if (_map->getRoom()[random].roomState == ROOM_START ||
	//		_map->getRoom()[random].roomState == ROOM_SHOP)
	//		continue;	// �� ���� �÷��̾���̰ų� �����̸� ��Ƽ��

	//	//�����ϰ� ���� ����� ��ǥ �� ���� �־ ��Ƽ��
	//	_tileX = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
	//	_tileY = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
	//	if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1
	//		|| _map->getIsEnemy(_tileX, _tileY))		//���� tile�� 2����, room���� ��ġ�ϴϱ� ����!
	//		continue;
	//	break;		//// ��� ��Ƽ�� �������� ����ٸ� ���� ������
	//}
}

void redDragon::setRedDragonFrame()
{
	//if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	//{
	//	_worldTime = TIMEMANAGER->getWorldTime();
	//}

	//_frameCount++;
	//if (_frameCount % 8 == 0)
	//{
	//	_frameCount = 0;
	//	if (_currentFrameX >= IMAGEMANAGER->findImage("redDragon")->getMaxFrameX())
	//	{
	//		_currentFrameX = 0;
	//	}
	//	else
	//	{
	//		_currentFrameX++;
	//	}
	//	//���� �ٲ� �����ֱ�
	//	if (_direction == LEFT)
	//	{
	//		_currentFrameY = 0;
	//	}
	//	else if (_direction == RIGHT)
	//	{
	//		_currentFrameY = 1;
	//	}
	//}
}

void redDragon::moveRedDragon()
{
}
