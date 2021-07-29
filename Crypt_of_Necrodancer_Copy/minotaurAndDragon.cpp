#include "stdafx.h"
#include "minotaurAndDragon.h"

HRESULT minotaurAndDragon::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = isMove = false;
	 _count = _damageRenderCount = _damageindex = _fireRenderCount = _fireIndex = _index = _indey = 0;
	isFire = isRun = toRender = damageRender = fireRender = false;
	attack = false;
	_beatspeed = 1.0f;

	while (true) //랜덤배치
	{
		int bossRoom = 0;
		int random = RND->getInt(_map->getRoom().size());//랜덤방에 배치
		for (int i = 0; i < _map->getRoom().size(); ++i)
		{
			if (_map->getRoom()[i].roomState == ROOM_BOSS)	//미니 보스방
			{
				bossRoom = i;
			}
		}
		_tilex = RND->getFromIntTo(_map->getRoom()[bossRoom].x, _map->getRoom()[bossRoom].x + _map->getRoom()[bossRoom].width);
		_tiley = RND->getFromIntTo(_map->getRoom()[bossRoom].y, _map->getRoom()[bossRoom].y + _map->getRoom()[bossRoom].height);
		if (_map->getTileObject(_tilex, _tiley) != OBJ_NONE || _map->getTileTerrain(_tilex, _tiley) != DIRT1 || _map->getIsEnemy(_tilex, _tiley))
			continue; //랜덤하게 찍은 방안의 좌표 중 벽이있어도 컨티뉴
		break;//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져나오기
	}
	_rc = _map->getRect(_tilex, _tiley);
	_map->setIsEnemy(_tilex, _tiley, true);
	_x = _rc.left;								//_x, _y는 이미지를 움직이기 위한 _rc를 토대로 가져온 실제 좌표(정보 가져오기 위함)
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY, true);	//miniBoss = true

	return S_OK;
}

void minotaurAndDragon::update(int playerIndexX, int playerIndexY)
{
	_playerindex = playerIndexX;
	_playerindey = playerIndexY;

	_astar->endmove(playerIndexX, playerIndexY);

	if (isFire || isRun) 
	{
		if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatspeed/2)
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
		_astar->clear();
		if (isRun &&_dir != NONE) minotaurActionMove(isTime);
		if (isFire) redDragonActionMove();
	}
	else
	{
		if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatspeed)
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
			_astar->update();
			if (!isMove &&_astar->getStart())
			{
				minotaurAndDragonMove(isTime);
			}
			isTime = false;
		}
	}
	if (_astar->getDamage())
	{
		damageRender = true;
		_astar->setDamage(false);
		//여기가 에너미가 플레이어한데 어택!
		if (!attack) attack = true;
	}

	if (damageRender)
	{
		_damageRenderCount++;
		if (_damageRenderCount % 3 == 0)
		{
			_damageindex++;
			_damageRenderCount = 0;
		}
		if (_damageindex > 4)
		{
			_damageindex = 0;
			damageRender = false;
		}
	}
	//isFire로 드래곤꺼
	if (fireRender)
	{
		if (!attack) attack = true;
		_fireRenderCount++;
		if (_fireRenderCount % 3 == 0)
		{
			_fireIndex++;
			_fireRenderCount = 0;
		}
		if (_fireIndex > 6)	//화염포 인덱스
		{
			_fireIndex = 0;
			fireRender = false;
			if (attack) attack = false;
			_index = 6;		//드래곤 동작 인덱스
		}
	}
}

void minotaurAndDragon::release()
{
}

void minotaurAndDragon::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		_astar->render();
	}
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
}

void minotaurAndDragon::minotaurAndDragonMove(bool Time)
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
				if (_map->getTileObject(_tilex, _tiley) == WALL_BASIC ||
					_map->getTileObject(_tilex, _tiley) == WALL_CRACK ||
					_map->getTileObject(_tilex, _tiley) == WALL_STONE ||
					_map->getTileObject(_tilex, _tiley) == WALL_GOLD)
				{
					_map->setTileObject(_tilex, _tiley, OBJ_NONE);
				}
				if (_map->getIsHaveTorch(_tilex, _tiley))
				{
					_map->setIsHaveTorch(_tilex, _tiley, false);
				}
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
			_dir = UP;
		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_dir = DOWN;
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_dir = NONE;
		}
	}
	if (!isMove)isMove = true;
}

