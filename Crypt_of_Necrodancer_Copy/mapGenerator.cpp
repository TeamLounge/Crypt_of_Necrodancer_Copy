#include "stdafx.h"
#include "mapGenerator.h"

HRESULT mapGenerator::init(int width, int height)
{
	_width = width;
	_height = height;

	_isMakeRoom = false;
	_isHaveCorridor = false;

	_worldTime = TIMEMANAGER->getWorldTime();
	_elapsedSec = 0;
	_isEvenLight = false;

	_shopKeeper.x = 0;
	_shopKeeper.y = 0;

	return S_OK;
}

void mapGenerator::release()
{
}

void mapGenerator::update(int tileX, int tileY)
{
	for (int i = tileY - VISIONY/2; i <= tileY + VISIONY/2; ++i)
	{
		if (i < 0) continue;
		if (i >= _height) break;
		for (int j = tileX - VISIONX / 2; j <= tileX + VISIONX / 2; ++j)
		{
			if (j < 0) continue;
			if (j >= _width) break;
			_tiles[i][j].alpha = 0;
		}
	}

	if (TIMEMANAGER->getWorldTime() - _worldTime >= 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		for (int i = tileY - VISIONY / 2; i <= tileY + VISIONY / 2; ++i)
		{
			if (i < 0) continue;
			if (i >= _height) break;
			for (int j = tileX - VISIONX / 2; j <= tileX + VISIONX / 2; ++j)
			{
				if (j < 0) continue;
				if (j >= _width) break;
				if (_tiles[i][j].terrain == STAIR_BOSS)
				{
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
					continue;
				}
				if (_tiles[i][j].terrain == STAIR_NONE)
				{
					_tiles[i][j].terrainFrameX = 1;
					_tiles[i][j].terrainFrameY = 0;
					continue;
				}
				if (i % 2 == 0)
				{
					if (_isEvenLight)
					{
						if (j % 2 == 0)
						{
							_tiles[i][j].terrainFrameX = 1;
						}
						else
						{
							_tiles[i][j].terrainFrameX = 0;
						}
					}
					else
					{
						if (j % 2 == 0)
						{
							_tiles[i][j].terrainFrameX = 0;
						}
						else
						{
							_tiles[i][j].terrainFrameX = 2;
						}
					}
				}
				else
				{
					if (_isEvenLight)
					{
						if (j % 2 == 0)
						{
							_tiles[i][j].terrainFrameX = 0;
						}
						else
						{
							_tiles[i][j].terrainFrameX = 2;
						}
					}
					else
					{
						if (j % 2 == 0)
						{
							_tiles[i][j].terrainFrameX = 1;
						}
						else
						{
							_tiles[i][j].terrainFrameX = 0;
						}
					}
				}
			}

		}

		if (_isEvenLight)
		{
			_isEvenLight = false;
		}
		else
		{
			_isEvenLight = true;
		}
	}

	_elapsedSec += TIMEMANAGER->getElapsedTime();
	if (_elapsedSec >= 0.2f)
	{
		_elapsedSec -= 0.2f;

		//횃불 업데이트
		if (IMAGEMANAGER->findImage("wall_torch")->getFrameX() >= IMAGEMANAGER->findImage("wall_torch")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("wall_torch")->setFrameX(0);
			IMAGEMANAGER->findImage("wall_torch_black")->setFrameX(0);
		}
		else
		{
			IMAGEMANAGER->findImage("wall_torch")->setFrameX(IMAGEMANAGER->findImage("wall_torch")->getFrameX() + 1);
			IMAGEMANAGER->findImage("wall_torch_black")->setFrameX(IMAGEMANAGER->findImage("wall_torch_black")->getFrameX() + 1);
		}

		//아이템 움직임
		for (int i = tileY - VISIONY / 2; i <= tileY + VISIONY / 2; ++i)
		{
			if (i < 0) continue;
			if (i >= _height) break;
			for (int j = tileX - VISIONX / 2; j <= tileX + VISIONX / 2; ++j)
			{
				if (j < 0) continue;
				if (j >= _width) break;

				if (_tiles[i][j].item != MAP_ITEM_NONE && _tiles[i][j].item != MAP_COIN10)
				{
					switch (_tiles[i][j].itemDirection)
					{
					case UP:
						if (_tiles[i][j].itemRect.top <= _tiles[i][j].rc.top - TILESIZE / 2 - 5)
						{
							_tiles[i][j].itemDirection = DOWN;
						}
						_tiles[i][j].itemRect.top -= 1;
						_tiles[i][j].itemRect.bottom = _tiles[i][j].itemRect.top + TILESIZE;
						break;
					case DOWN:
						if (_tiles[i][j].itemRect.top >= _tiles[i][j].rc.top - TILESIZE / 2 + 5)
						{
							_tiles[i][j].itemDirection = UP;
						}
						_tiles[i][j].itemRect.top += 1;
						_tiles[i][j].itemRect.bottom = _tiles[i][j].itemRect.top + TILESIZE;
						break;
					}
				}
			}
		}
	}
}

