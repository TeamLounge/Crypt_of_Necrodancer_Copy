#include "stdafx.h"
#include "zombie.h"

HRESULT zombie::init()
{
	//상속 init
	_toRender = _damageRender = false;
	_direction = (PLAYER_ENEMY_DIRECTION)RND->getFromIntTo(1, 4); //사방 랜덤
	_pastDirection = NONE;
	_frameCount = 0;
	_frameIndex = 0;

	_isMove = false;		//시작하자마자 움직여
	_isTime = false;

	
	_hp = 1;
	_beatSpeed = 1.0f;

	_gravity = 0;

	_worldTime = TIMEMANAGER->getWorldTime();

	//맵에 뿌려주기
	setArrangement();	//타일에 먼저 뿌리고

	_img = IMAGEMANAGER->findImage("zombie");	//자식
	_rc = _map->getRect(_tileX, _tileY);
	_map->setIsEnemy(_tileX, _tileY, true);
	_x = _rc.left;
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;
	///////////////////////////////////////////////


	return S_OK;
}

void zombie::release()
{
}

void zombie::update()
{
	setZombieFrame();
	moveZombie();
}

void zombie::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	if (_map->getAlpha(_tileX, _tileY) <= 255 && _map->getAlpha(_tileX, _tileY) > 150) {
		_img = IMAGEMANAGER->findImage("zombie");
		_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	}
	else if (_map->getAlpha(_tileX, _tileY) <= 150 && _map->getAlpha(_tileX, _tileY) > 0)
	{
		_img = IMAGEMANAGER->findImage("zombie_dark");
		_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	}
	//_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}

void zombie::setArrangement()
{
	//랜덤 배치
	while (true)
	{
		//랜덤방에 배치
		int random = RND->getInt(_map->getRoom().size());
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;	// 그 방이 플레이어방이거나 상점이면 컨티뉴

		//랜덤하게 찍은 방안의 좌표 중 벽이 있어도 컨티뉴
		_tileX = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tileY = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1
			|| _map->getIsEnemy(_tileX, _tileY))		//복도 tile은 2지만, room으로 배치하니까 무관!
			continue;
		break;		//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져 나오기
	}
}

void zombie::setZombieFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > _beatSpeed / 2)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	_frameCount++;
	if (_frameCount % 8 == 0)
	{
		_frameCount = 0;
		if (_currentFrameX >= IMAGEMANAGER->findImage("zombie")->getMaxFrameX())
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
			_currentFrameY = 2;
		}
		else if (_direction == DOWN)
		{
			_currentFrameY = 3;
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

void zombie::moveZombie()
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatSpeed)	//2박자		//_beatSpeed = 1.0f
	{
		_movingTime = TIMEMANAGER->getWorldTime();

		//점프 아닌 상태 => 방향은 이 때 바꿈
		if (!_isMove)
		{
			if (_direction == NONE)
			{
				//여기서 방향설정
				_direction = _pastDirection;	//이전에 담고 있던 방향을 NONE으로 제자리 뛰고 있을 때 다시 불러와
				
			}

			if (_direction == UP)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY - 1);
				//WALL 판단
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE)
				{
					_direction = DOWN;
				}
				//ENEMY 판단
				else if (_map->getIsEnemy(_tileX, _tileY - 1))		//다음 타일이 enemy면 제자리 점프
				{
					_pastDirection = _direction;	//_past에 이전 값을 일단 저장해주자.
					_direction = NONE;
				}
				//PLAYER 판단
				//else if ()
				//{
				//
				//}
				////TRAP 판단
				//else if ()
				//{
				//
				//}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileY -= 1;							//여길 들어와서 이동하면서 위에 setIsEnemy의 현재 타일은 이전 타일이 된다.
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);	//그리고 여기가 현재 타일이 되고, enemy가 되니까 true
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
				}
				else if (_map->getIsEnemy(_tileX - 1, _tileY))
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
				else if (_map->getIsEnemy(_tileX + 1, _tileY))		//다음 타일이 적이면
				{
					_pastDirection = _direction;
					_direction = NONE;	//제자리 점프			//이 때, 현재 타일과 다음 타일의 에너미는 true					
					
				}
				//제자리 점프하다가 다시 다음 타일이 적이 아니면
				//다시 이동..
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

	//점프 동작들
	//일직선으로 끝까지 달려가기
	if (_isMove)	//_isMove면 점프
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