void minotaurAndDragon::minotaurActionMove(bool Time)
{
	if (Time) {
		int pastx = _tilex;
		int pasty = _tiley;

		if ((_dir == DOWN && _tilex == _playerindex && _tiley+1 == _playerindey) ||
			(_dir == UP &&_tilex == _playerindex && _tiley-1 == _playerindey) ||
			(_dir == LEFT &&_tilex-1 == _playerindex && _tiley == _playerindey)||
			(_dir == RIGHT &&_tilex+1 == _playerindex&& _tiley == _playerindey))
		{
			_astar->enemyAttack();
			if (_astar->getDamage())
			{
				_rc = _map->getRect(_tilex, _tiley);
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
				_dir = NONE;
				_index = 5;
			}
		}
		else if ((_dir == LEFT && (_map->getTileObject(_tilex-1 , _tiley) == WALL_BASIC || _map->getTileObject(_tilex - 1, _tiley) == WALL_GOLD || _map->getTileObject(_tilex-1, _tiley) == WALL_STONE|| _map->getTileObject(_tilex - 1, _tiley) == WALL_DOOR || _map->getTileObject(_tilex - 1, _tiley) == WALL_END)) ||
				(_dir == RIGHT && (_map->getTileObject(_tilex + 1, _tiley) == WALL_BASIC || _map->getTileObject(_tilex + 1, _tiley) == WALL_GOLD || _map->getTileObject(_tilex + 1, _tiley) == WALL_STONE || _map->getTileObject(_tilex + 1, _tiley) == WALL_DOOR || _map->getTileObject(_tilex + 1, _tiley) == WALL_END)) ||
				(_dir == UP && (_map->getTileObject(_tilex, _tiley-1) == WALL_BASIC || _map->getTileObject(_tilex, _tiley - 1) == WALL_GOLD || _map->getTileObject(_tilex, _tiley - 1) == WALL_STONE || _map->getTileObject(_tilex, _tiley-1) == WALL_DOOR || _map->getTileObject(_tilex , _tiley-1) == WALL_END)) ||
				(_dir == DOWN && (_map->getTileObject(_tilex , _tiley+1) == WALL_BASIC || _map->getTileObject(_tilex, _tiley + 1) == WALL_GOLD || _map->getTileObject(_tilex, _tiley + 1) == WALL_STONE || _map->getTileObject(_tilex, _tiley+1) == WALL_DOOR || _map->getTileObject(_tilex , _tiley+1) == WALL_END)))
		{
			if (!isMove) {
				isMove = true;
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

				if (_map->getTileObject(_tilex, _tiley) != WALL_END) 
				{
					_map->setTileObject(_tilex, _tiley, OBJ_NONE);
				}
				if (_map->getIsHaveTorch(_tilex, _tiley))
				{
					_map->setIsHaveTorch(_tilex, _tiley, false);
				}
				_tilex = pastx;
				_tiley = pasty;
				_rc = _map->getRect(_tilex, _tiley);
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
				_dir = NONE;
				_index = 5;
			}
		}
		else if ((_dir == LEFT && !_map->getIsEnemy(_tilex-1, _tiley))||
				(_dir==RIGHT && !_map->getIsEnemy(_tilex +1, _tiley))||
				(_dir==UP && !_map->getIsEnemy(_tilex , _tiley-1))||
				(_dir==DOWN&& !_map->getIsEnemy(_tilex, _tiley+1)))
		{
			if (!isMove) {
				isMove = true;
				switch (_dir)
				{
				case LEFT:
					_y += -sinf(7 * PI / 9) * 9;
					_tilex -= 1;
					break;
				case RIGHT:
					_y += -sinf(7 * PI / 9) * 9;
					_tilex += 1;
					break;
				case UP:
					_tiley -= 1;
					break;
				case DOWN:
					_tiley += 1;
					break;
				}
				_map->setIsEnemy(pastx, pasty, false);
				_rc = _map->getRect(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
				_astar->actionMove(_tilex, _tiley);
			}

		}
	}

}

void minotaurAndDragon::redDragonActionMove()
{

}

void minotaurAndDragon::moveMotion()
{
	if (isMove)
	{
		switch (_dir)
		{
		case NONE:
			_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
			_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
		case LEFT:

			if (_x <= (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2))
			{
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				isMove = false;
		
			}
			else
			{
				_x += cosf(7 * PI / 9) * 9;
			}

			if (_y >= _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2))
			{
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
				_gravity = 0;
				isMove = false;
			}
			else
			{
				_gravity += 0.965f;
				_y += -sinf(7 * PI / 9) * 9 + _gravity;
			}

			break;
		case RIGHT:
		
			if (_x >= (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2))
			{
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				isMove = false;
				
			}
			else
			{
				_x -= cosf(7 * PI / 9) * 9;
			}
			if (_y >= _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2))
			{
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
				_gravity = 0;
				isMove = false;
			}
			else
			{
				_gravity += 0.965f;
				_y += -sinf(7 * PI / 9) * 9 + _gravity;
			}
			
			break;
		case UP:
			_gravity += 0.2f;
			_y += -sinf(PI / 2) * 9 + _gravity;
			
			if (_y <= _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2))
			{
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
				isMove = false;
				_gravity = 0;
			}
			break;
		case DOWN:
			_gravity += 1.2f;
			_y += -sinf(PI / 2) + _gravity;
		
			if (_y >= _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2))
			{
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
				isMove = false;
				_gravity = 0;
			
			}
			break;
		}
	}
}