void mapGenerator::render(int tileX, int tileY, bool isTile)
{
	if (isTile)
	{
		for (int i = tileY - VISIONY / 2; i <= tileY + VISIONY / 2; ++i)
		{
			if (i < 0) continue;
			if (i >= _height) break;
			for (int j = tileX - VISIONX / 2; j <= tileX + VISIONX / 2; ++j)
			{
				if (j < 0) continue;
				if (j >= _width) break;
				if (_tiles[i][j].alpha <= 0) continue;
				if (_tiles[i][j].obj == WALL_BASIC || _tiles[i][j].obj == WALL_CRACK || _tiles[i][j].obj == WALL_END || _tiles[i][j].obj == WALL_GOLD || _tiles[i][j].obj == WALL_STONE) continue;
				switch (_tiles[i][j].terrain)
				{
				case DIRT1:
					IMAGEMANAGER->alphaFrameRender("dirt1_tile", getMemDC(),
						_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY, _tiles[i][j].alpha);
					break;
				case DIRT2:
					IMAGEMANAGER->alphaFrameRender("dirt2_tile", getMemDC(),
						_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY, _tiles[i][j].alpha);
					break;
				case BOSS:
					IMAGEMANAGER->alphaFrameRender("boss_tile", getMemDC(),
						_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY, _tiles[i][j].alpha);
					break;
				case WATER:
					IMAGEMANAGER->alphaFrameRender("water_tile", getMemDC(),
						_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY, _tiles[i][j].alpha);
					break;
				case SHOP:
					IMAGEMANAGER->alphaFrameRender("shop_tile", getMemDC(),
						_tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 0, _tiles[i][j].alpha);
					break;
				case STAIR_BOSS:
					IMAGEMANAGER->alphaFrameRender("stair_miniboss_tile", getMemDC(),
						_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY, _tiles[i][j].alpha);
					break;
				case STAIR_NONE:
					IMAGEMANAGER->alphaFrameRender("stair_locked_tile", getMemDC(),
						_tiles[i][j].rc.left, _tiles[i][j].rc.top, 1, 0, _tiles[i][j].alpha);
					break;
				case EMPTY:
					break;
				}
			}
		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < _rooms.size(); i++)
			{
				char str[128];
				if (_rooms[i].roomState == ROOM_START)
				{
					sprintf_s(str, "start");
					TextOut(getMemDC(), _tiles[_rooms[i].y][_rooms[i].x].rc.left, _tiles[_rooms[i].y][_rooms[i].x].rc.top, str, strlen(str));
				}
				if (_rooms[i].roomState == ROOM_BOSS)
				{
					sprintf_s(str, "boss");
					TextOut(getMemDC(), _tiles[_rooms[i].y][_rooms[i].x].rc.left, _tiles[_rooms[i].y][_rooms[i].x].rc.top, str, strlen(str));
				}
			}
		}
	}
	else
	{
		if (_tiles[tileY][tileX].alpha <= 0) return;
		switch (_tiles[tileY][tileX].obj)
		{
		case OBJ_NONE:
			break;
		case WALL_BASIC:
			IMAGEMANAGER->frameRender("walls1", getMemDC(), _tiles[tileY][tileX].rc.left, _tiles[tileY][tileX].rc.top - (TILESIZE * 5) / 8, _tiles[tileY][tileX].objectFrameX, _tiles[tileY][tileX].objectFrameY);
			IMAGEMANAGER->alphaRender("wall_black", getMemDC(), _tiles[tileY][tileX].rc.left, _tiles[tileY][tileX].rc.top - (TILESIZE * 5) / 8, 255 - _tiles[tileY][tileX].alpha);
			break;
		case WALL_GOLD:
		case WALL_STONE:
		case WALL_CRACK:
		case WALL_DOOR:
		case WALL_END:
			IMAGEMANAGER->frameRender("walls2", getMemDC(), _tiles[tileY][tileX].rc.left,
				_tiles[tileY][tileX].rc.top - (TILESIZE * 5) / 8, _tiles[tileY][tileX].objectFrameX, _tiles[tileY][tileX].objectFrameY);
			IMAGEMANAGER->alphaRender("wall_black", getMemDC(), _tiles[tileY][tileX].rc.left, _tiles[tileY][tileX].rc.top - (TILESIZE * 5) / 8, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_BOMB:
			IMAGEMANAGER->frameRender("bomb_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("bomb_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_UP:
			IMAGEMANAGER->frameRender("up_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("up_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_DOWN:
			IMAGEMANAGER->frameRender("down_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("down_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_LEFT:
			IMAGEMANAGER->frameRender("left_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("left_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_RIGHT:
			IMAGEMANAGER->frameRender("right_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("right_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_FAST:
			IMAGEMANAGER->frameRender("fast_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("fast_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_SLOW:
			IMAGEMANAGER->frameRender("slow_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("slow_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_JUMP:
			IMAGEMANAGER->frameRender("jump_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("jump_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_DOOR:
			IMAGEMANAGER->frameRender("door_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("door_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case TR_SPIKE:
			IMAGEMANAGER->frameRender("spike_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 0);
			IMAGEMANAGER->alphaFrameRender("spike_trap", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, _tiles[tileY][tileX].objectFrameX, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case RED_ITEM_BOX:
			IMAGEMANAGER->frameRender("red_item_box", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("red_item_box", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameHeight() / 2, 1, 0, 255 - _tiles[tileY][tileX].alpha);
			break;
		case BLACK_ITEM_BOX:
			IMAGEMANAGER->frameRender("black_item_box", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("black_item_box", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameHeight() / 2, 1, 0, 255 - _tiles[tileY][tileX].alpha);
			break;
		case SHOPKEEPER:
			IMAGEMANAGER->frameRender("shopkeeper", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("shopkeeper")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("shopkeeper")->getFrameHeight() / 2 - 50);
			IMAGEMANAGER->alphaFrameRender("shopkeeper_dark", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("shopkeeper_dark")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("shopkeeper_dark")->getFrameHeight() / 2 - 50, 255 - _tiles[tileY][tileX].alpha);
			break;
		}

		if (_tiles[tileY][tileX].isHaveTorch)
		{
			IMAGEMANAGER->frameRender("wall_torch", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("wall_torch")->getFrameWidth() / 2 - 5,
				_tiles[tileY][tileX].rc.top - (TILESIZE * 5) / 8 - TILESIZE / 3);
			IMAGEMANAGER->alphaFrameRender("wall_torch_black", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("wall_torch_black")->getFrameWidth() / 2 - 5,
				_tiles[tileY][tileX].rc.top - (TILESIZE * 5) / 8 - TILESIZE / 3, 255 - _tiles[tileY][tileX].alpha);
		}

		if (_tiles[tileY][tileX].item != MAP_ITEM_NONE && _tiles[tileY][tileX].item != MAP_COIN10)
		{
			IMAGEMANAGER->alphaRender("shadow_standard_1", getMemDC(), _tiles[tileY][tileX].rc.left, _tiles[tileY][tileX].rc.top - TILESIZE/2 + 5, 125);
			IMAGEMANAGER->alphaRender("shadow_standard_2", getMemDC(), _tiles[tileY][tileX].rc.left, _tiles[tileY][tileX].rc.top + TILESIZE / 2 + 5, 125);
		}

		switch (_tiles[tileY][tileX].item)
		{
		case MAP_ITEM_NONE:
			break;
		case MAP_TORCH_PLUS_1:
			IMAGEMANAGER->frameRender("torch_plus_1", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("torch_plus_1")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("torch_plus_1")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("torch_plus_1", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("torch_plus_1")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("torch_plus_1")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_TORCH_PLUS_2:
			IMAGEMANAGER->frameRender("torch_plus_2", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("torch_plus_2")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("torch_plus_2")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("torch_plus_2", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("torch_plus_2")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("torch_plus_2")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_TITANUM_SHOVEL:
			IMAGEMANAGER->frameRender("shovelTitanium", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("shovelTitanium")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("shovelTitanium")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("shovelTitanium", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("shovelTitanium")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("shovelTitanium")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_LEATHER_ARMOR:
			IMAGEMANAGER->frameRender("leather_armor", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("leather_armor")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("leather_armor")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("leather_armor", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("leather_armor")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("leather_armor")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_CHAIN_ARMOR:
			IMAGEMANAGER->frameRender("chain_armor", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("chain_armor")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("chain_armor")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("chain_armor", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("chain_armor")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("chain_armor")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_DAGGER:
			IMAGEMANAGER->frameRender("dagger", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("dagger")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("dagger")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("dagger", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("dagger")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("dagger")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_BROADSWORD:
			IMAGEMANAGER->frameRender("broadSword", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("broadSword")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("broadSword")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("broadSword", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("broadSword")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("broadSword")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_RAPIER:
			IMAGEMANAGER->frameRender("rapier", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("rapier")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("rapier")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("rapier", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("rapier")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("rapier")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_LONGSWORD:
			IMAGEMANAGER->frameRender("longSword", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("longSword")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("longSword")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("longSword", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("longSword")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("longSword")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_SPEAR:
			IMAGEMANAGER->frameRender("spear", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("spear")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("spear")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("spear", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("spear")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("spear")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_APPLE:
			IMAGEMANAGER->frameRender("apple", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("apple")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("apple")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("apple", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("apple")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("apple")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_CHEESE:
			IMAGEMANAGER->frameRender("cheese", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("cheese")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("cheese")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("cheese", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("cheese")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("cheese")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_COIN10:
			IMAGEMANAGER->frameRender("coin10", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("coin10")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("coin10")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("coin10", getMemDC(),
				(_tiles[tileY][tileX].rc.left + _tiles[tileY][tileX].rc.right) / 2 - IMAGEMANAGER->findImage("coin10")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].rc.bottom + _tiles[tileY][tileX].rc.top) / 2 - IMAGEMANAGER->findImage("coin10")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		case MAP_BOMB:
			IMAGEMANAGER->frameRender("bombX3", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("bombX3")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("bombX3")->getFrameHeight() / 2, 0, 0);
			IMAGEMANAGER->alphaFrameRender("bombX3", getMemDC(),
				(_tiles[tileY][tileX].itemRect.left + _tiles[tileY][tileX].itemRect.right) / 2 - IMAGEMANAGER->findImage("bombX3")->getFrameWidth() / 2,
				(_tiles[tileY][tileX].itemRect.bottom + _tiles[tileY][tileX].itemRect.top) / 2 - IMAGEMANAGER->findImage("bombX3")->getFrameHeight() / 2, 0, 1, 255 - _tiles[tileY][tileX].alpha);
			break;
		default:
			break;
		}
	}
}

void mapGenerator::generate(int maxFeatures)
{
	while (1)
	{
		if (_rooms.size() == maxFeatures) break;

		//여기가 생성
		_tiles.clear();
		vector<vector<tagTile>>().swap(_tiles);
		_rooms.clear();
		vector<tagRoom>().swap(_rooms);
		_corridors.clear();
		vector<tagRoom>().swap(_corridors);
		_exits.clear();
		vector<tagRoom>().swap(_exits);
		for (int i = 0; i < _height; ++i)
		{
			vector<tagTile> vTile;
			for (int j = 0; j < _width; ++j)
			{
				tagTile tile;
				tile.rc = RectMake(j * TILESIZE, i * TILESIZE + MARGIN, TILESIZE, TILESIZE);
				tile.itemRect = RectMake(j * TILESIZE, i * TILESIZE + MARGIN - (TILESIZE/2), TILESIZE, TILESIZE);
				tile.terrain = EMPTY;
				tile.obj = OBJ_NONE;
				tile.item = MAP_ITEM_NONE;
				tile.itemDirection = NONE;
				tile.terrainFrameX = NULL;
				tile.terrainFrameY = NULL;
				tile.objectFrameX = NULL;
				tile.objectFrameY = NULL;
				tile.isHaveTorch = false;
				tile.alpha = 0;
				tile.isSeen = false;
				tile.isBombFired = false;
				vTile.push_back(tile);
			}
			_tiles.push_back(vTile);
		}

		if (!makeRoom(_width / 2, _height / 2, static_cast<ROOM_DIRECTION>(RND->getInt(4), true)))
		{
			return;
		}
		//스타트 지점 랜덤 지정
		_startRoomIndex = RND->getFromIntTo(1, 6);
		//방들을 만들고
		for (int i = 1; i < (maxFeatures - 1) * 2 - 1; ++i)
		{
			if (i % 2 != 0)
			{
				_isMakeRoom = false;
			}
			else
			{
				_isMakeRoom = true;
			}
			if (!createFeature())
			{
				break;
			}
		}
		//마지막에 상점을 만든다
		makeShop();

		//방들 사이 빈 공간에 타일 채우기

		//y축으로 조사
		for (int j = 0; j < _tiles[0].size(); j++)
		{
			bool _isEmptyRoom = false;;
			for (int i = 0; i < _tiles.size() - 1; i++)
			{
				if (_tiles[i][j].terrain == DIRT1)
				{
					if (_tiles[i + 1][j].terrain == EMPTY)
					{
						POINT p;
						p.x = j;
						p.y = i + 1;
						_newRoomYIndex.push_back(p);
						_isEmptyRoom = true;
					}
				}
				else if (_isEmptyRoom)
				{
					if (_tiles[i + 1][j].terrain == DIRT1)
					{
						POINT p;
						p.x = j;
						p.y = i + 1;
						_newRoomYIndex.push_back(p);
						_isEmptyRoom = false;
					}
				}
			}
			if (_isEmptyRoom && !_newRoomYIndex.empty())
			{
				_newRoomYIndex.pop_back();
			}
		}

		//타일 놓기
		for (int i = 0; i < _newRoomYIndex.size(); i++)
		{
			if (i % 2 == 0)
			{
				if (_newRoomYIndex[i + 1].y - _newRoomYIndex[i].y >= 5) continue;
				for (int j = _newRoomYIndex[i].y; j < _newRoomYIndex[i + 1].y; j++)
				{
					_tiles[j][_newRoomYIndex[i].x].terrain = DIRT1;
					_tiles[j][_newRoomYIndex[i].x].terrainFrameX = 0;
					_tiles[j][_newRoomYIndex[i].x].terrainFrameY = 0;
					_tiles[j][_newRoomYIndex[i].x].obj = OBJ_NONE;
					_tiles[j][_newRoomYIndex[i].x].objectFrameX = NULL;
					_tiles[j][_newRoomYIndex[i].x].objectFrameY = NULL;
				}
			}
		}
		vector<POINT>::iterator iter;
		for (iter = _newRoomYIndex.begin(); iter != _newRoomYIndex.end();)
		{
			if ((iter + 1)->y - iter->y >= 5)
			{
				iter = _newRoomYIndex.erase(iter);
				iter = _newRoomYIndex.erase(iter);
			}
			else
			{
				iter += 2;
			}
		}

		//미니룸에 추가
		for (int i = 0; i < _newRoomYIndex.size();)
		{
			tagRoom room;
			room.x = _newRoomYIndex[i].x;
			room.y = _newRoomYIndex[i].y;
			room.width = 1;
			room.height = _newRoomYIndex[i + 1].y - _newRoomYIndex[i].y;
			int j = i + 2;
			for (; j < _newRoomYIndex.size();)
			{
				if (_newRoomYIndex[i].y == _newRoomYIndex[j].y && _newRoomYIndex[i].x + (j - i) / 2 == _newRoomYIndex[j].x)
				{
					room.width++;
					j += 2;
				}
				else
				{
					break;
				}
			}
			i = j;
			_miniRooms.push_back(room);
		}

		//x축으로 조사
		for (int i = 0; i < _tiles.size(); i++)
		{
			bool _isEmptyRoom = false;;
			for (int j = 0; j < _tiles[i].size() - 1; j++)
			{
				if (_tiles[i][j].terrain == DIRT1)
				{
					if (_tiles[i][j + 1].terrain == EMPTY)
					{
						POINT p;
						p.x = j + 1;
						p.y = i;
						_newRoomXIndex.push_back(p);
						_isEmptyRoom = true;
					}
				}
				else if (_isEmptyRoom)
				{
					if (_tiles[i][j + 1].terrain == DIRT1)
					{
						POINT p;
						p.x = j + 1;
						p.y = i;
						_newRoomXIndex.push_back(p);
						_isEmptyRoom = false;
					}
				}
			}
			if (_isEmptyRoom)
			{
				_newRoomXIndex.pop_back();
			}
		}
		//타일 놓기
		for (int i = 0; i < _newRoomXIndex.size(); i++)
		{
			if (i % 2 == 0)
			{
				if (_newRoomXIndex[i + 1].x - _newRoomXIndex[i].x >= 5) continue;
				for (int j = _newRoomXIndex[i].x; j < _newRoomXIndex[i + 1].x; j++)
				{
					_tiles[_newRoomXIndex[i].y][j].terrain = DIRT1;
					_tiles[_newRoomXIndex[i].y][j].terrainFrameX = 0;
					_tiles[_newRoomXIndex[i].y][j].terrainFrameY = 0;
					_tiles[_newRoomXIndex[i].y][j].obj = OBJ_NONE;
					_tiles[_newRoomXIndex[i].y][j].objectFrameX = NULL;
					_tiles[_newRoomXIndex[i].y][j].objectFrameY = NULL;
				}
			}
		}


		for (iter = _newRoomXIndex.begin(); iter != _newRoomXIndex.end();)
		{
			if ((iter + 1)->x - iter->x >= 5)
			{
				iter = _newRoomXIndex.erase(iter);
				iter = _newRoomXIndex.erase(iter);
			}
			else
			{
				iter += 2;
			}
		}



		//미니룸으로 추가
		for (int i = 0; i < _newRoomXIndex.size();)
		{
			tagRoom room;
			room.x = _newRoomXIndex[i].x;
			room.y = _newRoomXIndex[i].y;
			room.width = _newRoomXIndex[i + 1].x - _newRoomXIndex[i].x;
			room.height = 1;
			int j = i + 2;
			for (; j < _newRoomXIndex.size();)
			{
				if (_newRoomXIndex[i].x == _newRoomXIndex[j].x && _newRoomXIndex[i].y + (j - i) / 2 == _newRoomXIndex[j].y)
				{
					room.height++;
					j += 2;
				}
				else
				{
					break;
				}
			}
			i = j;
			_miniRooms.push_back(room);
			_miniRooms[0].x;
		}

		//채운 빈공간 주위 벽 쌓기(y축조사)
		for (int i = 1; i < _tiles.size() - 1; i++)
		{
			for (int j = 0; j < _tiles[i].size(); j++)
			{
				if (_tiles[i][j].terrain == EMPTY)
				{
					if (_tiles[i - 1][j].terrain == DIRT1 && _tiles[i - 1][j].obj == OBJ_NONE)
					{
						_tiles[i][j].terrain = DIRT1;
						_tiles[i][j].terrainFrameX = 0;
						_tiles[i][j].terrainFrameY = 0;
						_tiles[i][j].obj = WALL_BASIC;
						_tiles[i][j].objectFrameX = RND->getInt(8);
						_tiles[i][j].objectFrameY = RND->getInt(2);
					}
					if (_tiles[i + 1][j].terrain == DIRT1 && _tiles[i + 1][j].obj == OBJ_NONE)
					{
						_tiles[i][j].terrain = DIRT1;
						_tiles[i][j].terrainFrameX = 0;
						_tiles[i][j].terrainFrameY = 0;
						_tiles[i][j].obj = WALL_BASIC;
						_tiles[i][j].objectFrameX = RND->getInt(8);
						_tiles[i][j].objectFrameY = RND->getInt(2);
					}
				}
			}
		}
		//x축조사
		for (int i = 0; i < _tiles.size(); i++)
		{
			for (int j = 1; j < _tiles[i].size() - 1; j++)
			{
				if (_tiles[i][j].terrain == EMPTY)
				{
					if (_tiles[i][j - 1].terrain == DIRT1 && _tiles[i][j - 1].obj == OBJ_NONE)
					{
						_tiles[i][j].terrain = DIRT1;
						_tiles[i][j].terrainFrameX = 0;
						_tiles[i][j].terrainFrameY = 0;
						_tiles[i][j].obj = WALL_BASIC;
						_tiles[i][j].objectFrameX = RND->getInt(8);
						_tiles[i][j].objectFrameY = RND->getInt(2);
					}
					if (_tiles[i][j + 1].terrain == DIRT1 && _tiles[i][j + 1].obj == OBJ_NONE)
					{
						_tiles[i][j].terrain = DIRT1;
						_tiles[i][j].terrainFrameX = 0;
						_tiles[i][j].terrainFrameY = 0;
						_tiles[i][j].obj = WALL_BASIC;
						_tiles[i][j].objectFrameX = RND->getInt(8);
						_tiles[i][j].objectFrameY = RND->getInt(2);
					}
				}
			}
		}

		vector<tagRoom>::iterator roomIter;
		for (roomIter = _miniRooms.begin(); roomIter != _miniRooms.end();)
		{
			if (roomIter->height <= 1 || roomIter->width <= 1)
			{
				for (int j = roomIter->y; j < roomIter->y + roomIter->height; j++)
				{
					for (int k = roomIter->x; k < roomIter->x + roomIter->width; k++)
					{
						_tiles[j][k].obj = WALL_BASIC;
						_tiles[j][k].objectFrameX = RND->getInt(8);
						_tiles[j][k].objectFrameY = RND->getInt(2);
					}
				}
				roomIter = _miniRooms.erase(roomIter);
			}
			else
			{
				roomIter++;
			}
		}

		while (1)
		{
			if (_miniRooms.size() <= 3) break;
			else
			{
				int num = RND->getInt(_miniRooms.size());
				for (int i = _miniRooms[num].y; i < _miniRooms[num].y + _miniRooms[num].height; i++)
				{
					for (int j = _miniRooms[num].x; i < _miniRooms[num].x + _miniRooms[num].width; j++)
					{
						if (_tiles[i][j].obj == OBJ_NONE)
						{
							_tiles[i][j].obj = WALL_BASIC;
							_tiles[i][j].objectFrameX = RND->getInt(8);
							_tiles[i][j].objectFrameY = RND->getInt(2);
						}
					}
				}
				_miniRooms.erase(_miniRooms.begin() + num);
			}
		}

		//벽쌓기
		for (int i = 1; i < _tiles.size() - 1; i++)
		{
			for (int j = 0; j < _tiles[i].size(); j++)
			{
				if (_tiles[i][j].terrain == EMPTY)
				{
					if (_tiles[i - 1][j].terrain == DIRT1 || _tiles[i + 1][j].terrain == DIRT1)
					{
						_newWallIndex.emplace_back(POINT{ j, i });
					}
				}
			}
		}
		for (int i = 0; i < _newWallIndex.size(); i++)
		{
			_tiles[_newWallIndex[i].y][_newWallIndex[i].x].terrain = DIRT1;
			_tiles[_newWallIndex[i].y][_newWallIndex[i].x].terrainFrameX = 0;
			_tiles[_newWallIndex[i].y][_newWallIndex[i].x].terrainFrameY = 0;
			_tiles[_newWallIndex[i].y][_newWallIndex[i].x].obj = WALL_BASIC;
			_tiles[_newWallIndex[i].y][_newWallIndex[i].x].objectFrameX = RND->getInt(8);
			_tiles[_newWallIndex[i].y][_newWallIndex[i].x].objectFrameY = RND->getInt(2);
		}

		setEndBlock();
		setEndEdge();
		moveMap();
		setEndBlock();
		deleteEmptyTiles();
	}
	setBossRoom();
	setStone();
	setTorch();
	settingTraps();
	settingItemBox();

	_width = _tiles[0].size();
	_height = _tiles.size();

	for (int i = _rooms.size() - 1; i >= 0 ; i--)
	{
		if (_rooms[i].roomState == ROOM_SHOP)
		{
			for (int j = _rooms[i].y; j < _rooms[i].y + _rooms[i].height; j++)
			{
				for (int k = _rooms[i].x; k < _rooms[i].x + _rooms[i].width; k++)
				{
					if (_tiles[j][k].obj == SHOPKEEPER)
					{
						_shopKeeper.x = k;
						_shopKeeper.y = j;
						break;
					}
				}
			}
		}
	}

	testObject();
	
	MINIMAP->setupMiniMap(_width, _height);
}

void mapGenerator::generateBossMap()
{
	_tiles.clear();
	vector<vector<tagTile>>().swap(_tiles);
	//처음 타일 초기화
	for (int i = 0; i < BOSSMAPY; ++i)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < BOSSMAPX; ++j)
		{
			tagTile tile;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE + MARGIN, TILESIZE, TILESIZE);
			tile.itemRect = RectMake(j * TILESIZE, i * TILESIZE + MARGIN - (TILESIZE / 2), TILESIZE, TILESIZE);
			tile.terrain = EMPTY;
			tile.obj = OBJ_NONE;
			tile.item = MAP_ITEM_NONE;
			tile.itemDirection = NONE;
			tile.terrainFrameX = 0;
			tile.terrainFrameY = 0;
			tile.objectFrameX = 0;
			tile.objectFrameY = 0;
			tile.isHaveTorch = false;
			tile.alpha = 0;
			tile.isSeen = false;
			tile.isBombFired = false;
			vTile.push_back(tile);
		}
		_tiles.push_back(vTile);
	}

	//맵 타일 깔기
	for (int i = 0; i < BOSSMAPY; ++i)
	{
		if ((i >= 0 && i <= 4) || i >= 18 && i < BOSSMAPY)
		{
			for (int j = 3; j <= 9; ++j)
			{
				_tiles[i][j].terrain = BOSS;
			}
		}
		else if (i >= 5 && i <= 15)
		{
			for (int j = 0; j < BOSSMAPX; ++j)
			{
				_tiles[i][j].terrain = BOSS;
			}
		}
		else
		{
			for (int j = 4; j <= 8; ++j)
			{
				_tiles[i][j].terrain = BOSS;
			}
		}
	}

	//벽 치기
	for (int i = 0; i < BOSSMAPY; ++i)
	{
		if (i == 0 || i == BOSSMAPY - 1)
		{
			for (int j = 3; j <= 9; ++j)
			{
				_tiles[i][j].obj = WALL_END;
				_tiles[i][j].objectFrameY = 3;
				_tiles[i][j].objectFrameX = RND->getFromIntTo(1, 6);
			}
		}
		else if ((i >= 1 && i <= 4) || (i >= 18 && i <= BOSSMAPY - 2))
		{
			if (i == 18)
			{
				_tiles[i][4].obj = WALL_END;
				_tiles[i][4].objectFrameY = 3;
				_tiles[i][4].objectFrameX = RND->getFromIntTo(1, 6);

				_tiles[i][8].obj = WALL_END;
				_tiles[i][8].objectFrameY = 3;
				_tiles[i][8].objectFrameX = RND->getFromIntTo(1, 6);
			}
			_tiles[i][3].obj = WALL_END;
			_tiles[i][3].objectFrameY = 3;
			_tiles[i][3].objectFrameX = RND->getFromIntTo(1, 6);

			_tiles[i][9].obj = WALL_END;
			_tiles[i][9].objectFrameY = 3;
			_tiles[i][9].objectFrameX = RND->getFromIntTo(1, 6);
		}
		else if (i == 5) //여기가 보스 죽이면 벽 뚫려야 할 곳
		{
			for (int j = 0; j < BOSSMAPX; j++)
			{
				_tiles[i][j].obj = WALL_END;
				_tiles[i][j].objectFrameY = 3;
				_tiles[i][j].objectFrameX = RND->getFromIntTo(1, 6);
			}
			/*
			for (int j = 0; j <= 3; j++)
			{
				_tiles[i][j].obj = WALL_END;
				_tiles[i][j].objectFrameY = 3;
				_tiles[i][j].objectFrameX = RND->getFromIntTo(1, 6);
			}
			for (int j = BOSSMAPX - 1; j >= 9; --j)
			{
				_tiles[i][j].obj = WALL_END;
				_tiles[i][j].objectFrameY = 3;
				_tiles[i][j].objectFrameX = RND->getFromIntTo(1, 6);
			}
			*/
		}
		else if (i >= 6 && i <= 14)
		{
			_tiles[i][0].obj = WALL_END;
			_tiles[i][0].objectFrameY = 3;
			_tiles[i][0].objectFrameX = RND->getFromIntTo(1, 6);

			_tiles[i][BOSSMAPX - 1].obj = WALL_END;
			_tiles[i][BOSSMAPX - 1].objectFrameY = 3;
			_tiles[i][BOSSMAPX - 1].objectFrameX = RND->getFromIntTo(1, 6);
		}
		else if (i == 15)
		{
			for (int j = 0; j < BOSSMAPX; j++)
			{
				if (j >= 0 && j <= 4)
				{
					_tiles[i][j].obj = WALL_END;
					_tiles[i][j].objectFrameY = 3;
					_tiles[i][j].objectFrameX = RND->getFromIntTo(1, 6);
					if (j == 4)
					{
						_tiles[i][j].isHaveTorch = true;
					}
				}
				else if (j >= 8 && j < BOSSMAPX)
				{
					_tiles[i][j].obj = WALL_END;
					_tiles[i][j].objectFrameY = 3;
					_tiles[i][j].objectFrameX = RND->getFromIntTo(1, 6);
					if (j == 8)
					{
						_tiles[i][j].isHaveTorch = true;
					}
				}
				else
				{
					_tiles[i][j].obj = WALL_DOOR;
					_tiles[i][j].objectFrameY = 2;
					_tiles[i][j].objectFrameX = 4;
				}
			}
		}
		else if (i >= 16 && i <= 17)
		{
			_tiles[i][4].obj = WALL_END;
			_tiles[i][4].objectFrameY = 3;
			_tiles[i][4].objectFrameX = RND->getFromIntTo(1, 6);

			_tiles[i][8].obj = WALL_END;
			_tiles[i][8].objectFrameY = 3;
			_tiles[i][8].objectFrameX = RND->getFromIntTo(1, 6);
		}

		//횃불 있는 중간 벽 설치
		if (i == 2 || i == 4 || i == 20 || i == 22)
		{
			_tiles[i][5].obj = WALL_END;
			_tiles[i][5].objectFrameY = 3;
			_tiles[i][5].objectFrameX = RND->getFromIntTo(1, 6);
			_tiles[i][5].isHaveTorch = true;

			_tiles[i][7].obj = WALL_END;
			_tiles[i][7].objectFrameY = 3;
			_tiles[i][7].objectFrameX = RND->getFromIntTo(1, 6);
			_tiles[i][7].isHaveTorch = true;
		}

		if (i == 3)
		{
			//계단 설치
			_tiles[i][6].terrain = STAIR_NONE;
		}
		else if (i == 7)
		{
			//함정 설치
			_tiles[i][2].obj = TR_JUMP;

			_tiles[i][6].obj = TR_JUMP;

			_tiles[i][10].obj = TR_JUMP;
		}
		else if (i == 10 || i == 13)
		{
			//함정 설치
			_tiles[i][2].obj = TR_JUMP;

			_tiles[i][10].obj = TR_JUMP;
		}
	}

	

	tagRoom room;
	room.width = 5;
	room.height = 5;
	room.x = 4;
	room.y = 19;
	_rooms.push_back(room);
	_startRoomIndex = 0;

	room.width = 11;
	room.height = 9;
	room.x = 1;
	room.y = 6;
	_rooms.push_back(room);
	_bossRoomIndex = 1;

	MINIMAP->setupMiniMap(_width, _height);
}

bool mapGenerator::makeRoom(int x, int y, ROOM_DIRECTION dir, bool firstRoom, int index)
{
	int minRoomSize = 5;
	int maxRoomSize = 8;
	tagRoom room;
	if (_rooms.size() == _startRoomIndex)
	{
		room.roomState = ROOM_START;
		room.width = 5;
		room.height = 5;
	}
	else
	{
		room.width = RND->getFromIntTo(minRoomSize, maxRoomSize);
		room.height = RND->getFromIntTo(minRoomSize, maxRoomSize);
		room.roomState = ROOM_BASIC;
	}


	switch (dir)
	{
	case NORTH:
		room.x = x - room.width / 2;
		room.y = y - room.height;
		break;
	case SOUTH:
		room.x = x - room.width / 2;
		room.y = y + 1;
		break;
	case WEST:
		room.x = x - room.width;
		room.y = y - room.height / 2;
		break;
	case EAST:
		room.x = x + 1;
		room.y = y - room.height / 2;
		break;
	case DIRECTIONCOUNT:
		break;
	default:
		break;
	}

	if (room.x < 3 || room.y < 3 || room.x + room.width + 2 >= _tiles[0].size() || room.y + room.height + 2 >= _tiles.size())
	{
		return false;
	}

	if (placeTile(room, OBJ_NONE, NULL, NULL))
	{
		_rooms.emplace_back(room);

		if (dir != SOUTH || firstRoom)
			_exits.emplace_back(tagRoom{ room.x, room.y - 1, room.width, 1 });
		if (dir != NORTH || firstRoom)
		{
			_exits.emplace_back(tagRoom{ room.x, room.y + room.height, room.width, 1 });
		}
		if (dir != EAST || firstRoom) // west side
			_exits.emplace_back(tagRoom{ room.x - 1, room.y, 1, room.height });
		if (dir != WEST || firstRoom) // east side
			_exits.emplace_back(tagRoom{ room.x + room.width, room.y, 1, room.height });
		return true;
	}
	return false;
}

bool mapGenerator::makeCorridor(int x, int y, ROOM_DIRECTION dir)
{
	int minCorridorLength = 0;
	int maxCorridorLength = 2;

	tagRoom corridor;
	corridor.x = x;
	corridor.y = y;

	switch (dir)
	{
	case NORTH:
		corridor.width = 1;
		corridor.height = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.height == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.y = y - corridor.height;
		break;
	case SOUTH:
		corridor.width = 1;
		corridor.height = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.height == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.y = y + 1;
		break;
	case WEST:
		corridor.height = 1;
		corridor.width = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.width == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.x = x - corridor.width;
		break;
	case EAST:
		corridor.height = 1;
		corridor.width = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.width == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.x = x + 1;
		break;
	default:
		break;
	}

	if (corridor.x < 3 || corridor.y < 3 || corridor.y + corridor.height + 2 >= _tiles.size() || corridor.x + corridor.width + 2 >= _tiles[0].size())
	{
		return false;
	}
	if (placeTile(corridor, OBJ_NONE, NULL, NULL))
	{
		_corridors.emplace_back(corridor);
		switch (dir)
		{
		case NORTH:
			_exits.emplace_back(tagRoom{ corridor.x, corridor.y - 1, corridor.width, 1 });
			_corridorDirection = NORTH;
			break;
		case SOUTH:
			_exits.emplace_back(tagRoom{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
			_corridorDirection = SOUTH;
			break;
		case WEST:
			_exits.emplace_back(tagRoom{ corridor.x - 1 , corridor.y, 1, corridor.height });
			_corridorDirection = WEST;
			break;
		case EAST:
			_exits.emplace_back(tagRoom{ corridor.x + corridor.width, corridor.y, 1, corridor.height });
			_corridorDirection = EAST;
			break;
		case DIRECTIONCOUNT:
			break;
		default:
			break;
		}
		_isHaveCorridor = true;
		return true;
	}

	return false;
}

bool mapGenerator::makeShop()
{
	for (int i = 0; i < 1000; ++i)
	{
		int r = RND->getInt(_exits.size());
		int x, y;
		if (_exits[r].width - 1 == 0)
		{
			x = _exits[r].x;
		}
		else
		{
			x = RND->getFromIntTo(_exits[r].x, _exits[r].x + _exits[r].width - 1);
		}
		if (_exits[r].height - 1 == 0)
		{
			y = _exits[r].y;
		}
		else
		{
			y = RND->getFromIntTo(_exits[r].y, _exits[r].y + _exits[r].height - 1);
		}
		for (int j = 0; j < DIRECTIONCOUNT; ++j)
		{
			if (makeShop(x, y, static_cast<ROOM_DIRECTION>(j)))
			{
				_exits.erase(_exits.begin() + r);
				return true;
			}
		}
	}
	return false;
}

bool mapGenerator::makeShop(int x, int y, ROOM_DIRECTION dir)
{
	tagRoom room;
	room.roomState = ROOM_SHOP;
	switch (dir)
	{
	case NORTH:
		room.width = 7;
		room.height = 8;
		room.x = x - room.width / 2;
		room.y = y - room.height;
		break;
	case SOUTH:
		room.width = 7;
		room.height = 8;
		room.x = x - room.width / 2;
		room.y = y + 1;
		break;
	case WEST:
		room.width = 6;
		room.height = 9;
		room.x = x - room.width;
		room.y = y - room.height / 2;
		break;
	case EAST:
		room.width = 6;
		room.height = 9;
		room.x = x + 1;
		room.y = y - room.height / 2;
		break;
	case DIRECTIONCOUNT:
		break;
	default:
		break;
	}

	if (placeTile(room, OBJ_NONE, NULL, NULL, true, dir))
	{
		_rooms.emplace_back(room);

		if (dir != SOUTH)
			_exits.emplace_back(tagRoom{ room.x, room.y - 1, room.width, 1 });
		if (dir != NORTH)
		{
			_exits.emplace_back(tagRoom{ room.x, room.y + room.height, room.width, 1 });
		}
		if (dir != EAST) // west side
			_exits.emplace_back(tagRoom{ room.x - 1, room.y, 1, room.height });
		if (dir != WEST) // east side
			_exits.emplace_back(tagRoom{ room.x + room.width, room.y, 1, room.height });

		_tiles[y][x].obj = WALL_DOOR;
		_tiles[y][x].objectFrameY = 2;
		if (dir == WEST || dir == EAST)
		{
			_tiles[y][x].objectFrameX = 5;
		}
		else
		{
			_tiles[y][x].objectFrameX = 4;
		}
		return true;
		return true;
	}
	return false;
}

bool mapGenerator::placeTile(const tagRoom & room, OBJECT obj, int objectFrameX, int objectFrameY, bool _isShop, ROOM_DIRECTION dir)
{
	if (room.x < 1 || room.y < 1 || room.x + room.width > _width - 1 || room.y + room.height > _height - 1)
		return false;

	for (int y = room.y; y < room.y + room.height; ++y)
	{
		for (int x = room.x; x < room.x + room.width; ++x)
		{
			if (_tiles[y][x].terrain != EMPTY)
				return false;
		}
	}

	if (_isShop)
	{
		for (int y = room.y - 1; y < room.y + room.height + 1; ++y)
		{
			for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
			{
				_tiles[y][x].terrain = DIRT1;
				_tiles[y][x].terrainFrameX = 0;
				_tiles[y][x].terrainFrameY = 0;
				_tiles[y][x].obj = obj;
				_tiles[y][x].objectFrameX = objectFrameX;
				_tiles[y][x].objectFrameY = objectFrameY;
			}

			switch (dir)
			{
			case NORTH:
			case SOUTH:
			case WEST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x - 1].terrain = DIRT1;
					_tiles[y][room.x - 1].terrainFrameX = 0;
					_tiles[y][room.x - 1].terrainFrameY = 0;
					_tiles[y][room.x - 1].obj = WALL_BASIC;
					_tiles[y][room.x - 1].objectFrameX = 0;
					_tiles[y][room.x - 1].objectFrameY = 0;
				}
				_tiles[y][room.x].terrain = DIRT1;
				_tiles[y][room.x].terrainFrameX = 0;
				_tiles[y][room.x].terrainFrameY = 0;
				_tiles[y][room.x].obj = WALL_GOLD;
				_tiles[y][room.x].objectFrameX = 0;
				_tiles[y][room.x].objectFrameY = 0;
				break;
			case EAST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x - 1].terrain = DIRT1;
					_tiles[y][room.x - 1].terrainFrameX = 0;
					_tiles[y][room.x - 1].terrainFrameY = 0;
					_tiles[y][room.x - 1].obj = WALL_GOLD;
					_tiles[y][room.x - 1].objectFrameX = 0;
					_tiles[y][room.x - 1].objectFrameY = 0;
				}
				else
				{
					_tiles[y][room.x - 1].terrain = DIRT1;
					_tiles[y][room.x - 1].terrainFrameX = 0;
					_tiles[y][room.x - 1].terrainFrameY = 0;
					_tiles[y][room.x - 1].obj = WALL_BASIC;
					_tiles[y][room.x - 1].objectFrameX = 0;
					_tiles[y][room.x - 1].objectFrameY = 0;
				}
				break;
			default:
				break;
			}

			switch (dir)
			{
			case NORTH:
			case SOUTH:
			case EAST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x + room.width - 1].terrain = DIRT1;
					_tiles[y][room.x + room.width - 1].terrainFrameX = 0;
					_tiles[y][room.x + room.width - 1].terrainFrameY = 0;
					_tiles[y][room.x + room.width - 1].obj = WALL_GOLD;
					_tiles[y][room.x + room.width - 1].objectFrameX = 0;
					_tiles[y][room.x + room.width - 1].objectFrameY = 0;
				}
				_tiles[y][room.x + room.width].terrain = DIRT1;
				_tiles[y][room.x + room.width].terrainFrameX = 0;
				_tiles[y][room.x + room.width].terrainFrameY = 0;
				_tiles[y][room.x + room.width].obj = WALL_BASIC;
				_tiles[y][room.x + room.width].objectFrameX = 0;
				_tiles[y][room.x + room.width].objectFrameY = 0;
				break;
			case WEST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x + room.width].terrain = DIRT1;
					_tiles[y][room.x + room.width].terrainFrameX = 0;
					_tiles[y][room.x + room.width].terrainFrameY = 0;
					_tiles[y][room.x + room.width].obj = WALL_GOLD;
					_tiles[y][room.x + room.width].objectFrameX = 0;
					_tiles[y][room.x + room.width].objectFrameY = 0;
				}
				else
				{
					_tiles[y][room.x + room.width].terrain = DIRT1;
					_tiles[y][room.x + room.width].terrainFrameX = 0;
					_tiles[y][room.x + room.width].terrainFrameY = 0;
					_tiles[y][room.x + room.width].obj = WALL_BASIC;
					_tiles[y][room.x + room.width].objectFrameX = 0;
					_tiles[y][room.x + room.width].objectFrameY = 0;
				}
			default:
				break;
			}


		}
		for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
		{
			switch (dir)
			{
			case NORTH:
			case EAST:
			case WEST:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y][x].terrain = DIRT1;
					_tiles[room.y][x].terrainFrameX = 0;
					_tiles[room.y][x].terrainFrameY = 0;
					_tiles[room.y][x].obj = WALL_GOLD;
					_tiles[room.y][x].objectFrameX = 0;
					_tiles[room.y][x].objectFrameY = 0;
				}
				_tiles[room.y - 1][x].terrain = DIRT1;
				_tiles[room.y - 1][x].terrainFrameX = 0;
				_tiles[room.y - 1][x].terrainFrameY = 0;
				_tiles[room.y - 1][x].obj = WALL_BASIC;
				_tiles[room.y - 1][x].objectFrameX = 0;
				_tiles[room.y - 1][x].objectFrameY = 0;
				break;
			case SOUTH:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y - 1][x].terrain = DIRT1;
					_tiles[room.y - 1][x].terrainFrameX = 0;
					_tiles[room.y - 1][x].terrainFrameY = 0;
					_tiles[room.y - 1][x].obj = WALL_GOLD;
					_tiles[room.y - 1][x].objectFrameX = 0;
					_tiles[room.y - 1][x].objectFrameY = 0;
				}
				else
				{
					_tiles[room.y - 1][x].terrain = DIRT1;
					_tiles[room.y - 1][x].terrainFrameX = 0;
					_tiles[room.y - 1][x].terrainFrameY = 0;
					_tiles[room.y - 1][x].obj = WALL_BASIC;
					_tiles[room.y - 1][x].objectFrameX = 0;
					_tiles[room.y - 1][x].objectFrameY = 0;
				}
			default:
				break;
			}
			switch (dir)
			{
			case SOUTH:
			case EAST:
			case WEST:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y + room.height - 1][x].terrain = DIRT1;
					_tiles[room.y + room.height - 1][x].terrainFrameX = 0;
					_tiles[room.y + room.height - 1][x].terrainFrameY = 0;
					_tiles[room.y + room.height - 1][x].obj = WALL_GOLD;
					_tiles[room.y + room.height - 1][x].objectFrameX = 0;
					_tiles[room.y + room.height - 1][x].objectFrameY = 0;
				}
				_tiles[room.y + room.height][x].terrain = DIRT1;
				_tiles[room.y + room.height][x].terrainFrameX = 0;
				_tiles[room.y + room.height][x].terrainFrameY = 0;
				_tiles[room.y + room.height][x].obj = WALL_BASIC;
				_tiles[room.y + room.height][x].objectFrameX = 0;
				_tiles[room.y + room.height][x].objectFrameY = 0;
				break;
			case NORTH:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y + room.height][x].terrain = DIRT1;
					_tiles[room.y + room.height][x].terrainFrameX = 0;
					_tiles[room.y + room.height][x].terrainFrameY = 0;
					_tiles[room.y + room.height][x].obj = WALL_GOLD;
					_tiles[room.y + room.height][x].objectFrameX = 0;
					_tiles[room.y + room.height][x].objectFrameY = 0;
				}
				else
				{
					_tiles[room.y + room.height][x].terrain = DIRT1;
					_tiles[room.y + room.height][x].terrainFrameX = 0;
					_tiles[room.y + room.height][x].terrainFrameY = 0;
					_tiles[room.y + room.height][x].obj = WALL_BASIC;
					_tiles[room.y + room.height][x].objectFrameX = 0;
					_tiles[room.y + room.height][x].objectFrameY = 0;
				}

				break;
			default:
				break;
			}
		}

		vector<int> shopItem;
		int count = 0;
		while (1)
		{
			bool isItemSame = false;
			if (count == 3) break;
			int item;
			while (1)
			{
				item = RND->getFromIntTo(1, 13);
				if (item != 6) break;
			}
			for (int i = 0; i < shopItem.size(); i++)
			{
				if (shopItem[i] == item)
				{
					isItemSame = true;
					break;
				}
			}
			if (!isItemSame)
			{
				shopItem.push_back(item);
				count++;
			}
		}

		switch (dir)
		{
		case NORTH:
			_tiles[room.y + 3][room.x + 2].terrain = SHOP;
			_tiles[room.y + 3][room.x + 3].obj = SHOPKEEPER;
			_tiles[room.y + 3][room.x + 4].terrain = SHOP;

			_tiles[room.y + 5][room.x + 2].item = (MAP_ITEM)shopItem[0];
			_tiles[room.y + 5][room.x + 3].item = (MAP_ITEM)shopItem[1];
			_tiles[room.y + 5][room.x + 4].item = (MAP_ITEM)shopItem[2];
			break;
		case SOUTH:
			_tiles[room.y + 2][room.x + 2].terrain = SHOP;
			_tiles[room.y + 2][room.x + 3].obj = SHOPKEEPER;
			_tiles[room.y + 2][room.x + 4].terrain = SHOP;

			_tiles[room.y + 4][room.x + 2].item = (MAP_ITEM)shopItem[0];
			_tiles[room.y + 4][room.x + 3].item = (MAP_ITEM)shopItem[1];
			_tiles[room.y + 4][room.x + 4].item = (MAP_ITEM)shopItem[2];
			break;
		case WEST:
			_tiles[room.y + 3][room.x + 2].terrain = SHOP;
			_tiles[room.y + 3][room.x + 3].obj = SHOPKEEPER;
			_tiles[room.y + 3][room.x + 4].terrain = SHOP;

			_tiles[room.y + 5][room.x + 2].item = (MAP_ITEM)shopItem[0];
			_tiles[room.y + 5][room.x + 3].item = (MAP_ITEM)shopItem[1];
			_tiles[room.y + 5][room.x + 4].item = (MAP_ITEM)shopItem[2];
			break;
		case EAST:
			_tiles[room.y + 3][room.x + 1].terrain = SHOP;
			_tiles[room.y + 3][room.x + 2].obj = SHOPKEEPER;
			_tiles[room.y + 3][room.x + 3].terrain = SHOP;

			_tiles[room.y + 5][room.x + 1].item = (MAP_ITEM)shopItem[0];
			_tiles[room.y + 5][room.x + 2].item = (MAP_ITEM)shopItem[1];
			_tiles[room.y + 5][room.x + 3].item = (MAP_ITEM)shopItem[2];
			break;
		case DIRECTIONCOUNT:
			break;
		default:
			break;
		}
	}
	else
	{
		for (int y = room.y - 1; y < room.y + room.height + 1; ++y)
		{
			for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
			{
				if (x == room.x - 1 || y == room.y - 1 || x == room.x + room.width || y == room.y + room.height)
				{
					_tiles[y][x].terrain = DIRT1;
					_tiles[y][x].terrainFrameX = 0;
					_tiles[y][x].terrainFrameY = 0;
					_tiles[y][x].obj = WALL_BASIC;
					_tiles[y][x].objectFrameX = 0;
					_tiles[y][x].objectFrameY = 0;
				}
				else
				{
					_tiles[y][x].terrain = DIRT1;
					_tiles[y][x].terrainFrameX = 0;
					_tiles[y][x].terrainFrameY = 0;
					_tiles[y][x].obj = obj;
					_tiles[y][x].objectFrameX = objectFrameX;
					_tiles[y][x].objectFrameY = objectFrameY;
				}
			}
		}
	}

	return true;
}

bool mapGenerator::createFeature()
{
	for (int i = 0; i < 1000; ++i)
	{
		if (_exits.empty())
			break;
		int r;
		if (_isMakeRoom && _isHaveCorridor)
		{
			r = _exits.size() - 1;
		}
		else
		{
			r = RND->getInt(_exits.size());
		}
		int x, y;
		if (_exits[r].width - 1 == 0)
		{
			x = _exits[r].x;
		}
		else
		{
			x = RND->getFromIntTo(_exits[r].x, _exits[r].x + _exits[r].width - 1);
		}
		if (_exits[r].height - 1 == 0)
		{
			y = _exits[r].y;
		}
		else
		{
			y = RND->getFromIntTo(_exits[r].y, _exits[r].y + _exits[r].height - 1);
		}
		if (_isMakeRoom && _isHaveCorridor)
		{
			if (createFeature(x, y, _corridorDirection))
			{
				_exits.erase(_exits.begin() + r);
				return true;
			}
		}
		else
		{
			for (int j = 0; j < DIRECTIONCOUNT; ++j)
			{
				if (createFeature(x, y, static_cast<ROOM_DIRECTION>(j)))
				{
					_exits.erase(_exits.begin() + r);
					return true;
				}
			}
		}
	}

	return false;
}

bool mapGenerator::createFeature(int x, int y, ROOM_DIRECTION dir, int index)
{
	int dx = 0;
	int dy = 0;

	switch (dir)
	{
	case NORTH:
		dy = 1;
		break;
	case SOUTH:
		dy = -1;
		break;
	case WEST:
		dx = 1;
		break;
	case EAST:
		dx = -1;
		break;
	case DIRECTIONCOUNT:
		break;
	default:
		break;
	}

	if (getTileTerrain(x + dx, y + dy) != DIRT1)
		return false;

	if (_isMakeRoom)
	{
		if (makeRoom(x, y, dir))
		{
			_tiles[y][x].obj = WALL_DOOR;
			_tiles[y][x].objectFrameY = 2;
			if (dir == WEST || dir == EAST)
			{
				_tiles[y][x].objectFrameX = 5;
			}
			else
			{
				_tiles[y][x].objectFrameX = 4;
			}
			return true;
		}
	}
	else
	{

		if (makeCorridor(x, y, dir))
		{
			if (_isHaveCorridor)
			{
				if (getTileTerrain(x + dx, y + dy) == DIRT1)
				{
					_tiles[y][x].obj = OBJ_NONE;
					_tiles[y][x].objectFrameX = NULL;
					_tiles[y][x].objectFrameY = NULL;
				}
				else
				{
					_tiles[y][x].terrain = DIRT2;
					_tiles[y][x].terrainFrameX = 0;
					_tiles[y][x].terrainFrameY = 0;
					_tiles[y][x].obj = OBJ_NONE;
					_tiles[y][x].objectFrameX = NULL;
					_tiles[y][x].objectFrameY = NULL;
				}
				return true;
			}
			else return true;
		}

	}

	return false;
}

TERRAIN mapGenerator::getTileTerrain(int x, int y)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
		return EMPTY;
	return _tiles[y][x].terrain;
}

OBJECT mapGenerator::getTileObject(int x, int y)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
		return OBJ_NONE;
	return _tiles[y][x].obj;
}

void mapGenerator::deleteEmptyTiles()
{
	//맵이 그려진 가장큰 x, y 구하기
	int maxX = 0;
	int	maxY = 0;

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				if (i >= maxY) maxY = i;
				if (j >= maxX) maxX = j;
			}
		}
	}
	//maxX, maxY보다 큰 빈 타일들 삭제
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = _tiles[i].size() - 1; j > maxX; j--)
		{
			_tiles[i].erase(_tiles[i].begin() + j);
		}
	}

	for (int i = _tiles.size() - 1; i > maxY; i--)
	{
		_tiles.erase(_tiles.begin() + i);
	}
}

void mapGenerator::moveMap()
{
	//맵을 화면의 0,0 근처로 옮깁니다
	int minX = _tiles[0].size();
	int	minY = _tiles.size();

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				if (i <= minY) minY = i;
				if (j <= minX) minX = j;
			}
		}
	}
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = minX; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				tagTile temp;
				temp = _tiles[i][j];
				_tiles[i][j] = _tiles[i][j - minX];
				_tiles[i][j - minX] = temp;

				RECT rc;
				rc = _tiles[i][j].rc;
				_tiles[i][j].rc = _tiles[i][j - minX].rc;
				_tiles[i][j - minX].rc = rc;

				RECT rect;
				rect = _tiles[i][j].itemRect;
				_tiles[i][j].itemRect = _tiles[i][j - minX].itemRect;
				_tiles[i][j - minX].itemRect = rect;
			}
		}
	}

	for (int i = minY; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				tagTile temp;
				temp = _tiles[i][j];
				_tiles[i][j] = _tiles[i - minY][j];
				_tiles[i - minY][j] = temp;

				RECT rc;
				rc = _tiles[i][j].rc;
				_tiles[i][j].rc = _tiles[i - minY][j].rc;
				_tiles[i - minY][j].rc = rc;

				RECT rect;
				rect = _tiles[i][j].itemRect;
				_tiles[i][j].itemRect = _tiles[i - minY][j].itemRect;
				_tiles[i - minY][j].itemRect = rect;
			}
		}
	}

	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i].x = _rooms[i].x - minX;
		_rooms[i].y = _rooms[i].y - minY;
	}

	for (int i = 0; i < _corridors.size(); i++)
	{
		_corridors[i].x = _corridors[i].x - minX;
		_corridors[i].y = _corridors[i].y - minY;
	}
}

void mapGenerator::setEndBlock()
{
	_endBlockIndex.clear();

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 1; j < _tiles[i].size() - 1; j++)
		{
			if ((_tiles[i][j - 1].obj != WALL_END && _tiles[i][j - 1].terrain == DIRT1) || (_tiles[i][j + 1].obj != WALL_END && _tiles[i][j + 1].terrain == DIRT1))
			{
				_endBlockIndex.emplace_back(POINT{ j, i });
			}
		}
	}

	for (int i = 1; i < _tiles.size() - 1; i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{

				if ((_tiles[i - 1][j].obj != WALL_END && _tiles[i - 1][j].terrain == DIRT1) || (_tiles[i + 1][j].obj != WALL_END && _tiles[i + 1][j].terrain == DIRT1))
				{
					_endBlockIndex.emplace_back(POINT{ j, i });
				}
			}
		}
	}

	for (int i = 0; i < _endBlockIndex.size(); i++)
	{
		if (_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain != EMPTY) continue;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain = DIRT1;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameY = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].obj = WALL_END;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameY = 3;
	}
}

