#include "stdafx.h"
#include "player.h"
#include "weapon.h"

HRESULT player::init()
{	
	_headImageName = "player_head";
	_bodyImageName = "player_body_basic";
	_tileX = _tileRenderX = _map->getStartRoomX() + 2;
	_tileY = _tileRenderY = _map->getStartRoomY() + 2;
	_elapsedSec = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_gravity = 0;
	_playerDirection = RIGHT;

	_vision = new vision;
	_vision->init(_tileX, _tileY, BASICVISION);

	_isMove = false;

	_bomb = new bomb;
	_bomb->init();

	setupPlayerRect();

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	CAMERAMANAGER->updateCamera((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2);
	
	//이미지 프레임 업데이트
	_elapsedSec += TIMEMANAGER->getElapsedTime();
	if (_elapsedSec >= 0.15f)
	{
		_elapsedSec -= 0.15f;
		if (_currentFrameX >= IMAGEMANAGER->findImage(_headImageName)->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else
		{
			_currentFrameX++;
		}
		if (_playerDirection == LEFT)
		{
			_currentFrameY = 1;
		}
		else if (_playerDirection == RIGHT)
		{
			_currentFrameY = 0;
		}
	}

	//점프모션 하는 중이 아닐때만 방향키 입력 받음
	if (!_isMove)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_bomb->fire(_tileX, _tileY, _map->getRect(_tileX, _tileY));
			}
			else
			{
				_playerDirection = LEFT;
				OBJECT obj = _map->getTileObject(_tileX - 1, _tileY);
				if (obj == WALL_CRACK || obj == WALL_END
					|| obj == WALL_STONE
					|| obj == WALL_GOLD)
				{

				}
				else if (obj == WALL_DOOR || obj == WALL_BASIC)
				{
					_map->setTileObject(_tileX - 1, _tileY, OBJ_NONE, 0, 0);
					CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
					_map->setIsHaveTorch(_tileX - 1, _tileY, false);
				}
				else
				{
					_tileX -= 1;
					_isMove = true;
				}
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_playerDirection = RIGHT;
			OBJECT obj = _map->getTileObject(_tileX + 1, _tileY);
			if (obj == WALL_CRACK || obj == WALL_END
				|| obj == WALL_GOLD
				|| obj == WALL_STONE)
			{

			}
			else if (obj == WALL_DOOR || obj == WALL_BASIC)
			{
				_map->setTileObject(_tileX + 1, _tileY, OBJ_NONE, 0, 0);
				CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
				_map->setIsHaveTorch(_tileX + 1, _tileY, false);
			}
			else
			{
				_tileX += 1;
				_tileRenderX = _tileX;
				_isMove = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_playerDirection = UP;
			OBJECT obj = _map->getTileObject(_tileX, _tileY - 1);
			if (obj == WALL_CRACK || obj == WALL_END
				|| obj == WALL_GOLD 
				|| obj == WALL_STONE)
			{

			}
			else if (obj == WALL_DOOR || obj == WALL_BASIC)
			{
				_map->setTileObject(_tileX, _tileY - 1, OBJ_NONE, 0, 0);
				CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
				_map->setIsHaveTorch(_tileX, _tileY - 1, false);
			}
			else
			{
				_tileY -= 1;
				_isMove = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_bomb->fire(_tileX, _tileY, _map->getRect(_tileX, _tileY));
			}
			else
			{
				_playerDirection = DOWN;
				OBJECT obj = _map->getTileObject(_tileX, _tileY + 1);
				if (obj == WALL_CRACK || obj == WALL_END
					|| obj == WALL_GOLD
					|| obj == WALL_STONE)
				{

				}
				else if (obj == WALL_DOOR || obj == WALL_BASIC)
				{
					_map->setTileObject(_tileX, _tileY + 1, OBJ_NONE, 0, 0);
					CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
					_map->setIsHaveTorch(_tileX, _tileY + 1, false);
				}
				else
				{
					_tileY += 1;
					_tileRenderY = _tileY;
					_isMove = true;
				}
			}
		}
	}
	_tileRect = _map->getRect(_tileX, _tileY);

	//점프 모션
	if (_isMove)
	{
		switch (_playerDirection)
		{
		case LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			_shadow.left += cosf(7 * PI / 9) * 9;
			_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
			if (_x <= (_tileRect.left + _tileRect.right) / 2)
			{
				_x = (_tileRect.left + _tileRect.right) / 2;
				_isMove = false;
				_gravity = 0;
				if (_y >= (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN)
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN;
				}
				_tileRenderX = _tileX;
			}
			if (_shadow.left <= _tileRect.left)
			{
				_shadow.left = _tileRect.left;
				_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
			}
			break;
		case RIGHT:
			_gravity += 0.965f;
			_x -= cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			_shadow.left -= cosf(7 * PI / 9) * 10;
			_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
			if (_x >= (_tileRect.left + _tileRect.right) / 2)
			{
				_x = (_tileRect.left + _tileRect.right) / 2;
				_isMove = false;
				_gravity = 0;
				if (_y >= (_tileRect.top + _tileRect.bottom) / 2/ - BODYMARGIN)
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN;
				}
				_tileRenderX = _tileX;
			}
			if (_shadow.left >= _tileRect.left)
			{
				_shadow.left = _tileRect.left;
				_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
			}
			break;
		case UP:
			_gravity += 0.47f;
			_y += -sinf(1 * PI / 2) * 9 + _gravity;
			//_y -= 9;
			_shadow.top += -sinf(1 * PI / 2) * 6;
			_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
			if (_shadow.top <= _tileRect.top - SHADOWMARGIN)
			{
				_shadow.top = _tileRect.top - SHADOWMARGIN;
				_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
				if (_y >= (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN)
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN;
					_isMove = false;
					_gravity = 0;
					_tileRenderY = _tileY;
				}
			}
			break;
		case DOWN:
			/*
			_y += 9;
			_shadow.top += 9;
			*/
			_gravity += 1.2f;
			_y += -sinf(1 * PI / 2) + _gravity;
			//_y -= 9;
			_shadow.top -= -sinf(1 * PI / 2) * 6;
			_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
			if (_shadow.top >= _tileRect.top - SHADOWMARGIN)
			{
				_shadow.top = _tileRect.top - SHADOWMARGIN;
				_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
				if (_y >= (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN)
				{
					_y = (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN;
					_isMove = false;
					_gravity = 0;	
					_tileRenderY = _tileY;
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

	_vision->update(_tileX, _tileY);

	_bomb->update();

}

void player::render()
{
	//Rectangle(getMemDC(), _shadow);
	IMAGEMANAGER->alphaRender("shadow_standard_1", getMemDC(), _shadow.left, _shadow.top, 125);
	IMAGEMANAGER->alphaRender("shadow_standard_2", getMemDC(), _shadow.left, _shadow.top, 125);
	IMAGEMANAGER->frameRender(_bodyImageName, getMemDC(), _body.left, _body.top, _currentFrameX, _currentFrameY);
	IMAGEMANAGER->frameRender(_headImageName, getMemDC(), _head.left, _head.top, _currentFrameX, _currentFrameY);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		char str[128];
		sprintf_s(str, "x: %d, y: %d", _tileX, _tileY);
		DrawText(getMemDC(), str, strlen(str), &_shadow, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	//_vision->render();
	
}

void player::render(int tileX, int tileY)
{
	if (tileX == _tileRenderX && tileY == _tileRenderY)
	{
		//Rectangle(getMemDC(), _shadow);
		IMAGEMANAGER->alphaRender("shadow_standard_1", getMemDC(), _shadow.left, _shadow.top, 125);
		IMAGEMANAGER->alphaRender("shadow_standard_2", getMemDC(), _shadow.left, _shadow.top, 125);
		IMAGEMANAGER->frameRender(_bodyImageName, getMemDC(), _body.left, _body.top, _currentFrameX, _currentFrameY);
		IMAGEMANAGER->frameRender(_headImageName, getMemDC(), _head.left, _head.top, _currentFrameX, _currentFrameY);

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			char str[128];
			sprintf_s(str, "x: %d, y: %d", _tileX, _tileY);
			DrawText(getMemDC(), str, strlen(str), &_shadow, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
		//_vision->render();
	}
	_bomb->render(tileX, tileY);
}

void player::setupPlayerRect()
{
	_tileRect = _map->getRect(_tileX, _tileY);
	//그림자 초기화
	_shadow = RectMake(_tileRect.left,
		_tileRect.top - SHADOWMARGIN,
		IMAGEMANAGER->findImage("shadow_standard_1")->getWidth(), 
		IMAGEMANAGER->findImage("shadow_standard_1")->getHeight());
	//몸통 초기화
	_body = RectMakeCenter((_tileRect.left + _tileRect.right) / 2,
		(_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN,
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

	_bomb->setBombMapMemoryAddressLink(_map);

	//카메라 설정
	CAMERAMANAGER->setCameraCenter((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2);
}

void player::shopkeeperSound()
{
	
}
