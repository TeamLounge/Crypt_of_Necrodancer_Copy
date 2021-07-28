#include "stdafx.h"
#include "slimeGold.h"

HRESULT slimeGold::init(int playerIndexX, int playerIndexY)
{

	slime::init(playerIndexX, playerIndexY);	//상속

	_direction = RIGHT;		//slimeGold는 항상 우측으로 가며 시작

	_img = IMAGEMANAGER->findImage("slimeGold");
	_map->setIsEnemy(_tileX, _tileY, true);	//에너미 타일 속성 ON
	_hp = 1;
	_direction = RIGHT;


	return S_OK;
}

void slimeGold::update(int playerIndexX, int playerIndexY)
{
	_playerIndexX = playerIndexX;
	_playerIndexY = playerIndexY;

	setSlimeFrame();
	moveSlimeGold();

	//다음 타일이 플레이어여서 bool 값이 true 되면
	if (_isPlayer)
	{
		_damageRenderCount++;
		if (_damageRenderCount % 6 == 0)
		{
			_damageIndex++;
			if (_damageIndex > 4)
			{
				_damageIndex = 0;
				_isPlayer = false;
			}
			_damageRenderCount = 0;
		}
	}
}

void slimeGold::release()
{
}

void slimeGold::render(int tileX, int tileY)
{
	if (tileX == _tileX && tileY == _tileY)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _rc);
		}

		//알파 값에 따른 블랙모드
		if (_map->getAlpha(_tileX, _tileY) <= 255 && _map->getAlpha(_tileX, _tileY) > 150) {
			if (_hp == 1)
			{
				_heart = IMAGEMANAGER->findImage("Enemy_heart");
				_heart->frameRender(getMemDC(), _x + 20, _y - 30, 0, 0);
			}
			_img = IMAGEMANAGER->findImage("slimeGold");
			_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		}
		else if (_map->getAlpha(_tileX, _tileY) <= 150 && _map->getAlpha(_tileX, _tileY) > 0)
		{
			if (_hp == 1)
			{
				_heart = IMAGEMANAGER->findImage("Enemy_heart");
				_heart->frameRender(getMemDC(), _x + 20, _y - 30, 0, 0);
			}
			_img = IMAGEMANAGER->findImage("slimeGold_dark");
			_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		}

		attackPlayerRender();
	}
}