void mapGenerator::setEndEdge()
{
	_endBlockIndex.clear();
	for (int i = 0; i < _tiles.size() - 1; i++)
	{
		for (int j = 1; j < _tiles[i].size() - 1; j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{
				if (_tiles[i + 1][j].obj == WALL_END)
				{
					if (_tiles[i][j - 1].obj == WALL_END || _tiles[i][j + 1].obj == WALL_END)
					{
						_endBlockIndex.emplace_back(POINT{ j, i });
					}
				}
			}
		}
	}

	for (int i = 1; i < _tiles.size(); i++)
	{
		for (int j = 1; j < _tiles[i].size() - 1; j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{
				if (_tiles[i - 1][j].obj == WALL_END)
				{
					if (_tiles[i][j - 1].obj == WALL_END || _tiles[i][j + 1].obj == WALL_END)
					{
						_endBlockIndex.emplace_back(POINT{ j, i });
					}
				}
			}
		}
	}

	for (int i = 0; i < _endBlockIndex.size(); i++)
	{
		if (_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain != EMPTY) continue;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain = DIRT1;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameY = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].obj = WALL_END;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameY = 3;
	}
}

void mapGenerator::setStone()
{
	int num = RND->getFromIntTo(20, 40);
	int count = 0;
	while (1)
	{
		if (count == num) break;
		int y = RND->getInt(_tiles.size());
		int x = RND->getInt(_tiles[y].size());
		if (_tiles[y][x].obj == WALL_BASIC)
		{
			_tiles[y][x].obj = WALL_STONE;
			_tiles[y][x].objectFrameX = 2;
			_tiles[y][x].objectFrameY = 0;
			count++;
		}
	}
}

