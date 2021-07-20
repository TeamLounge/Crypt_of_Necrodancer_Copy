#include "stdafx.h"
#include "player.h"

HRESULT player::init(int tileX, int tileY)
{
	IMAGEMANAGER->addFrameImage("player_head", "image/player/playerHead.bmp", 216, 72, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body_basic", "image/player/playerArmor_basic.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body_leather", "image/player/playerArmor_leather.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body_chain", "image/player/playerArmor_chain.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_shadow", "image/player/shadow_standard1.bmp", 72, 81, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("player_shadow2", "image/player/shadow_standard2.bmp", 72, 81, true, RGB(255, 0, 255), true);
	
	CAMERAMANAGER->setCamera(0, 0);

	_headImageName = "player_head";
	_bodyImageName = "player_body_basic";
	_tileX = tileX;
	_tileY = tileY;
	_elapsedSec = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_gravity = 0;
	_playerDirection = PLAYER_DIRECTION_RIGHT;

	_vision = new vision;
	_vision->init(_tileX, _tileY, 5);
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_elapsedSec += TIMEMANAGER->getElapsedTime();
	if (_elapsedSec >= 0.2f)
	{
		_elapsedSec -= 0.2f;
		if (_currentFrameX >= IMAGEMANAGER->findImage(_headImageName)->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else
		{
			_currentFrameX++;
		}
		if (_playerDirection == PLAYER_DIRECTION_LEFT)
		{
			_currentFrameY = 1;
		}
		else if (_playerDirection == PLAYER_DIRECTION_RIGHT)
		{
			_currentFrameY = 0;
		}
	}
	if (!_isPlayerMove)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_playerDirection = PLAYER_DIRECTION_LEFT;
			OBJECT obj = _map->getTileObject(_tileX - 1, _tileY);
			if (obj == WALL_CRACK || obj == WALL_END
				|| obj == WALL_STONE
				|| obj == WALL_GOLD)
			{

			}
			else if (obj == WALL_DOOR || obj == WALL_BASIC)
			{
				_map->setTileObject(_tileX - 1, _tileY, OBJ_NONE, NULL, NULL);
				_tileX -= 1;
				_isPlayerMove = true;
			}
			else
			{
				_tileX -= 1;
				_isPlayerMove = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_playerDirection = PLAYER_DIRECTION_RIGHT;
			OBJECT obj = _map->getTileObject(_tileX + 1, _tileY);
			if (obj == WALL_CRACK || obj == WALL_END
				|| obj == WALL_GOLD
				|| obj == WALL_STONE)
			{

			}
			else if (obj == WALL_DOOR || obj == WALL_BASIC)
			{
				_map->setTileObject(_tileX + 1, _tileY, OBJ_NONE, NULL, NULL);
				_tileX += 1;
				_isPlayerMove = true;
			}
			else
			{
				_tileX += 1;
				_isPlayerMove = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_playerDirection = PLAYER_DIRECTION_UP;
			OBJECT obj = _map->getTileObject(_tileX, _tileY - 1);
			if (obj == WALL_CRACK || obj == WALL_END
				|| obj == WALL_GOLD 
				|| obj == WALL_STONE)
			{

			}
			else if (obj == WALL_DOOR || obj == WALL_BASIC)
			{
				_map->setTileObject(_tileX, _tileY - 1, OBJ_NONE, NULL, NULL);
				_tileY -= 1;
				_isPlayerMove = true;
			}
			else
			{
				_tileY -= 1;
				_isPlayerMove = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_playerDirection = PLAYER_DIRECTION_DOWN;
			OBJECT obj = _map->getTileObject(_tileX, _tileY + 1);
			if (obj == WALL_CRACK || obj == WALL_END
				|| obj == WALL_GOLD
				|| obj == WALL_STONE)
			{

			}
			else if (obj == WALL_DOOR || obj == WALL_BASIC)
			{
				_map->setTileObject(_tileX, _tileY + 1, OBJ_NONE, NULL, NULL);
				_tileY += 1;
				_isPlayerMove = true;
			}
			else
			{
				_tileY += 1;
				_isPlayerMove = true;
			}
		}
	}
	_tileRect = _map->getRect(_tileX, _tileY);

	if (_isPlayerMove)
	{
		switch (_playerDirection)
		{
		case PLAYER_DIRECTION_LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			_shadow.left += cosf(7 * PI / 9) * 9;
			_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			if (_x <= (_tileRect.left + _tileRect.right) / 2)
			{
				_x = (_tileRect.left + _tileRect.right) / 2;
				_isPlayerMove = false;
				_gravity = 0;
				if (_y >= ((_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3))
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3;
				}
			}
			if (_shadow.left <= _tileRect.left)
			{
				_shadow.left = _tileRect.left;
				_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			}
			break;
		case PLAYER_DIRECTION_RIGHT:
			_gravity += 0.965f;
			_x -= cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			_shadow.left -= cosf(7 * PI / 9) * 10;
			_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			if (_x >= (_tileRect.left + _tileRect.right) / 2)
			{
				_x = (_tileRect.left + _tileRect.right) / 2;
				_isPlayerMove = false;
				_gravity = 0;
				if (_y >= ((_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3))
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3;
				}
			}
			if (_shadow.left >= _tileRect.left)
			{
				_shadow.left = _tileRect.left;
				_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			}
			break;
		case PLAYER_DIRECTION_UP:
			_gravity += 0.47f;
			_y += -sinf(1 * PI / 2) * 9 + _gravity;
			//_y -= 9;
			_shadow.top += -sinf(1 * PI / 2) * 6;
			_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			if (_shadow.top <= _tileRect.top - 37)
			{
				_shadow.top = _tileRect.top - 37;
				_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
				if (_y >= (_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3)
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3;
					_isPlayerMove = false;
					_gravity = 0;
				}
			}
			break;
		case PLAYER_DIRECTION_DOWN:
			/*
			_y += 9;
			_shadow.top += 9;
			*/
			_gravity += 1.2f;
			_y += -sinf(1 * PI / 2) + _gravity;
			//_y -= 9;
			_shadow.top -= -sinf(1 * PI / 2) * 6;
			_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			if (_shadow.top >= _tileRect.top - 37)
			{
				_shadow.top = _tileRect.top - 37;
				_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
				if (_y >= (_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3)
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - TILESIZE / 3;
					_isPlayerMove = false;
					_gravity = 0;
				}
			}
			break;
		default:
			break;
		}
	}
	//_tileRect = _map->getTiles()[_tileY][_tileX].rc;
		
	/*
	_shadow = RectMakeCenter((_tileRect.left + _tileRect.right) / 2, 
		(_tileRect.top + _tileRect.bottom) / 2 - 32,
		IMAGEMANAGER->findImage("player_shadow")->getWidth(),
		IMAGEMANAGER->findImage("player_shadow")->getHeight());
		*/
	_body = RectMakeCenter(_x, _y,
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight());
	_head = RectMake(_body.left,
		_body.top - 24,
		IMAGEMANAGER->findImage(_headImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_headImageName)->getFrameHeight());

	CAMERAMANAGER->updateCamera((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2);

	_vision->update(_tileX, _tileY);
}

void player::render()
{
	//Rectangle(getMemDC(), _shadow);
	IMAGEMANAGER->alphaRender("player_shadow", getMemDC(), _shadow.left, _shadow.top, 125);
	IMAGEMANAGER->alphaRender("player_shadow2", getMemDC(), _shadow.left, _shadow.top, 125);
	IMAGEMANAGER->frameRender(_bodyImageName, getMemDC(), _body.left, _body.top, _currentFrameX, _currentFrameY);
	IMAGEMANAGER->frameRender(_headImageName, getMemDC(), _head.left, _head.top, _currentFrameX, _currentFrameY);\
	char str[128];
	sprintf_s(str, "x: %d, y: %d", _tileX, _tileY);
	DrawText(getMemDC(), str, strlen(str), &_shadow, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	_vision->render();
}

void player::setupPlayerRect()
{
	_tileRect = _map->getRect(_tileX, _tileY);
	//그림자 초기화
	_shadow = RectMake(_tileRect.left,
		_tileRect.top - 37,
		IMAGEMANAGER->findImage("player_shadow")->getWidth(), 
		IMAGEMANAGER->findImage("player_shadow")->getHeight());
	//몸통 초기화
	_body = RectMakeCenter((_tileRect.left + _tileRect.right) / 2,
		(_tileRect.top + _tileRect.bottom) / 2 - TILESIZE/3,
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight());
	//머리 초기화
	_head = RectMake(_body.left,
		_body.top - 24,
		IMAGEMANAGER->findImage(_headImageName)->getFrameWidth(), 
		IMAGEMANAGER->findImage(_headImageName)->getFrameHeight());
	
	_x = (_body.left + _body.right) / 2;
	_y = (_body.top + _body.bottom) / 2;

	_vision->setVisionMapMemoryAddressLink(_map);
	_vision->setSearchBoundary();

	//카메라 설정
	CAMERAMANAGER->setCameraCenter((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2);
}