void slimeGold::setSlimeFrame()
{
	_frameCount++;
	if (_frameCount % 8 == 0)
	{
		_frameCount = 0;
		if (_currentFrameX >= IMAGEMANAGER->findImage("slimeGold")->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else
		{
			_currentFrameX++;
		}
		//방향 바꿔 보여주기
		if (_direction == UP)
		{
			_currentFrameY = 1;
		}
		else if (_direction == DOWN)
		{
			_currentFrameY = 0;
		}
		if (_direction == LEFT)
		{
			_currentFrameY = 0;
		}
		else if (_direction == RIGHT)
		{
			_currentFrameY = 1;
		}
	}
}

void slimeGold::moveSlimeGold()		//1박자 우, 아래, 좌, 위 .. 길 막으면 반박자마다 때림
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatSpeed / 2)	//1박자
	{
		_movingTime = TIMEMANAGER->getWorldTime();

		if (!_isMove)
		{
			if (_direction == NONE)
			{
				//LEFT
				if (_pastDirection == LEFT)
				{
					if (_tileX - 1 == _playerIndexX && _tileY == _playerIndexY)
					{

						if (!_isAttack)	_isAttack = true;
						_isPlayer = true;			//_isAttack = false는 플레이어쪽에서 맞았다고 정해주고 거기서 꺼줘야한다.
					}
					else
					{
						_direction = _pastDirection;
					}
				}
				//RIGHT
				else if (_pastDirection == RIGHT)
				{
					if ((_tileX + 1 == _playerIndexX) && (_tileY == _playerIndexY))
					{

						if (!_isAttack)	_isAttack = true;
						_isPlayer = true;
					}
					else
					{
						_direction = _pastDirection;
					}
				}
				//UP
				else if (_pastDirection == UP)
				{
					if (_tileX == _playerIndexX && _tileY - 1 == _playerIndexY)
					{

						if (!_isAttack)	_isAttack = true;
						_isPlayer = true;
					}
					else
					{
						_direction = _pastDirection;
					}
				}
				//DOWN
				else if (_pastDirection == DOWN)
				{

					if (_tileX == _playerIndexX && _tileY + 1 == _playerIndexY)
					{
						if (!_isAttack)	_isAttack = true;
						_isPlayer = true;
					}
					else
					{
						_direction = _pastDirection;
					}
				}
			}
			if (_direction == UP)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY - 1);

				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE)
				{
					_direction = DOWN;
				}
				else if (_map->getIsEnemy(_tileX, _tileY - 1))
				{
					_pastDirection = _direction;	//_past에 이전 값을 일단 저장해주자.
					_direction = NONE;
				}
				else if (_tileX == _playerIndexX && _tileY - 1 == _playerIndexY)
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileY -= 1;
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);
				}

				_rc = _map->getRect(_tileX, _tileY);
			}
			else if (_direction == DOWN)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY + 1);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE)
				{
					_direction = UP;
				}
				else if (_map->getIsEnemy(_tileX, _tileY + 1))
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else if (_tileX == _playerIndexX && _tileY + 1 == _playerIndexY)
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileY += 1;
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);
				}

				_rc = _map->getRect(_tileX, _tileY);
			}
			else if (_direction == LEFT)
			{
				OBJECT obj = _map->getTileObject(_tileX - 1, _tileY);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE)
				{
					_direction = RIGHT;
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else if (_map->getIsEnemy(_tileX - 1, _tileY))
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else if (_tileX - 1 == _playerIndexX && _tileY == _playerIndexY)
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileX -= 1;
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);
				}

				_rc = _map->getRect(_tileX, _tileY);
			}
			else if (_direction == RIGHT)
			{
				OBJECT obj = _map->getTileObject(_tileX + 1, _tileY);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE)
				{
					_direction = LEFT;
				}
				else if (_map->getIsEnemy(_tileX + 1, _tileY))		
				{
					_pastDirection = _direction;
					_direction = NONE;	//제자리 점프							

				}
				else if (_tileX + 1 == _playerIndexX && _tileY == _playerIndexY)
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_direction = RIGHT;
					_tileX += 1;
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);
				}

				_rc = _map->getRect(_tileX, _tileY);
			}
			
		}
	}
	//장애물이나 에너미 있으면 움직이지 않고 제자리 뛰기 만들어야함
	/////////////////////////////////////////////////////

	if (TIMEMANAGER->getWorldTime() - _renderTime >= _beatSpeed / 2)	//1박자
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

	//점프
	if (_isMove)	//RIGHT -> DOWN -> LEFT -> UP -> RIGHT ..순서
	{
		switch (_direction)
		{
		case LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;

			if (_x <= _rc.left)
			{
				_x = _rc.left;
				_isMove = false;
				_direction = UP;		//LEFT -> UP
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{
					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
			}
			break;

		case RIGHT:
			_gravity += 0.965f;
			_x -= cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;

			if (_x >= _rc.left)
			{
				_x = _rc.left;
				_isMove = false;
				_direction = DOWN;		//RIGHT -> DOWN
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{

					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
			}
			break;

		case UP:
			_gravity += 0.2f;
			_y += -sinf(PI / 2) * 9 + _gravity;

			if (_y <= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				_isMove = false;
				_direction = RIGHT;		//UP -> RIGHT
				_gravity = 0;
			}
			break;

		case DOWN:
			_gravity += 1.2f;
			_y += -sinf(PI / 2) + _gravity;

			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				_isMove = false;
				_direction = LEFT;		//DOWN -> LEFT
				_gravity = 0;
			}
			break;

		case NONE:
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
}

void slimeGold::attackPlayerRender()
{
	if (_isPlayer)
	{
		switch (_pastDirection)
		{
		case LEFT:
			IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
				_map->getRect(_tileX, _tileY).left + (_map->getRect(_tileX, _tileY).left - _map->getRect(_tileX, _tileY).right) / 2, _map->getRect(_tileX, _tileY).top, _damageIndex, 1);
			break;
		case RIGHT:
			IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
				(_map->getRect(_tileX, _tileY).left + _map->getRect(_tileX, _tileY).right) / 2, _map->getRect(_tileX, _tileY).top, _damageIndex, 0);
			break;
		case UP:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tileX, _tileY).left, _map->getRect(_tileX, _tileY).top + (_map->getRect(_tileX, _tileY).top - _map->getRect(_tileX, _tileY).bottom)* (3 / 2), _damageIndex, 1);
			break;
		case DOWN:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tileX, _tileY).left, (_map->getRect(_tileX, _tileY).top + _map->getRect(_tileX, _tileY).bottom) / 2, _damageIndex, 1);
			break;
		}
	}
}