void mapGenerator::setBossRoom()
{
	int max = 0;
	for (int i = 0; i < _rooms.size(); i++)
	{
		if (_rooms[i].roomState == ROOM_START)
		{
			_startRoomIndex = i;
		}
	}
	for (int i = 0; i < _rooms.size(); i++)
	{
		if (i == _startRoomIndex) continue;
		if (_rooms[i].roomState != ROOM_SHOP)
		{
			float distance = getDistance(_tiles[_rooms[i].y][_rooms[i].x].rc.left, _tiles[_rooms[i].y][_rooms[i].x].rc.top, _tiles[_rooms[_startRoomIndex].y][_rooms[_startRoomIndex].x].rc.left, _tiles[_rooms[_startRoomIndex].y][_rooms[_startRoomIndex].x].rc.top);
			if (distance > max)
			{
				max = distance;
				_bossRoomIndex = i;
			}
		}
	}
	_rooms[_bossRoomIndex].roomState = ROOM_BOSS;

	int x = RND->getFromIntTo(_rooms[_bossRoomIndex].x, _rooms[_bossRoomIndex].x + _rooms[_bossRoomIndex].width - 1);
	int y = RND->getFromIntTo(_rooms[_bossRoomIndex].y, _rooms[_bossRoomIndex].y + _rooms[_bossRoomIndex].height - 1);
	_tiles[y][x].terrain = STAIR_BOSS;
	_tiles[y][x].terrainFrameX = 0;
	_tiles[y][x].terrainFrameY = 0;
	_tiles[y][x].obj = OBJ_NONE;
	_tiles[y][x].objectFrameX = 0;
	_tiles[y][x].objectFrameY = 0;
	_bossStair.x = x;
	_bossStair.y = y;
}

