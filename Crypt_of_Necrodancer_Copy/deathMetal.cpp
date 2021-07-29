#include "stdafx.h"
#include "deathMetal.h"

HRESULT deathMetal::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = isMove = false;
	attack = isdamaged = false;
	_responeCount = _count =  _damageRenderCount = _damageindex = _index = _indey = _phase = 0;
	toRender = damageRender = false;
	actionCount = _fireindex = _fireRenderCount =0;
	_beatSpeed = 1.0f;
	_beat = (_beatSpeed * (3.0f / 2.0f));
	_img = IMAGEMANAGER->findImage("deathMetal");
	_tilex = 6;
	_tiley = 10;
	_rc = _map->getRect(_tilex, _tiley);		//_tileX, _tileY는 움직임을 위한 첫번째 타일맵의 좌표
	_map->setIsEnemy(_tilex, _tiley, true);
	_x = _rc.right -_img->getFrameWidth()/2;								//_x, _y는 이미지를 움직이기 위한 _rc를 토대로 가져온 실제 좌표(정보 가져오기 위함)
	_y = _rc.bottom - _img->getFrameHeight();
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY);
	_playerindex = playerIndexX;
	_playerindey = playerIndexY;
	_hp = 9;
	_heart1 = _heart2 = _heart3 = _heart4 = _heart5 = _heart6 = _heart7 = _heart8 = _heart9 = IMAGEMANAGER->findImage("Enemy_heart");
	_vCollision.clear();

	return S_OK;
}

void deathMetal::update(int playerIndexX, int playerIndexY)
{
	_playerindex = playerIndexX;
	_playerindey = playerIndexY;
	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beat)
	{
		_movingTime = TIMEMANAGER->getWorldTime();
		if (isTime)
		{
			isTime = false;
		}
		else
		{
			isTime = true;
		}
	}
	if (!isFind) {
		for (int y = _tiley - 4; y <= _tiley + 4; y++)
		{
			for (int x = _tilex - 4; x <= _tilex + 4; x++)
			{
				if (x == playerIndexX && y == playerIndexY)
				{
					isFind = true;
				}
			}
		}
	}
	else
	{
		if (_hp >= 7) {
			_astar->endmove(playerIndexX, playerIndexY);
			_astar->update();

			TrapMove();
			if (!isMove&&_astar->getStart())
			{
				phaseOneMove(isTime);
			}
			if (_astar->getDamage())
			{
				damageRender = true;
				if (!attack) attack = true;
				_astar->setDamage(false);
			}
		}
		else if (_hp < 7 && _hp >= 3)
		{
			_beat = _beatSpeed;
			_astar->endmove(playerIndexX, playerIndexY);
			_astar->clear();

			TrapMove();
			phaseTwoThreeMove(isTime);
		}
		else if (_hp <= 2 && _hp > 0)
		{
			_astar->endmove(playerIndexX, playerIndexY);
			_astar->update();
			TrapMove();
			if (!isMove && _astar->getStart())
			{
				phaseFourMove(isTime);
			}
			if (isAction&&_index == 7)
			{
				if (!attack)attack = true;
				_fireRenderCount++;
				if (_fireRenderCount % 3 == 0)
				{
					_fireindex++;
				}
				if (_fireindex > 5)
				{
					_fireindex = 0;
					_index = 8;
					isAction = false;
					if (attack)attack = false;
				}
			}
		}
		isTime = false;
	}
	
	if (damageRender)
	{
		_damageRenderCount++;
		if (_damageRenderCount % 3 == 0)
		{
			_damageindex++;
		}
		if (_damageindex > 4)
		{
			_damageindex = 0;
			damageRender = false;
		}
	}

	if (isMove)
	{
		switch (_dir)
		{
		case NONE:
			if (_y >= _rc.bottom - _img->getFrameHeight())
			{
				_y = _rc.bottom - _img->getFrameHeight();
				isMove = false;
				_gravity = 0;
			}
			else
			{
				_gravity += 0.965f;
				_y += -sinf(7 * PI / 9) * 9 + _gravity;
			}
			break;
		case LEFT:
			
			if (_x <= _rc.right - _img->getFrameWidth() / 2 - 18)
			{
				_x = _rc.right - _img->getFrameWidth() / 2 - 18;
				isMove = false;
			
			}
			else
			{
				_x += cosf(7 * PI / 9) * 9;
			}
			if (_y >= _rc.bottom - _img->getFrameHeight())
			{

				_y = _rc.bottom - _img->getFrameHeight();
				isMove = false;
				_gravity = 0;
			}
			else
			{
				_gravity += 0.965f;
				_y += -sinf(7 * PI / 9) * 9 + _gravity;
			}

			break;
		case RIGHT:
	
			if (_x >= _rc.right - _img->getFrameWidth() / 2)
			{
				_x = _rc.right - _img->getFrameWidth() / 2;
				isMove = false;
			}
			else
			{
				_x -= cosf(7 * PI / 9) * 9;
			}
			if (_y >= _rc.bottom - _img->getFrameHeight())
			{
				_y = _rc.bottom - _img->getFrameHeight();
				isMove = false;
				_gravity = 0;
			}
			else
			{
				_gravity += 0.965f;
				_y += -sinf(7 * PI / 9) * 9 + _gravity;
			}

			break;
		case UP:
			if (_y <= _rc.bottom - _img->getFrameHeight())
			{
				_y = _rc.bottom - _img->getFrameHeight();
				isMove = false;
				_gravity = 0;

			}
			else
			{
				_gravity += 0.2f;
				_y += -sinf(PI / 2) * 9 + _gravity;
			}
			break;
		case DOWN:

			if (_y >= _rc.bottom - _img->getFrameHeight())
			{
				_y = _rc.bottom - _img->getFrameHeight();
				isMove = false;
				_gravity = 0;

			}
			else
			{
				_gravity += 1.2f;
				_y += -sinf(PI / 2) + _gravity;

			}
			break;
		}
	}

	if (_hp >= 7)
	{
		switch (_judgmentdir)
		{
		case LEFT:
		case RIGHT:
			_count++;
			if (_count & 10 == 0)
			{
				_index++;
				if (_index > 1)_index=0;
				_count = 0;
			}
			break;
		case UP:
			_count++;
			if (_count & 10 == 0)
			{
				_index++;
				if (_index > 5)_index = 4;
				_count = 0;
			}
			break;
		case DOWN:
			_count++;
			if (_count & 10 == 0)
			{
				_index++;
				if (_index > 3)_index = 2;
				_count = 0;
			}
			break;

		}
	}
	else
	{
		if (!isAction)
		{
			_count++;
			if (_count & 10 == 0)
			{
				_index++;
				if (_index > 9) _index = 8;
				_count = 0;
			}
		}

	}
	if (playerIndexX < _tilex)
	{
		_indey = 0;
	}
	else
	{
		_indey = 1;
	}



}

