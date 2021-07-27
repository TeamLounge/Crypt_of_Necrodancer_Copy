#include "stdafx.h"
#include "zombie.h"

HRESULT zombie::init(int playerIndexX, int playerIndexY)
{
	//��� init
	_toRender = _damageRender = false;
	_direction = (PLAYER_ENEMY_DIRECTION)RND->getFromIntTo(1, 4); //��� ����
	_pastDirection = NONE;
	_frameCount = 0;
	_frameIndex = 0;
	_damageIndex = 0;
	_damageRenderCount = 0;

	_isMove = false;		//�������ڸ��� ������
	_isTime = false;
	_isPlayer = false;
	_isAttack = false;

	
	_hp = 1;
	_beatSpeed = 1.0f;

	_gravity = 0;

	_worldTime = TIMEMANAGER->getWorldTime();

	//�ʿ� �ѷ��ֱ�
	setArrangement();	//Ÿ�Ͽ� ���� �Ѹ���

	_img = IMAGEMANAGER->findImage("zombie");	//�ڽ�
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

void zombie::update(int playerIndexX, int playerIndexY)
{
	_playerIndexX = playerIndexX;
	_playerIndexY = playerIndexY;

	setZombieFrame();
	moveZombie();
	
	//���� Ÿ���� �÷��̾�� bool ���� true �Ǹ�
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

void zombie::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	//���� ���� ���� �����
	if (_map->getAlpha(_tileX, _tileY) <= 255 && _map->getAlpha(_tileX, _tileY) > 150) {
		_img = IMAGEMANAGER->findImage("zombie");
		_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	}
	else if (_map->getAlpha(_tileX, _tileY) <= 150 && _map->getAlpha(_tileX, _tileY) > 0)
	{
		_img = IMAGEMANAGER->findImage("zombie_dark");
		_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	}

	attackPlayerRender();
}

void zombie::setArrangement()
{
	//���� ��ġ
	while (true)
	{
		//�����濡 ��ġ
		int random = RND->getInt(_map->getRoom().size());
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;	// �� ���� �÷��̾���̰ų� �����̸� ��Ƽ��

		//�����ϰ� ���� ����� ��ǥ �� ���� �־ ��Ƽ��
		_tileX = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tileY = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1
			|| _map->getIsEnemy(_tileX, _tileY))		//���� tile�� 2����, room���� ��ġ�ϴϱ� ����!
			continue;
		break;		//// ��� ��Ƽ�� �������� ����ٸ� ���� ������
	}
}

void zombie::setZombieFrame()
{
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
		//���� �ٲ� �����ֱ�
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
	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatSpeed)	//2����		//_beatSpeed = 1.0f
	{
		_movingTime = TIMEMANAGER->getWorldTime();

		//���� �ƴ� ���� => ������ �� �� �ٲ�
		if (!_isMove)
		{
			if (_direction == NONE)
			{
				//���⼭ ���⼳��
				//������ ��� �ִ� ������ NONE���� ���ڸ� �ٰ� ���� �� �ٽ� �ҷ���
				
				//LEFT
				if (_pastDirection == LEFT)
				{
					if (_tileX - 1 == _playerIndexX && _tileY == _playerIndexY)
					{
						if(!_isAttack)	_isAttack = true;
						_isPlayer = true;			//���� Ÿ���� �÷��̾���   ///////_isAttack = false�� �÷��̾��ʿ��� �¾Ҵٰ� �����ְ� �ű⼭ ������Ѵ�.
					}
					else
					{
						_direction = _pastDirection;
					}
				}
				//RIGHT
				else if (_pastDirection == RIGHT)
				{
					if ((_tileX + 1 == _playerIndexX )&& (_tileY == _playerIndexY))
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

				//WALL �Ǵ�
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE)
				{
					_direction = DOWN;
				}
				//ENEMY �Ǵ�
				else if (_map->getIsEnemy(_tileX, _tileY - 1))		//���� Ÿ���� enemy�� ���ڸ� ����
				{
					_pastDirection = _direction;	//_past�� ���� ���� �ϴ� ����������.
					_direction = NONE;
				}
				//PLAYER �Ǵ�
				else if (_tileX == _playerIndexX && _tileY - 1 == _playerIndexY)
				{
					_pastDirection = _direction;
					_direction = NONE;
					_isPlayer = true;

				}
				////TRAP �Ǵ�
				//else if ()
				//{
				//
				//}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileY -= 1;							//���� ���ͼ� �̵��ϸ鼭 ���� setIsEnemy�� ���� Ÿ���� ���� Ÿ���� �ȴ�.
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);	//�׸��� ���Ⱑ ���� Ÿ���� �ǰ�, enemy�� �Ǵϱ� true
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
					//_isPlayer = true;
					_pastDirection = _direction;
					_direction = NONE;
					_isPlayer = true;
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
				else if (_tileX - 1 == _playerIndexX && _tileY == _playerIndexY)
				{
					//_isPlayer = true;
					_pastDirection = _direction;
					_direction = NONE;
					_isPlayer = true;
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
				else if (_map->getIsEnemy(_tileX + 1, _tileY))		//���� Ÿ���� ���̸�
				{
					_pastDirection = _direction;
					_direction = NONE;	//���ڸ� ����			//�� ��, ���� Ÿ�ϰ� ���� Ÿ���� ���ʹ̴� true					
					
				}
				else if (_tileX + 1 == _playerIndexX && _tileY == _playerIndexY)
				{
					//_isPlayer = true;
					_pastDirection = _direction;
					_direction = NONE;
					_isPlayer = true;
				}
				//���ڸ� �����ϴٰ� �ٽ� ���� Ÿ���� ���� �ƴϸ�
				//�ٽ� �̵�..
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

	//���� ���۵�
	//���������� ������ �޷�����
	if (_isMove)	//_isMove�� ����
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

void zombie::attackPlayerRender()
{
	if (_isPlayer)
	{
		switch (_pastDirection)	//_pastDirection���� �ؾ� ���� Ÿ�Ͽ� �°� ���̰���.
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
				_map->getRect(_tileX, _tileY).left, _map->getRect(_tileX, _tileY).top + (_map->getRect(_tileX, _tileY).top - _map->getRect(_tileX, _tileY).bottom)* (3/ 2), _damageIndex, 1);
			break;
		case DOWN:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tileX, _tileY).left, (_map->getRect(_tileX, _tileY).top + _map->getRect(_tileX, _tileY).bottom) / 2, _damageIndex, 1);
			break;
		}
	}
}