void mapGenerator::setTorch()
{
	for (int i = 0; i < _rooms.size(); i++)
	{
		if (_rooms[i].roomState == ROOM_SHOP)
		{
			int torchNum = RND->getFromIntTo(7, 9);
			int count = 0;
			while (1)
			{
				if (count == torchNum) break;
				int x = RND->getFromIntTo(_rooms[i].x - 1, _rooms[i].x + _rooms[i].width + 1);
				int y = RND->getFromIntTo(_rooms[i].y - 1, _rooms[i].y + _rooms[i].height + 1);
				if (_tiles[y][x].obj == WALL_GOLD && !_tiles[y][x].isHaveTorch)
				{
					if (!_tiles[y][x - 1].isHaveTorch && !_tiles[y][x + 1].isHaveTorch && !_tiles[y - 1][x].isHaveTorch && !_tiles[y + 1][x].isHaveTorch)
					{
						_tiles[y][x].isHaveTorch = true;
						count++;
					}
				}
			}
		}
		else
		{
			int torchNum = RND->getFromIntTo(2, 4);
			int count = 0;
			while (1)
			{
				if (count == torchNum) break;
				int x = RND->getFromIntTo(_rooms[i].x - 1, _rooms[i].x + _rooms[i].width + 1);
				int y = RND->getFromIntTo(_rooms[i].y - 1, _rooms[i].y + _rooms[i].height + 1);
				if (!_tiles[y][x].isHaveTorch)
				{
					if (_tiles[y][x].obj == WALL_BASIC || _tiles[y][x].obj == WALL_CRACK || _tiles[y][x].obj == WALL_GOLD || _tiles[y][x].obj == WALL_STONE)
					{
						if (!_tiles[y][x - 1].isHaveTorch && !_tiles[y][x + 1].isHaveTorch && !_tiles[y - 1][x].isHaveTorch && !_tiles[y + 1][x].isHaveTorch)
						{
							_tiles[y][x].isHaveTorch = true;
							count++;
						}
					}
				}
			}
		}
	}
	
	
}