void deathMetal::release()
{

}

void deathMetal::render(int tileX, int tileY)
{

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		_astar->render();
	}
	if (tileX == _tilex && tileY == _tiley) 
	{
		if (damageRender)
		{
			switch (_astar->getDirection())
			{
			case LEFT:
				IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
					_map->getRect(_tilex, _tiley).left + (_map->getRect(_tilex, _tiley).left - _map->getRect(_tilex, _tiley).right) / 2, _map->getRect(_tilex, _tiley).top, _damageindex, 1);
				break;
			case RIGHT:
				IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
					(_map->getRect(_tilex, _tiley).left + _map->getRect(_tilex, _tiley).right) / 2, _map->getRect(_tilex, _tiley).top, _damageindex, 0);
				break;
			case UP:
				IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
					_map->getRect(_tilex, _tiley).left, _map->getRect(_tilex, _tiley).top + (_map->getRect(_tilex, _tiley).top - _map->getRect(_tilex, _tiley).bottom) / 2, _damageindex, 1);
				break;
			case DOWN:
				IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
					_map->getRect(_tilex, _tiley).left, (_map->getRect(_tilex, _tiley).top + _map->getRect(_tilex, _tiley).bottom) / 2, _damageindex, 1);
				break;
			}
		}
		if (isAction&&_index == 7)
		{
			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				if (_viCollision->tileX == _tilex)
				{
					_viCollision->_img->frameRender(getMemDC(), _viCollision->rc.left, _viCollision->rc.top, _fireindex, 1);
				}
				else if (_viCollision->tileX - 1 == _tilex)
				{
					_viCollision->_img->frameRender(getMemDC(), _viCollision->rc.left, _viCollision->rc.top, _fireindex, 0);
				}
				else
				{
					_viCollision->_img->frameRender(getMemDC(), _viCollision->rc.left, _viCollision->rc.top, _fireindex, 0);
				}
	
			}
		}
		if (_hp == 9)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 0);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 0);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 0);
		}
		if (_hp == 8)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 0);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 0);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		if (_hp == 7)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 0);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 2);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		if (_hp == 6)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 2);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		if (_hp == 5)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 2);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		if (_hp == 4)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 2);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		if (_hp == 3)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 2);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 2);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		if (_hp == 2)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 2);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 2);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 2);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		if (_hp == 1)
		{
			_heart1->frameRender(getMemDC(), _x - 23, _y - 25, 0, 0);
			_heart2->frameRender(getMemDC(), _x + 3, _y - 25, 0, 2);
			_heart3->frameRender(getMemDC(), _x + 33, _y - 25, 0, 2);
			_heart4->frameRender(getMemDC(), _x + 63, _y - 25, 0, 2);
			_heart5->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
			_heart6->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
			_heart7->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			_heart8->frameRender(getMemDC(), _x + 183, _y - 25, 0, 2);
			_heart9->frameRender(getMemDC(), _x + 213, _y - 25, 0, 2);
		}
		_img->frameRender(getMemDC(), _x, _y, _index, _indey);
	}

}

