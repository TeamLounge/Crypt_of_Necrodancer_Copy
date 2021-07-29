#include "stdafx.h"
#include "player.h"
#include "weapon.h"
#include "shovel.h"
#include "objectManager.h"


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
	_isRush = false;

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

	_miss = new image;
	_miss = IMAGEMANAGER->findImage("벗어남");
	_miss->setX(CAMERAMANAGER->getCameraCenterX());
	_miss->setY(CAMERAMANAGER->getCameraBOTTOM() - 200);
	_missRange = 0;

	_isMiss = false;
	_isThrow = false;
	_isThrowReady = false;

	_foodName = "food_none";

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

	//공격 받았을 때 알파렌더
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
			_map->setTileFrameY(_tileX, _tileY, 0);
		}
	}
	_isWall = false;
	//심장박동에 맞춘 경우만 행동
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove && !_isRush && !_uiManager->getIsPlayerDead() && !_isThrowReady)
		{
			if (KEYMANAGER->isStayKeyDown(VK_UP)) {
				if (_foodName == "apple")
				{
					_uiManager->minusItemHUD(ITEM);
					_uiManager->plusHeart(2);
					_foodName = "food_none";
				}
				else if (_foodName == "cheese")
				{
					_uiManager->minusItemHUD(ITEM);
					_uiManager->plusHeart(4);
					_foodName = "food_none";

				}
			}
			else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
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
					CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
				}
				else
				{
					_tileX -= 1;
					_isMove = true;

					//삽과 벽 충돌처리
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
						//웨폰과 에너미의 충돌처리
						if (_weapon->getVCollision().size() != 0)
						{
							if (_weapon->getWeaponName() == "rapier")
							{
								if (!_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY) && _map->getIsEnemy(_weapon->getVCollision()[1].tileX, _weapon->getVCollision()[1].tileY))
								{
									_attack = true;
									_isMove = false;
									_isRush = true;
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
								}
								else if (_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY))
								{
									_tileX += 1;
									_isMove = false;
									_attack = true;
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
								}
							}
							else
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
											CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		//판정 벗어났을때
		else if (!_uiManager->getIsIntersectJudge() && !_isMove && !_isThrowReady)
		{
			_isMiss = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
		}

		//던질준비가 되었다면 던져라
		else if (_isThrowReady)
		{
			_playerDirection = LEFT;
			_uiManager->minusItemHUD(PRESS);
			_uiManager->minusItemHUD(THROW);
			_isThrow = true;
			_isThrowReady = false;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove && !_isRush && !_uiManager->getIsPlayerDead() && !_isThrowReady)
		{
			_playerDirection = RIGHT;
			_weapon->update();
			_shovel->update();
			
			if (_em->getIsCatch())
			{
				_attack = true;
				CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			}
			else
			{
				_tileX += 1;
				_tileRenderX = _tileX;
				_isMove = true;
				
				//삽과 벽 충돌처리
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
					//웨폰과 에너미의 충돌처리
					if (_weapon->getVCollision().size() != 0)
					{
						if (_weapon->getWeaponName() == "rapier")
						{
							if (!_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY) && _map->getIsEnemy(_weapon->getVCollision()[1].tileX, _weapon->getVCollision()[1].tileY))
							{
								_attack = true;
								_isMove = false;
								_isRush = true;
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
							}
							else if (_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY))
							{
								_tileX -= 1;
								_isMove = false;
								_attack = true;
								CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
							}
						}
						else
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
										CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
									}
								}
							}
						}
					}
				}
			}		
		}
		//판정 벗어났을때
		else if (!_uiManager->getIsIntersectJudge() && !_isMove && !_isThrowReady)
		{
			_isMiss = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
		}

		//던질준비가 되었다면 던져라
		else if (_isThrowReady)
		{
			_playerDirection = RIGHT;
			_isThrow = true;
			_uiManager->minusItemHUD(PRESS);
			_uiManager->minusItemHUD(THROW);
			_isThrowReady = false;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove && !_isRush && !_uiManager->getIsPlayerDead() && !_isThrowReady)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
				if (_foodName == "apple")
				{
					//_uiManager->minusItemHUD(ITEM);
					_uiManager->plusHeart(2);
					_foodName = "food_none";
				}
				else if (_foodName == "cheese")
				{
					//_uiManager->minusItemHUD(ITEM);
					_uiManager->plusHeart(4);
					_foodName = "food_none";
				}
			}
			else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				for (int i = 0; i < _uiManager->getVItemHUD().size(); ++i)
				{
					if ((*(_uiManager->getVItemHUD().begin() + i))->getItemType() == THROW)
					{
						_uiManager->plusItemHUD(PRESS);
						_isThrowReady = true;
					}
				}
			}
			else
			{
				_playerDirection = UP;
				_weapon->update();
				_shovel->update();

				if (_em->getIsCatch())
				{
					_attack = true;
					CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
				}
				else
				{
					_tileY -= 1;
					_isMove = true;

					//삽과 벽 충돌처리
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
						//웨폰과 에너미의 충돌처리
						if (_weapon->getVCollision().size() != 0)
						{
							if (_weapon->getWeaponName() == "rapier")
							{
								if (!_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY) && _map->getIsEnemy(_weapon->getVCollision()[1].tileX, _weapon->getVCollision()[1].tileY))
								{
									_attack = true;
									_isMove = false;
									_isRush = true;
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
								}
								else if (_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY))
								{
									_tileY += 1;
									_isMove = false;
									_attack = true;
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
								}
							}
							else
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
											CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
										}
									}
								}
							}
						}
					}
				}

			}
		}
		//판정 벗어났을때
		else if (!_uiManager->getIsIntersectJudge() && !_isMove && !_isThrowReady)
		{
			_isMiss = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
		}

		//던질준비가 되었다면 던져라
		else if (_isThrowReady)
		{
			_playerDirection = UP;
			_isThrow = true;
			_uiManager->minusItemHUD(PRESS);
			_uiManager->minusItemHUD(THROW);
			_isThrowReady = false;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_uiManager->getIsIntersectJudge() && !_isMove && !_isRush && !_uiManager->getIsPlayerDead() && !_isThrowReady)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_bomb->fire(_tileX, _tileY, _map->getRect(_tileX, _tileY));
			}

			else if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				for (int i = 0; i < _uiManager->getVItemHUD().size(); ++i)
				{
					if ((*(_uiManager->getVItemHUD().begin() + i))->getItemType() == THROW)
					{
						_uiManager->plusItemHUD(PRESS);
						_isThrowReady = true;
					}
				}
			}

			else
			{
				_playerDirection = DOWN;
				_weapon->update();
				_shovel->update();

				if (_em->getIsCatch())
				{
					_attack = true;
					CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
				}
				else
				{
					_tileY += 1;
					_tileRenderY = _tileY;
					_isMove = true;

					//삽과 벽 충돌처리
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
						//웨폰과 에너미의 충돌처리
						if (_weapon->getVCollision().size() != 0)
						{
							if (_weapon->getWeaponName() == "rapier")
							{
								if (!_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY) && _map->getIsEnemy(_weapon->getVCollision()[1].tileX, _weapon->getVCollision()[1].tileY))
								{
									_attack = true;
									_isMove = false;
									_isRush = true;
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
								}
								else if (_map->getIsEnemy(_weapon->getVCollision()[0].tileX, _weapon->getVCollision()[0].tileY))
								{
									_tileY -= 1;
									_isMove = false;
									_attack = true;
									CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
								}
							}
							else
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
											CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
										}
									}
								}
							}
						}
					}
				}
			
				
				
			}
		}

		//판정 벗어났을때
		else if (!_uiManager->getIsIntersectJudge() && !_isMove && !_isThrowReady)
		{
			_isMiss = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
		}

		//던질준비가 되었다면 던져라
		else if (_isThrowReady)
		{
			_playerDirection = DOWN;
			_isThrow = true;
			_uiManager->minusItemHUD(PRESS);
			_uiManager->minusItemHUD(THROW);
			_isThrowReady = false;
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

	//돌진 모션
	if (_isRush)
	{
		switch (_playerDirection)
		{
		case LEFT:
			if (_x <= (_tileRect.left + _tileRect.right) / 2)
			{
				_x = (_tileRect.left + _tileRect.right) / 2;
				if (_shadow.left <= _tileRect.left)
				{
					_shadow.left = _tileRect.left;
					_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
				}
				_isRush = false;
			}
			else
			{
				_x -= 9;
				_shadow.left -= 9;
				_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
			}
			break;
		case RIGHT:
			if (_x >= (_tileRect.left + _tileRect.right) / 2)
			{
				_x = (_tileRect.left + _tileRect.right) / 2;
				if (_shadow.left >= _tileRect.left)
				{
					_shadow.left = _tileRect.left;
					_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
				}
				_isRush = false;
			}
			else
			{
				_x += 9;
				_shadow.left += 9;
				_shadow.right = _shadow.left + IMAGEMANAGER->findImage("shadow_standard_1")->getWidth();
			}
			break;
		case UP:
			if (_y <= (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN)
			{
				_y = (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN;
				if (_shadow.top <= _tileRect.top - SHADOWMARGIN)
				{
					_shadow.top = _tileRect.top - SHADOWMARGIN;
					_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
				}
				_isRush = false;
			}
			else
			{
				_y -= 9;
				_shadow.top -= 9;
				_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
			}
			break;
		case DOWN:
			if (_y >= (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN)
			{
				_y = (_tileRect.top + _tileRect.bottom) / 2 - BODYMARGIN;
				if (_shadow.top >= _tileRect.top - SHADOWMARGIN)
				{
					_shadow.top = _tileRect.top - SHADOWMARGIN;
					_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
				}
				_isRush = false;
			}
			else
			{
				_y += 9;
				_shadow.top += 9;
				_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("shadow_standard_1")->getHeight();
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
	damaged();
	miss();
}


void player::render(int tileX, int tileY)
{
	if (tileX == _tileRenderX && tileY == _tileRenderY)
	{
		//Rectangle(getMemDC(), _shadow);
		IMAGEMANAGER->alphaRender("shadow_standard_1", getMemDC(), _shadow.left, _shadow.top, 125);
		IMAGEMANAGER->alphaRender("shadow_standard_2", getMemDC(), _shadow.left, _shadow.top, 125);
		if (!_uiManager->getIsPlayerDead())
		{
			IMAGEMANAGER->alphaFrameRender(_bodyImageName, getMemDC(), _body.left, _body.top, _currentFrameX, _currentFrameY, _alpha);
			IMAGEMANAGER->alphaFrameRender(_headImageName, getMemDC(), _head.left, _head.top, _currentFrameX, _currentFrameY, _alpha);
		}
		char str[128];
		sprintf_s(str, "bool : %d", _uiManager->getIsIntersectJudge());
		DrawText(getMemDC(), str, strlen(str), &_shadow, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		

		//_vision->render();
	}
	_bomb->render(tileX, tileY);

	if (_isMiss)
	{
		_miss->render(getMemDC());
	}
}

void player::render()
{
	_vision->render();
}

void player::damaged()
{
	//////////////////////////////////////
	// #### 스켈레톤 공격력 부여 ###
	/////////////////////////////////////

	for (int i = 0; i < _em->getVBlackSkeleton().size(); ++i)
	{
		if ((*(_em->getVBlackSkeleton().begin() + i))->getAttck())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(3);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(2);
			}
			else
			{
				_uiManager->minusHeart(4);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVBlackSkeleton().begin() + i))->setAttck(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	for (int i = 0; i < _em->getVWitheSkeleton().size(); ++i)
	{
		if ((*(_em->getVWitheSkeleton().begin() + i))->getAttck())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(1);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(1);
			}
			else
			{
				_uiManager->minusHeart(2);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVWitheSkeleton().begin() + i))->setAttck(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	for (int i = 0; i < _em->getVGreenSkeleton().size(); ++i)
	{
		if ((*(_em->getVGreenSkeleton().begin() + i))->getAttck())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(1);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(1);
			}
			else
			{
				_uiManager->minusHeart(2);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVGreenSkeleton().begin() + i))->setAttck(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	//////////////////////////////////////
	// #### 미노타우르스 공격력 부여 ###
	/////////////////////////////////////
	for (int i = 0; i < _em->getVMinotaur().size(); i++)
	{
		if ((*(_em->getVSlimeBlue().begin() + i))->getAttack())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(3);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(2);
			}
			else
			{
				_uiManager->minusHeart(4);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVSlimeBlue().begin() + i))->setAttack(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}


	//////////////////////////////////////
	// #### 슬라임 공격력 부여 ###
	/////////////////////////////////////
	for (int i = 0; i < _em->getVSlimeBlue().size(); i++)
	{
		if ((*(_em->getVSlimeBlue().begin() + i))->getAttack())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(1);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(1);
			}
			else
			{
				_uiManager->minusHeart(2);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVSlimeBlue().begin() + i))->setAttack(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	for (int i = 0; i < _em->getVSlimeGold().size(); i++)
	{
		if ((*(_em->getVSlimeGold().begin() + i))->getAttack())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(1);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(1);
			}
			else
			{
				_uiManager->minusHeart(1);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVSlimeGold().begin() + i))->setAttack(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}
	//////////////////////////////////////
	// #### 좀비 공격력 부여 ###
	/////////////////////////////////////
	for (int i = 0; i < _em->getVZombie().size(); i++)
	{
		if ((*(_em->getVZombie().begin() + i))->getAttack())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(1);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(1);
			}
			else
			{
				_uiManager->minusHeart(2);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVZombie().begin() + i))->setAttack(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	//////////////////////////////////////
	// #### 고스트 공격력 부여 ###
	/////////////////////////////////////

	for (int i = 0; i < _em->getVGhost().size(); i++)
	{
		if ((*(_em->getVGhost().begin() + i))->getAttck())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(1);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(1);
			}
			else
			{
				_uiManager->minusHeart(2);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVGhost().begin() + i))->setAttck(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	//////////////////////////////////////
	// #### 미믹 공격력 부여 ###
	/////////////////////////////////////
	for (int i = 0; i < _em->getVMimic().size(); i++)
	{
		if ((*(_em->getVMimic().begin() + i))->getAttck())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(1);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(1);
			}
			else
			{
				_uiManager->minusHeart(2);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVMimic().begin() + i))->setAttck(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	//////////////////////////////////////
	// #### 드래곤 공격력 부여 ###
	/////////////////////////////////////
	for (int i = 0; i < _em->getVRedDragon().size(); i++)
	{
		if ((*(_em->getVRedDragon().begin() + i))->getAttck())
		{
			if (_bodyImageName == "player_body_leather")
			{
				_uiManager->minusHeart(5);
			}
			else if (_bodyImageName == "player_body_chain")
			{
				_uiManager->minusHeart(4);
			}
			else
			{
				_uiManager->minusHeart(6);
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			(*(_em->getVRedDragon().begin() + i))->setAttck(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
			break;
		}
	}

	//////////////////////////////////////
	// #### 데스메탈 공격력 부여 ###
	/////////////////////////////////////
	if (_em->getIsBoss())
	{
		if (_em->getDeathMetal()->getAttck())
		{
			if (_em->getDeathMetal()->getHp() > 2) {
				if (_bodyImageName == "player_body_leather")
				{
					_uiManager->minusHeart(1);
				}
				else if (_bodyImageName == "player_body_chain")
				{
					_uiManager->minusHeart(2);
				}
				else
				{
					_uiManager->minusHeart(3);
				}
			}
			if (_em->getDeathMetal()->getHp() <= 2)
			{
				RECT rc;
				bool isdamaged = false;
				for(int i=0 ; i <_em->getDeathMetal()->_vCollision.size(); i++)
				{
					if (IntersectRect(&rc, &_em->getDeathMetal()->_vCollision[i].rc, &_body))
					{
						if (_em->getDeathMetal()->_vCollision[i].isattack)
						{
							if (_bodyImageName == "player_body_leather")
							{
								_uiManager->minusHeart(1);
									isdamaged = true;
									break;
							}
							else if (_bodyImageName == "player_body_chain")
							{
								_uiManager->minusHeart(2);
								isdamaged = true;
								break;
							}
							else
							{
								_uiManager->minusHeart(3);
								isdamaged = true;
								break;
							}
						}
					}
				}
				if (isdamaged) {
					for (int i = 0; i < _em->getDeathMetal()->_vCollision.size(); i++)
					{   
						_em->getDeathMetal()->_vCollision[i].isattack = false;
					}
				}
			}
			_isAttacked = true;
			_map->setTileFrameY(_tileX, _tileY, 0);
			_em->getDeathMetal()->setAttck(false);
			CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);
		}
	}
}

void player::miss()
{
	if (!_isMiss)
	{
		_miss->setY(CAMERAMANAGER->getCameraBOTTOM() - 200);
		_miss->setX(CAMERAMANAGER->getCameraCenterX() - 36);
		_missRange = 0;
		_missSpeed = 0;
	}

	if (_isMiss)
	{
		_missSpeed = 10;
		_missRange -= (TIMEMANAGER->getElapsedTime() * _missSpeed);
		_miss->setY(_miss->getY() + _missRange);
		_miss->setX(CAMERAMANAGER->getCameraCenterX() - 36);
	}

	if (_missRange / TIMEMANAGER->getElapsedTime() < -200)
	{
		_isMiss = false;
	}
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
	CAMERAMANAGER->updateCamera((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2);
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