void mapGenerator::testObject()
{
	
	/*_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 1].obj = TR_SLOW;
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 1].objectFrameX = 0;
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 1].objectFrameY = 0;

	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 1].obj = TR_FAST;
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 1].objectFrameX = 0;
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 1].objectFrameY = 0;

	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 3].obj = TR_LEFT;
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 3].objectFrameX = 0;
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 3].objectFrameY = 0;

	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 3].obj = TR_RIGHT;
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 3].objectFrameX = 0;
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 3].objectFrameY = 0;
	
*/
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 1].item = MAP_BOMB;
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 1].itemDirection = UP;

	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 2].item = MAP_CHEESE;
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 2].itemDirection = UP;

	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 3].item = MAP_TORCH_PLUS_2;
	_tiles[_rooms[_startRoomIndex].y + 1][_rooms[_startRoomIndex].x + 3].itemDirection = UP;

	_tiles[_rooms[_startRoomIndex].y + 2][_rooms[_startRoomIndex].x + 1].item = MAP_CHAIN_ARMOR;
	_tiles[_rooms[_startRoomIndex].y + 2][_rooms[_startRoomIndex].x + 1].itemDirection = UP;

	_tiles[_rooms[_startRoomIndex].y + 2][_rooms[_startRoomIndex].x + 3].item = MAP_LEATHER_ARMOR;
	_tiles[_rooms[_startRoomIndex].y + 2][_rooms[_startRoomIndex].x + 3].itemDirection = UP;

	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 1].item = MAP_DAGGER;
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 1].itemDirection = UP;
									   
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 2].item = MAP_RAPIER;
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 2].itemDirection = UP;
									   
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 3].item = MAP_TITANUM_SHOVEL;
	_tiles[_rooms[_startRoomIndex].y + 3][_rooms[_startRoomIndex].x + 3].itemDirection = UP;

}