void deathMetal::phaseOneMove(bool Time)
{
	if (Time) {
		int pastX = _tilex;
		int pastY = _tiley;
		if (_astar->getCloseListsize() != 0)
		{
			if (!_map->getIsEnemy(_astar->getClosebackX(), _astar->getClosebackY()))
			{
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex = _astar->getClosebackX();
				_tiley = _astar->getClosebackY();
				_rc = _map->getRect(_tilex, _tiley);
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
			}
		}
		else if (_astar->getCloseListsize() == 0)
		{
			_astar->enemyAttack();
		}
		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = LEFT;
			_judgmentdir = _dir;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = RIGHT;
			_judgmentdir = _dir;
		}
		else if (pastX == _tilex && _tiley - pastY == -1)
		{
			_y += -sinf(PI / 2) * 9;
			_dir = UP;
			_judgmentdir = _dir;
		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_y += -sinf(PI / 2);
			_dir = DOWN;
			_judgmentdir = _dir;
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = NONE;
		}
	}
	if (_hp >= 7)
	{
		_count++;
		switch (_dir)
		{
		case LEFT:
		case RIGHT:
			_index = 0;
			break;
		case UP:
			_index = 4;
			break;
		case DOWN:
			_index = 2;
			break;

		}
	}
	if (!isMove)isMove = true;
}

void deathMetal::phaseTwoThreeMove(bool Time)
{
	
	if (isdamaged)
	{
		int pastX = _tilex;
		int pastY = _tiley;
		if (_tilex > 6)
		{
			_tilex = 3;
		}
		else
		{
			_tilex = 9;
		}

		if (_tiley > 10)
		{
			_tiley = 8;
		}
		else
		{
			_tiley = 12;
		}
		isdamaged = false;
		_x = _map->getRect(_tilex, _tiley).right - _img->getFrameWidth() / 2;
		_y = _map->getRect(_tilex, _tiley).bottom - _img->getFrameHeight();
		if (_map->getIsEnemy(_tilex, _tiley)) {
			_tilex -= 1;
		}
		_map->setIsEnemy(pastX, pastY, false);
		_rc = _map->getRect(_tilex, _tiley);
		_astar->actionMove(_tilex, _tiley);
		_map->setIsEnemy(_tilex, _tiley, true);
	
		_y += -sinf(7 * PI / 9) * 9;
		_index = 8;
		_dir = NONE;
	}
	else if (!isdamaged && Time) {
		++actionCount;
		int x = abs(_tilex - _playerindex);
		int y = abs(_tiley - _playerindey);
		int pastX = _tilex;
		int pastY = _tiley;
		
		if (x >= y)
		{
			if (x >= 3) {
				
				if (_tilex >= _playerindex)
				{
					_tilex -= 1;
				}
				else
				{
					_tilex += 1;
				}
			}
			else
			{
				if (_tilex >= _playerindex)
				{
					_tilex += 1;
				}
				else
				{
					_tilex -= 1;
				}
			}
		}
		else
		{
			if (y >= 3)
			{
				if (_tiley >= _playerindey)
				{
					_tiley -= 1;
				}
				else
				{
					_tiley += 1;
				}
			}
			else
			{
				if (_tiley >= _playerindey)
				{
					_tiley += 1;
				}
				else
				{
					_tiley -= 1;
				}
			}
		}
		if (_map->getIsEnemy(_tilex, _tiley) || _map->getTileObject(_tilex, _tiley) != OBJ_NONE  || _map->getIsPlayer(_tilex,_tiley))
		{
			_tilex = pastX;
			_tiley = pastY;
		}
		else
		{
			_map->setIsEnemy(pastX, pastY, false);
			_rc = _map->getRect(_tilex, _tiley);
			_astar->actionMove(_tilex, _tiley);
			_map->setIsEnemy(_tilex, _tiley, true);
		}
	
		

		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = LEFT;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = RIGHT;
		}
		else if (pastX == _tilex && _tiley - pastY == -1)
		{
			_y += -sinf(PI / 2) * 9;
			_dir = UP;
		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_y += -sinf(PI / 2);
			_dir = DOWN;
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = NONE;
		}
		_index = 8;
		if (actionCount==8)
		{
			_index = 6;
			actionCount = 0;
			isAction = true;
		}
	}
	if (!isMove)isMove = true;

}

