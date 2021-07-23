#include "stdafx.h"
#include "slime.h"

HRESULT slime::init()
{

	_toRender = _damageRender = false;
	_direction = NONE;
	_frameCount = 0;
	_frameIndex = 0;

	_isMove = false;		//�������ڸ��� ������
	_isTime = false;

	_isMoveUp = false;		//��, �Ʒ�
	_isMoveRight = false;	//��, ��

	_gravity = 0;
	_jumpPower = 0;

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

void slime::update()
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= 1.0f)
	{
		_movingTime = TIMEMANAGER->getWorldTime();
		if (_isTime)
		{
			_isTime = false;
		}
		else
		{
			_isTime = true;
		}

	}
	if (TIMEMANAGER->getWorldTime() - _renderTime >= 0.5f)
	{
		_renderTime = TIMEMANAGER->getWorldTime();
		if (_toRender)
		{
			_toRender = false;
		}
		else
		{
			_toRender = true;
		}
	}
	
	if (_map->getTileObject(_tileX, _tileY) == TR_LEFT)
	{
		_direction = LEFT;
		_map->setIsEnemy(_tileX, _tileY, false);
		_tileX -= 1;
		_rc = _map->getRect(_tileX, _tileY);
		_map->setIsEnemy(_tileX, _tileY, true);
		_isMove = true;
	}
	else if (_map->getTileObject(_tileX, _tileY) == TR_RIGHT)
	{
		_direction = RIGHT;
		_map->setIsEnemy(_tileX, _tileY, false);
		_tileX += 1;
		_rc = _map->getRect(_tileX, _tileY);
		_map->setIsEnemy(_tileX, _tileY, true);
		_isMove = true;
	}
	else if (_map->getTileObject(_tileX, _tileY) == TR_UP)
	{
		_direction = UP;
		_map->setIsEnemy(_tileX, _tileY, false);
		_tileY -= 1;
		_rc = _map->getRect(_tileX, _tileY);
		_map->setIsEnemy(_tileX, _tileY, true);
		_isMove = true;
	}
	else if (_map->getTileObject(_tileX, _tileY) == TR_DOWN)
	{
		_direction = DOWN;
		_map->setIsEnemy(_tileX, _tileY, false);
		_tileY += 1;
		_rc = _map->getRect(_tileX, _tileY);
		_map->setIsEnemy(_tileX, _tileY, true);
		_isMove = true;
	}
	/*else if (_astar->getStart())
	{
		skeletonMove(isTime);
	}*/
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
