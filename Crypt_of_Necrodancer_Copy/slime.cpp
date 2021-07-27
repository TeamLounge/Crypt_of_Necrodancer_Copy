#include "stdafx.h"
#include "slime.h"

HRESULT slime::init(int playerIndexX, int playerIndexY)
{

	_toRender = _damageRender = false;
	//_direction = NONE;
	_frameCount = 0;
	_frameIndex = 0;

	_isMove = false;		//�������ڸ��� ������
	_isTime = false;

	_gravity = 0;
	_beatSpeed = 1.0f;

	_worldTime = TIMEMANAGER->getWorldTime();


	//�ʿ� �ѷ��ֱ�
	/////////////////////////////////////////////////////////////////// ���� �� ��ƶ� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	setArrangement();	//Ÿ�Ͽ� ���� �Ѹ���

	_rc = _map->getRect(_tileX, _tileY);		//�ڸ� ��� ���� �����������
	_map->setIsEnemy(_tileX, _tileY, true);		//_map->setTileObject(_tileX, _tileY, ENEMY);  ���� ��
	_x = _rc.left;								//_x, _y�� �̹����� �����̱� ���� _rc�� ���� ������ ���� ��ǥ(���� �������� ����)
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;



	return S_OK;
}

void slime::release()
{
}

void slime::update(int playerIndexX, int playerIndexY)
{
	_playerIndexX = playerIndexX;
	_playerIndexY = playerIndexY;
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
		if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1 
			|| _map->getIsEnemy(_tileX, _tileY))		//���� tile�� 2����, room���� ��ġ�ϴϱ� ����!
			continue;
		break;		//// ��� ��Ƽ�� �������� ����ٸ� ���� ������
	}
}
