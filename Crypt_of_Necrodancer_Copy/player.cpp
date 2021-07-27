#include "stdafx.h"
#include "player.h"
#include "weapon.h"
#include "shovel.h"
#include "enemyManager.h"

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
	_attack = false;

	_bomb = new bomb;
	_bomb->init();
	_shopkeeperDistance = 0;

	_isAttacked = false;
	_alpha = 255;

	_attackedElapsedTime = 0;
	_alphaCount = 0;
	_isWall = false;
	_isTouchWall = false;

	_shovelEffectElapsedTime = 0;

	_attackElapsedTime = 0;
	setupPlayerRect();

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	CAMERAMANAGER->updateCamera((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2);
	
	//�̹��� ������ ������Ʈ
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

	//���� �޾��� �� ���ķ���
	if (_isAttacked)
	{
		_attackedElapsedTime += TIMEMANAGER->getElapsedTime();
		if (_attackedElapsedTime >= 0.1f)
		{
			_attackedElapsedTime -= 0.1f;
			if (_alpha == 255)
			{
				_alpha = 0;
				_alphaCount++;
			}
			else
			{
				_alpha = 255;
				_alphaCount++;
			}
		}
		if (_alphaCount >= 5)
		{
			_isAttacked = false;
			_alphaCount = 0;
		}
	}
	else
	{
		_alpha = 255;
	}

	if (_isTouchWall)
	{
		if (!SOUNDMANAGER->isPlaySound("dig_stone") && !SOUNDMANAGER->isPlaySound("dig_dirt") && !SOUNDMANAGER->isPlaySound("dig_stone"))
		{
			_shovelEffectElapsedTime += TIMEMANAGER->getElapsedTime();
			if (_shovelEffectElapsedTime >= 0.1f)
			{
				_shovelEffectElapsedTime -= 0.1f;
				_isTouchWall = false;
			}
			
		}
	}

	if (!_attack)
	{
		_attackElapsedTime += TIMEMANAGER->getElapsedTime();
		if (_attackElapsedTime >= 5.0f)
		{
			_attackElapsedTime -= 5.0f;
			_map->setDirtTileFrameY(0);
		}
	}
	_isWall = false;
	//����ڵ��� ���� ��츸 �ൿ
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove)
		{
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_bomb->fire(_tileX, _tileY, _map->getRect(_tileX, _tileY));
			}
			else
			{
				_playerDirection = LEFT;
				_weapon->update();
				_shovel->update();

				if (_em->getIsCatch())
				{
					_attack = true;
				}
				else
				{
					_tileX -= 1;
					_isMove = true;

					//��� �� �浹ó��
					if (_shovel->getVCollision().size() != 0)
					{
						for (int i = 0; i < _shovel->getVCollision().size(); ++i)
						{
							int sTileX = (*(_shovel->getVCollision().begin() + i)).tileX;
							int sTileY = (*(_shovel->getVCollision().begin() + i)).tileY;
							OBJECT obj = _map->getTileObject(sTileX, sTileY);
							if (_shovel->getShovelName() == "shovelTitanium")
							{
								if (obj == WALL_STONE)
								{
									_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
									_tileX += 1;
									_isMove = false;
									_isWall = true;
									_isTouchWall = true;
									SOUNDMANAGER->play("dig_stone", EFFECTVOLUME);
								}
								else if (obj == WALL_DOOR || obj == WALL_BASIC)
								{
									_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
									_map->setIsHaveTorch(sTileX, sTileY, false);
									_tileX += 1;
									_isMove = false;
									_isWall = true;
									if (obj == WALL_DOOR)
									{
										SOUNDMANAGER->play("door_open", EFFECTVOLUME);
									}
									else
									{
										SOUNDMANAGER->play("dig_dirt", EFFECTVOLUME);
										_isTouchWall = true;
									}
								}
								else if (obj == WALL_END || obj == WALL_GOLD)
								{
									_tileX += 1;
									_isMove = false;
									_isWall = true;
									_isTouchWall = true;
									SOUNDMANAGER->play("dig_fail", 0.2f);
								}
							}
							else
							{
								if (obj == WALL_DOOR || obj == WALL_BASIC)
								{
									_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
									_map->setIsHaveTorch(sTileX, sTileY, false);
									_tileX += 1;
									_isMove = false;
									_isWall = true;
									if (obj == WALL_DOOR)
									{
										SOUNDMANAGER->play("door_open", EFFECTVOLUME);
									}
									else
									{
										SOUNDMANAGER->play("dig_dirt", EFFECTVOLUME);
										_isTouchWall = true;
									}
								}
								else if (obj == WALL_CRACK || obj == WALL_END
									|| obj == WALL_GOLD
									|| obj == WALL_STONE)
								{
									_tileX += 1;
									_isMove = false;
									_isWall = true;
									_isTouchWall = true;
									SOUNDMANAGER->play("dig_fail", EFFECTVOLUME);
								}
							}
						}
					}
					if (!_isWall)
					{
						//������ ���ʹ��� �浹ó��
						if (_weapon->getVCollision().size() != 0)
						{
							for (int i = 0; i < _weapon->getVCollision().size(); ++i)
							{
								if (_map->getIsEnemy((*(_weapon->getVCollision().begin() + i)).tileX, (*(_weapon->getVCollision().begin() + i)).tileY))
								{
									if (_isMove)
									{
										_tileX += 1;
										_isMove = false;
										_attack = true;
										_map->setDirtTileFrameY(1);
									}
								}
							}
						}
					}
				}
			}
		}

	}
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove)
		{
			_playerDirection = RIGHT;
			_weapon->update();
			_shovel->update();
			
			if (_em->getIsCatch())
			{
				_attack = true;
			}
			else
			{
				_tileX += 1;
				_tileRenderX = _tileX;
				_isMove = true;
				
				//��� �� �浹ó��
				if (_shovel->getVCollision().size() != 0)
				{
					for (int i = 0; i < _shovel->getVCollision().size(); ++i)
					{
						int sTileX = (*(_shovel->getVCollision().begin() + i)).tileX;
						int sTileY = (*(_shovel->getVCollision().begin() + i)).tileY;
						OBJECT obj = _map->getTileObject(sTileX, sTileY);
						if (_shovel->getShovelName() == "shovelTitanium")
						{
							if (obj == WALL_STONE)
							{
								_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
								_tileX -= 1;
								_tileRenderX = _tileX;
								_isMove = false;
								_isWall = true;
								_isTouchWall = true;
								SOUNDMANAGER->play("dig_stone", EFFECTVOLUME);
							}
							else if (obj == WALL_DOOR || obj == WALL_BASIC)
							{
								_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
								_map->setIsHaveTorch(sTileX, sTileY, false);
								_tileX -= 1;
								_tileRenderX = _tileX;
								_isMove = false;
								_isWall = true;
								if (obj == WALL_DOOR)
								{
									SOUNDMANAGER->play("door_open", EFFECTVOLUME);
								}
								else
								{
									SOUNDMANAGER->play("dig_dirt", EFFECTVOLUME);
									_isTouchWall = true;
								}
							}
							else if (obj == WALL_END || obj == WALL_GOLD)
							{
								_tileX -= 1;
								_tileRenderX = _tileX;
								_isMove = false;
								_isWall = true;
								_isTouchWall = true;
								SOUNDMANAGER->play("dig_fail", EFFECTVOLUME);
							}
						}
						else
						{
							if (obj == WALL_DOOR || obj == WALL_BASIC)
							{
								_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
								_map->setIsHaveTorch(sTileX, sTileY, false);
								_tileX -= 1;
								_tileRenderX = _tileX;
								_isMove = false;
								_isWall = true;
								if (obj == WALL_DOOR)
								{
									SOUNDMANAGER->play("door_open", EFFECTVOLUME);
								}
								else
								{
									SOUNDMANAGER->play("dig_dirt", EFFECTVOLUME);
									_isTouchWall = true;
								}
							}
							else if (obj == WALL_CRACK || obj == WALL_END
								|| obj == WALL_GOLD
								|| obj == WALL_STONE)
							{
								_tileX -= 1;
								_tileRenderX = _tileX;
								_isMove = false;
								_isWall = true;
								SOUNDMANAGER->play("dig_fail", EFFECTVOLUME);
								_isTouchWall = true;
							}
						}
					}
				}
				if (!_isWall)
				{
					//������ ���ʹ��� �浹ó��
					if (_weapon->getVCollision().size() != 0)
					{
						for (int i = 0; i < _weapon->getVCollision().size(); ++i)
						{
							if (_map->getIsEnemy((*(_weapon->getVCollision().begin() + i)).tileX, (*(_weapon->getVCollision().begin() + i)).tileY))
							{
								if (_isMove)
								{
									_tileX -= 1;
									_isMove = false;
									_attack = true;
									_map->setDirtTileFrameY(1);
								}
							}
						}
					}
				}
			}		
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove)
		{
			_playerDirection = UP;
			_weapon->update();
			_shovel->update();

			if (_em->getIsCatch())
			{
				_attack = true;
			}
			else
			{
				_tileY -= 1;
				_isMove = true;

				//��� �� �浹ó��
				if (_shovel->getVCollision().size() != 0)
				{
					for (int i = 0; i < _shovel->getVCollision().size(); ++i)
					{
						int sTileX = (*(_shovel->getVCollision().begin() + i)).tileX;
						int sTileY = (*(_shovel->getVCollision().begin() + i)).tileY;
						OBJECT obj = _map->getTileObject(sTileX, sTileY);
						if (_shovel->getShovelName() == "shovelTitanium")
						{
							if (obj == WALL_STONE)
							{
								_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
								_tileY += 1;
								_isMove = false;
								_isWall = true;
								_isTouchWall = true;
								SOUNDMANAGER->play("dig_stone", EFFECTVOLUME);
							}
							else if (obj == WALL_DOOR || obj == WALL_BASIC)
							{
								_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
								_map->setIsHaveTorch(sTileX, sTileY, false);
								_tileY += 1;
								_isMove = false;
								_isWall = true;
								if (obj == WALL_DOOR)
								{
									SOUNDMANAGER->play("door_open", EFFECTVOLUME);
								}
								else
								{
									SOUNDMANAGER->play("dig_dirt", EFFECTVOLUME);
									_isTouchWall = true;
								}
							}
							else if (obj == WALL_END || obj == WALL_GOLD)
							{
								_tileY += 1;
								_isMove = false;
								_isWall = true;
								_isTouchWall = true;
								SOUNDMANAGER->play("dig_fail", EFFECTVOLUME);
							}
						}
						else
						{
							if (obj == WALL_DOOR || obj == WALL_BASIC)
							{
								_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
								_map->setIsHaveTorch(sTileX, sTileY, false);
								_tileY += 1;
								_isMove = false;
								_isWall = true;
								if (obj == WALL_DOOR)
								{
									SOUNDMANAGER->play("door_open", EFFECTVOLUME);
								}
								else
								{
									SOUNDMANAGER->play("dig_dirt", EFFECTVOLUME);
									_isTouchWall = true;
								}
							}
							else if (obj == WALL_CRACK || obj == WALL_END
								|| obj == WALL_GOLD
								|| obj == WALL_STONE)
							{
								_tileY += 1;
								_isMove = false;
								_isWall = true;
								_isTouchWall = true;
								SOUNDMANAGER->play("dig_fail", 0.3f);
							}
						}
					}
				}
				if (!_isWall)
				{
					//������ ���ʹ��� �浹ó��
					if (_weapon->getVCollision().size() != 0)
					{
						for (int i = 0; i < _weapon->getVCollision().size(); ++i)
						{
							if (_map->getIsEnemy((*(_weapon->getVCollision().begin() + i)).tileX, (*(_weapon->getVCollision().begin() + i)).tileY))
							{
								if (_isMove)
								{
									_tileY += 1;
									_isMove = false;
									_attack = true;
									_map->setDirtTileFrameY(1);
								}
							}
						}
					}
				}
			}
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_bomb->fire(_tileX, _tileY, _map->getRect(_tileX, _tileY));
			}
			else
			{
				_playerDirection = DOWN;
				_weapon->update();
				_shovel->update();


				if (_em->getIsCatch())
				{
					_attack = true;
				}
				else
				{
					_tileY += 1;
					_tileRenderY = _tileY;
					_isMove = true;

					//��� �� �浹ó��
					if (_shovel->getVCollision().size() != 0)
					{
						for (int i = 0; i < _shovel->getVCollision().size(); ++i)
						{
							int sTileX = (*(_shovel->getVCollision().begin() + i)).tileX;
							int sTileY = (*(_shovel->getVCollision().begin() + i)).tileY;
							OBJECT obj = _map->getTileObject(sTileX, sTileY);
							if (_shovel->getShovelName() == "shovelTitanium")
							{
								if (obj == WALL_STONE)
								{
									_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
									_tileY -= 1;
									_tileRenderY = _tileY;
									_isMove = false;
									_isWall = true;
									_isTouchWall = true;
									SOUNDMANAGER->play("dig_stone", 0.3f);
								}
								else if (obj == WALL_DOOR || obj == WALL_BASIC)
								{
									_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
									_map->setIsHaveTorch(sTileX, sTileY, false);
									_tileY -= 1;
									_tileRenderY = _tileY;
									_isMove = false;
									_isWall = true;
									if (obj == WALL_DOOR)
									{
										SOUNDMANAGER->play("door_open", 0.3f);
									}
									else
									{
										SOUNDMANAGER->play("dig_dirt", 0.3f);
										_isTouchWall = true;
									}
								}
								else if (obj == WALL_END
									|| obj == WALL_GOLD)
								{
									_tileY -= 1;
									_tileRenderY = _tileY;
									_isMove = false;
									_isWall = true;
									_isTouchWall = true;
									SOUNDMANAGER->play("dig_fail", 0.3f);
								}
							}
							else
							{
								if (obj == WALL_DOOR || obj == WALL_BASIC)
								{
									_map->setTileObject(sTileX, sTileY, OBJ_NONE, 0, 0);
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 20.0f);
									_map->setIsHaveTorch(sTileX, sTileY, false);
									_tileY -= 1;
									_tileRenderY = _tileY;
									_isMove = false;
									_isWall = true;
									if (obj == WALL_DOOR)
									{
										SOUNDMANAGER->play("door_open", 0.3f);
									}
									else
									{
										SOUNDMANAGER->play("dig_dirt", 0.3f);
										_isTouchWall = true;
									}
								}
								else if (obj == WALL_CRACK || obj == WALL_END
									|| obj == WALL_GOLD
									|| obj == WALL_STONE)
								{
									_tileY -= 1;
									_tileRenderY = _tileY;
									_isMove = false;
									_isWall = true;
									SOUNDMANAGER->play("dig_fail", 0.3f);
									_isTouchWall = true;
								}
							}
						}
					}
					if (!_isWall)
					{
						//������ ���ʹ��� �浹ó��
						if (_weapon->getVCollision().size() != 0)
						{
							for (int i = 0; i < _weapon->getVCollision().size(); ++i)
							{
								if (_map->getIsEnemy((*(_weapon->getVCollision().begin() + i)).tileX, (*(_weapon->getVCollision().begin() + i)).tileY))
								{
									if (_isMove)
									{
										_tileY -= 1;
										_isMove = false;
										_attack = true;
										_map->setDirtTileFrameY(1);
									}
								}
							}
						}
					}
				}
			
				
				
			}
		}
	}
	_tileRect = _map->getRect(_tileX, _tileY);

	//���� ���
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

	_body = RectMakeCenter(_x, _y,
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight());
	_head = RectMake(_body.left,
		_body.top - 24,
		IMAGEMANAGER->findImage(_headImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_headImageName)->getFrameHeight());

	_vision->update(_tileX, _tileY);

	_bomb->update();
	//damaged();
}


