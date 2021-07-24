#include "stdafx.h"
#include "minotaurAndDragon.h"

HRESULT minotaurAndDragon::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = isMove = false;
	_count = _damageRenderCount = _damageindex = _index = _indey = 0;
	isAction = damageRender = false;
	while (true) //랜덤배치
	{
		int random = RND->getInt(_map->getRoom().size());//랜덤방에 배치
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;// 그 방이 플레이어방이거나 상점이면 컨티뉴  
		_tilex = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tiley = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tilex, _tiley) != OBJ_NONE || _map->getTileTerrain(_tilex, _tiley) != DIRT1 || _map->getIsEnemy(_tilex, _tiley))
			continue; //랜덤하게 찍은 방안의 좌표 중 벽이있어도 컨티뉴
		break;//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져나오기
	}
	_rc = _map->getRect(_tilex, _tiley);
	_map->setIsEnemy(_tilex, _tiley, true);
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY, true);
	return S_OK;
}

void minotaurAndDragon::update(int playerIndexX, int playerIndexY)
{
	if (isAction) {
		if (TIMEMANAGER->getWorldTime() - _movingTime >= 0.5f)
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
		//_astar->endmove(playerIndexX, playerIndexY);
		_astar->clear();
		if (_dir != NONE) minotaurActionMove(isTime);
	}
	else
	{
		if (TIMEMANAGER->getWorldTime() - _movingTime >= 1.0f)
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
			_astar->endmove(playerIndexX, playerIndexY);
			_astar->update();

			if (_map->getTileObject(_tilex, _tiley) == TR_LEFT)
			{
				_dir = LEFT;
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex -= 1;
				_rc = _map->getRect(_tilex, _tiley);
				moveMotion(isTime);
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
				//_astar->callPathFinder();
				isMove = true;
			}
			else if (_map->getTileObject(_tilex, _tiley) == TR_RIGHT)
			{
				_dir = RIGHT;
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex += 1;
				_rc = _map->getRect(_tilex, _tiley);
				moveMotion(isTime);
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
				//_astar->callPathFinder();
				isMove = true;
			}
			else if (_map->getTileObject(_tilex, _tiley) == TR_UP)
			{
				_dir = UP;
				_map->setIsEnemy(_tilex, _tiley, false);
				_tiley -= 1;
				_rc = _map->getRect(_tilex, _tiley);
				moveMotion(isTime);
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
				//_astar->callPathFinder();
				isMove = true;
			}
			else if (_map->getTileObject(_tilex, _tiley) == TR_DOWN)
			{
				_dir = DOWN;
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex += 1;
				_rc = _map->getRect(_tilex, _tiley);
				moveMotion(isTime);
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
				//_astar->callPathFinder();
				isMove = true;
			}
			else if (_astar->getStart())
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
			if (_map->getTileObject(_astar->getClosebackX(), _astar->getClosebackY()) != WALL_DOOR &&
				!_map->getIsEnemy(_astar->getClosebackX(), _astar->getClosebackY()))
			{
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex = _astar->getClosebackX();
				_tiley = _astar->getClosebackY();
				moveMotion(isTime);
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
			}
		}
		else if (_astar->getCloseListsize() == 0)
		{
			_astar->enemyAttack();
		}
		_rc = _map->getRect(_tilex, _tiley);
		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_dir = LEFT;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
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
		isMove = true;
	}
}

void minotaurAndDragon::minotaurActionMove(bool Time)
{
	if (Time) {
		int pastx = _tilex;
		int pasty = _tiley;
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
		if (_tilex == _playerindex && _tiley == _playerindey )
		{
			_astar->enemyAttack();
			if (_astar->getDamage())
			{
				_tilex = pastx;
				_tiley = pasty;
				_dir = NONE;
				_index = 5;
			}
		}
		else if (_map->getTileObject(_tilex, _tiley) == WALL_BASIC ||
			_map->getTileObject(_tilex, _tiley) == WALL_GOLD ||
			_map->getTileObject(_tilex, _tiley) == WALL_STONE)
		{
			_map->setTileObject(_tilex, _tiley, OBJ_NONE);
			_tilex = pastx;
			_tiley = pasty;
			_dir = NONE;
			_index = 5;
		}
		else if(!_map->getIsEnemy(_tilex, _tiley))
		{
			_map->setIsEnemy(pastx, pasty, false);
			_rc = _map->getRect(_tilex, _tiley);
			moveMotion(isTime);
			_map->setIsEnemy(_tilex, _tiley, true);
			_astar->actionMove(_tilex, _tiley);
			isMove = true;
		}
	}
}

void minotaurAndDragon::moveMotion(bool Time)
{
	if (isMove)
	{
		switch (_dir)
		{
		case LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			//_shadow.left += cosf(7 * PI / 9) * 9;
			//_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			if (_x >= (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2))
			{
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2))
				{
					_y = _rc.top - (_rc.bottom - _rc.top) / 2 - (_img->getFrameHeight() / 2);
				}
				//_tileRenderX = _tileX;
			}
			//if (_shadow.left <= _tileRect.left)
			//{
			//	_shadow.left = _tileRect.left;
			//	_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			//}
			break;
		case RIGHT:
			_gravity += 0.965f;
			_x -= cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			//_shadow.left -= cosf(7 * PI / 9) * 10;
			//_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			if (_x <= (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2))
			{
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2))
				{

					_y = _rc.top - (_rc.bottom - _rc.top) / 2 - (_img->getFrameHeight() / 2);
				}
				//_tileRenderX = _tileX;
			}
			//if (_shadow.left >= _tileRect.left)
			//{
			//	_shadow.left = _tileRect.left;
			//	_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			//}

			break;
		case UP:
			_gravity += 0.2f;
			_y += -sinf(PI / 2) * 9 + _gravity;
			//_y -= 9;
			//_shadow.top += -sinf(1 * PI / 2) * 6;
			//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			//if (_shadow.top <= _tileRect.top - 13)
			//{
			//	_shadow.top = _tileRect.top - 13;
			//	_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			if (_y <= _rc.top - (_rc.bottom - _rc.top) / 2 - (_img->getFrameHeight() / 2))
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2 - (_img->getFrameHeight() / 2);
				isMove = false;
				_gravity = 0;
				//_tileRenderY = _tileY;
			}
			//}
			break;
		case DOWN:

			_gravity += 1.2f;
			_y += -sinf(PI / 2) + _gravity;
			//_y -= 9;
			//_shadow.top -= -sinf(1 * PI / 2) * 6;
			//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			//if (_shadow.top >= _tileRect.top - 13)
			//{
			//_shadow.top = _tileRect.top - 13;
			//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2 - (_img->getFrameHeight() / 2))
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2 - (_img->getFrameHeight() / 2);
				isMove = false;
				_gravity = 0;
				//_tileRenderY = _tileY;
			}
			//}
			break;
		}
	}
}