void deathMetal::phaseFourMove(bool Time)
{
	if (isdamaged)
	{
		int pastX = _tilex;
		int pastY = _tiley;
		if (_tilex > 6)
		{
			_tilex = 3;
		}
		else
		{
			_tilex = 9;
		}

		if (_tiley > 10)
		{
			_tiley = 8;
		}
		else
		{
			_tiley = 12;
		}
		isdamaged = false;
		isAction == false;
		_x = _map->getRect(_tilex, _tiley).right - _img->getFrameWidth() / 2;
		_y = _map->getRect(_tilex, _tiley).bottom - _img->getFrameHeight();
		if (_map->getIsEnemy(_tilex, _tiley)) {
			_tilex -= 1;
		}
		_map->setIsEnemy(pastX, pastY, false);
		_rc = _map->getRect(_tilex, _tiley);
		_astar->actionMove(_tilex, _tiley);
		_map->setIsEnemy(_tilex, _tiley, true);

		_y += -sinf(7 * PI / 9) * 9;
		_dir = NONE;
		_index = 8;
	}
	else if (isAction && Time)
	{
		if (_index == 6)
		{
			for (int i = 1; i < 12; i++)
			{
				collision _collision;
				_collision.tileX = i;
				_collision.tileY = _tiley;
				_collision.rc = _map->getRect(_collision.tileX, _collision.tileY);
				_collision.isattack = true;
				if (_tilex == i || _tilex + 1 == i)
				{
					_collision._img = IMAGEMANAGER->findImage("dragonRedFireStarting");
				}
				else
				{
					_collision._img = IMAGEMANAGER->findImage("dragonRedFire");
				}
				_vCollision.emplace_back(_collision);
			}
			++_index;
			SOUNDMANAGER->play("deathMetal_fire", 0.4f);
		}
	}
	else if (!isdamaged && !isAction && Time) {

		int pastX = _tilex;
		int pastY = _tiley;
		if (_astar->getCloseListsize() != 0)
		{
			if (!_map->getIsEnemy(_astar->getClosebackX(), _astar->getClosebackY()))
			{
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex = _astar->getClosebackX();
				_tiley = _astar->getClosebackY();
				_rc = _map->getRect(_tilex, _tiley);
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
			}
		}
		else if (_astar->getCloseListsize() == 0)
		{
			_astar->enemyAttack();
		}
		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = LEFT;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = RIGHT;
		}
		else if (pastX == _tilex && _tiley - pastY == -1)
		{
			_y += -sinf(PI / 2) * 9;
			_dir = UP;

		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_y += -sinf(PI / 2);
			_dir = DOWN;
	
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_y += -sinf(7 * PI / 9) * 9;
			_dir = NONE;
		}
		_index = 8;
		if (_tiley == _playerindey)
		{
			++fireCount;
			if (fireCount == 2)
			{
				isAction = true;
				_index = 6;
				fireCount = 0;
				_vCollision.clear();
			}
		}
	
	}

	if (!isMove)isMove = true;
}


void deathMetal::TrapMove()
{
	if (_map->getTileObject(_tilex, _tiley) == TR_JUMP)
	{
		_map->setIsEnemy(_tilex, _tiley, false);
		switch (_dir)
		{
		case LEFT:
			_tilex -= 1;
			break;
		case RIGHT:
			_tilex += 1;
			break;
		case UP:
			_tiley -= 1;
			break;
		case DOWN:
			_tiley += 1;
			break;
		}
		_astar->callPathFinder(_tilex, _tiley);
		_map->setIsEnemy(_tilex, _tiley, true);
		_rc = _map->getRect(_tilex, _tiley);
		if (!isMove)isMove = true;
	}
}