void mapGenerator::settingTraps()
{
	for (int i = 0; i < _rooms.size(); i++)
	{
		if (_rooms[i].roomState == ROOM_START || _rooms[i].roomState == ROOM_SHOP) continue;
		int trapNum = RND->getInt(3);
		int count = 0;
		while (1)
		{
			if (count == trapNum) break;
			int x = RND->getFromIntTo(_rooms[i].x - 1, _rooms[i].x + _rooms[i].width + 1);
			int y = RND->getFromIntTo(_rooms[i].y - 1, _rooms[i].y + _rooms[i].height + 1);
			if (_tiles[y][x].obj == OBJ_NONE && _tiles[y][x].terrain != STAIR_BOSS)
			{
				_tiles[y][x].obj = (OBJECT)RND->getFromIntTo(7, 15);
				count++;
			}
		}
	}
}

void mapGenerator::settingItemBox()
{
	int itemBoxNum = 2;
	int count = 0;
	int roomNum = 0;
	int _redBoxRoomNum = -1;
	while (1)
	{
		if (count == itemBoxNum) break;
		while (1)
		{
			roomNum = RND->getInt(_rooms.size());
			if (_rooms[roomNum].roomState != ROOM_SHOP && _rooms[roomNum].roomState != ROOM_START && roomNum != _redBoxRoomNum)
				break;
		}
		int x = RND->getFromIntTo(_rooms[roomNum].x - 1, _rooms[roomNum].x + _rooms[roomNum].width + 1);
		int y = RND->getFromIntTo(_rooms[roomNum].y - 1, _rooms[roomNum].y + _rooms[roomNum].height + 1);
		if (_tiles[y][x].obj == OBJ_NONE)
		{
			_tiles[y][x].obj = (OBJECT)(17+count);
			if (17 + count == 17)
			{
				_redBoxRoomNum = roomNum;
			}
			count++;
		}
	}
}
