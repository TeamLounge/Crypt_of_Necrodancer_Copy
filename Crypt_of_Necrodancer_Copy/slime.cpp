#include "stdafx.h"
#include "slime.h"

HRESULT slime::init()
{
	_worldTime = TIMEMANAGER->getWorldTime();

	_rc = _map->getRect(_tileX, _tileY);
	_map->setTileObject(_x, _y, ENEMY);

	_direction = NONE;
	_isRight = true;
	_frameCount = 0;
	_frameIndex = 0;


	_gravity = 0;
	_jumpPower = 0;

	//�ʿ� �ѷ��ֱ�
	setArrangement();

	return S_OK;
}

void slime::release()
{
}

void slime::update()
{
	//�÷��̾� ��ġ �ľ�
	//���󰡱� Ȥ�� ���ڸ� �ٱ�
}

void slime::render()
{

}

void slime::setArrangement()
{
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
		_tileX = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tileY = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1)
			continue;
		break;		//// ��� ��Ƽ�� �������� ����ٸ� ���� ������

	}
}

void slime::slimeMove()
{
	_map->setTileObject(_tileX, _tileY, OBJ_NONE);
	_rc = _map->getRect(_tileX, _tileY);	//slime�� _x, _y ��ǥ�� Ÿ�� ������ �޾ƿ´�
	_map->setTileObject(_tileX, _tileY, ENEMY);
}