void player::render(int tileX, int tileY)
{
	if (tileX == _tileRenderX && tileY == _tileRenderY)
	{
		//Rectangle(getMemDC(), _shadow);
		IMAGEMANAGER->alphaRender("shadow_standard_1", getMemDC(), _shadow.left, _shadow.top, 125);
		IMAGEMANAGER->alphaRender("shadow_standard_2", getMemDC(), _shadow.left, _shadow.top, 125);
		IMAGEMANAGER->alphaFrameRender(_bodyImageName, getMemDC(), _body.left, _body.top, _currentFrameX, _currentFrameY, _alpha);
		IMAGEMANAGER->alphaFrameRender(_headImageName, getMemDC(), _head.left, _head.top, _currentFrameX, _currentFrameY, _alpha);

		char str[128];
		sprintf_s(str, "bool : %d", _uiManager->getIsIntersectJudge());
		DrawText(getMemDC(), str, strlen(str), &_shadow, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		//_vision->render();
	}
	_bomb->render(tileX, tileY);
}

void player::damaged()
{
	for (int i = 0; i < _em->getVBlackSkeleton().size(); ++i)
	{
		if ((*(_em->getVBlackSkeleton().begin() + i))->getAttck())
		{
			_uiManager->minusHeart(1);
			_isAttacked = true;
			_map->setDirtTileFrameY(0);
			(*(_em->getVBlackSkeleton().begin() + i))->setAttck(false);
			break;
		}
	}
}

void player::setupPlayerRect()
{
	_tileRect = _map->getRect(_tileX, _tileY);
	//�׸��� �ʱ�ȭ
	_shadow = RectMake(_tileRect.left,
		_tileRect.top - SHADOWMARGIN,
		IMAGEMANAGER->findImage("shadow_standard_1")->getWidth(), 
		IMAGEMANAGER->findImage("shadow_standard_1")->getHeight());
	//���� �ʱ�ȭ
	_body = RectMakeCenter((_tileRect.left + _tileRect.right) / 2,
		(_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN,
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight());
	//�Ӹ� �ʱ�ȭ
	_head = RectMake(_body.left,
		_body.top - 24,
		IMAGEMANAGER->findImage(_headImageName)->getFrameWidth(), 
		IMAGEMANAGER->findImage(_headImageName)->getFrameHeight());
	
	_x = (_body.left + _body.right) / 2;
	_y = (_body.top + _body.bottom) / 2;

	_vision->setVisionMapMemoryAddressLink(_map);
	_vision->setSearchBoundary();

	_bomb->setBombMapMemoryAddressLink(_map);

	//ī�޶� ����
	CAMERAMANAGER->setCameraCenter((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2);
}

void player::renderShovelEffect(int tileX, int tileY)
{
	if (_isTouchWall && tileX == _shovel->getVCollision()[0].tileX && tileY == _shovel->getVCollision()[0].tileY)
	{
		if (_shovel->getShovelName() == "shovelTitanium")
		{
			IMAGEMANAGER->findImage("shovelTitanium")->frameRender(getMemDC(), _shovel->getVCollision()[0].rc.left, _shovel->getVCollision()[0].rc.top - (TILESIZE * 5) / 8, 0, 0);
		}
		else
		{
			IMAGEMANAGER->findImage("shovelBasic")->frameRender(getMemDC(), _shovel->getVCollision()[0].rc.left, _shovel->getVCollision()[0].rc.top - (TILESIZE * 5) / 8, 0, 0);
		}
	}
}

