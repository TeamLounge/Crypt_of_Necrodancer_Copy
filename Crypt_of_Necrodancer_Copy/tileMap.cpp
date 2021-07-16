#include "stdafx.h"
#include "tileMap.h"

HRESULT tileMap::init()
{
	_tileX = 20;
	_tileY = 20;
	_isEvenLight = false;
	_worldTime = TIMEMANAGER->getWorldTime();
	_elapsedSec = 0;
	_tileBuffer = new image;
	_tileBuffer->init(BACKGROUNDX, BACKGROUNDY);
	setup();
	CAMERAMANAGER->setCamera(0, 0);
	return S_OK;
}

HRESULT tileMap::init(int tileX, int tileY)
{
	_tileX = tileX;
	_tileY = tileY;
	_isEvenLight = false;
	_worldTime = TIMEMANAGER->getWorldTime();
	_tileBuffer = new image;
	_tileBuffer->init(BACKGROUNDX, BACKGROUNDY);
	setup();
	CAMERAMANAGER->setCamera(0, 0);
	return S_OK;
}

void tileMap::release()
{
}

void tileMap::update()
{
	deleteObject();
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - 5);
		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
		}
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_tileX * TILESIZE >= CAMERAX)
		{
			CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + 5);
		}
	
		if (CAMERAMANAGER->getCameraRIGHT() >= _tileX * TILESIZE && _tileX * TILESIZE >= CAMERAX)
		{
			CAMERAMANAGER->setCameraX(_tileX * TILESIZE - CAMERAX);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - 5);
		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_tileY * TILESIZE >= CAMERAY)
		{
			CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
		}
		if (CAMERAMANAGER->getCameraBOTTOM() >= _tileY * TILESIZE + MARGIN && _tileY * TILESIZE + MARGIN >= CAMERAY)
		{
			CAMERAMANAGER->setCameraY(_tileY * TILESIZE + MARGIN - CAMERAY);
		}
	}
	
	if (TIMEMANAGER->getWorldTime() - _worldTime >= 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
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
	if (_elapsedSec >= 0.1f)
	{
		_elapsedSec -= 0.1f;
		if (IMAGEMANAGER->findImage("wall_torch")->getFrameX() >= IMAGEMANAGER->findImage("wall_torch")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("wall_torch")->setFrameX(0);
		}
		else
		{
			IMAGEMANAGER->findImage("wall_torch")->setFrameX(IMAGEMANAGER->findImage("wall_torch")->getFrameX() + 1);
		}
	}
}

void tileMap::render()
{
	PatBlt(_tileBuffer->getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);

	for (int i = 0; i <_tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			switch (_tiles[i][j].terrain)
			{
			case DIRT1:
				IMAGEMANAGER->frameRender("dirt1_tile", _tileBuffer->getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case DIRT2:
				IMAGEMANAGER->frameRender("dirt2_tile", _tileBuffer->getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case BOSS:
				IMAGEMANAGER->frameRender("boss_tile", _tileBuffer->getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case WATER:
				IMAGEMANAGER->frameRender("water_tile", _tileBuffer->getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case SHOP:
				IMAGEMANAGER->frameRender("shop_tile", _tileBuffer->getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 0);
				break;
			}

			switch (_tiles[i][j].obj)
			{
			case OBJ_NONE :
				break;
			case WALL_BASIC:
				IMAGEMANAGER->frameRender("walls1", _tileBuffer->getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case WALL_GOLD:
			case WALL_STONE:
			case WALL_CRACK:
			case WALL_DOOR:
			case WALL_END:
				IMAGEMANAGER->frameRender("walls2", _tileBuffer->getMemDC(), _tiles[i][j].rc.left, 
					_tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_BOMB:
				IMAGEMANAGER->frameRender("bomb_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_UP:
				IMAGEMANAGER->frameRender("up_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_DOWN:
				IMAGEMANAGER->frameRender("down_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_LEFT:
				IMAGEMANAGER->frameRender("left_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_RIGHT:
				IMAGEMANAGER->frameRender("right_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_FAST:
				IMAGEMANAGER->frameRender("fast_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_SLOW:
				IMAGEMANAGER->frameRender("slow_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_JUMP:
				IMAGEMANAGER->frameRender("jump_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_DOOR:
				IMAGEMANAGER->frameRender("door_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_SPIKE:
				IMAGEMANAGER->frameRender("spike_trap", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case RED_ITEM_BOX:
				IMAGEMANAGER->frameRender("red_item_box", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameHeight() / 2, 0, 0);
				break;
			case BLACK_ITEM_BOX:
				IMAGEMANAGER->frameRender("black_item_box", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameHeight() / 2, 0, 0);
				break;
			case BOX:
				IMAGEMANAGER->frameRender("box", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("box")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("box")->getFrameHeight() / 2, 0, 0);
				break;
			case BARREL:
				IMAGEMANAGER->frameRender("barrel", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameHeight() / 2, 0, 0);
				break;
			}
			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				Rectangle(_tileBuffer->getMemDC(), _tiles[i][j].rc);
			}

			if (_tiles[i][j].isHaveTorch)
			{
				IMAGEMANAGER->frameRender("wall_torch", _tileBuffer->getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("wall_torch")->getFrameWidth() / 2 - 5,
					_tiles[i][j].rc.top - (TILESIZE * 5) / 8 - TILESIZE/3);
			}
		}

		
	}

	CAMERAMANAGER->render(_tileBuffer, getMemDC());
}

void tileMap::setup()
{
	//타일 영역
	for (int i = 0; i < _tileY; ++i)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < _tileX; ++j)
		{
			tagTile tile;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE + MARGIN, TILESIZE, TILESIZE);
			tile.terrain = DIRT1;
			tile.obj = OBJ_NONE;
			tile.terrainFrameX = 0;
			tile.terrainFrameY = 0;
			if (i == 0 || i == _tileX - 1 || j == 0 || j == _tileY-1)
			{
				tile.obj = WALL_END;
				tile.objectFrameX = 0;
				tile.objectFrameY = 3;
			}
			tile.isHaveTorch = false;
			vTile.push_back(tile);
		}
		_tiles.push_back(vTile);
	}
}

void tileMap::resizeTile(int tileX, int tileY)
{
	if (_tileX > tileX)
	{
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = _tileX - 1; j >= tileX; j--)
			{
				_tiles[i].erase(_tiles[i].begin() + j);
			}
		}
		_tileX = tileX;
	}
	else
	{
		for (int i = 0; i < _tileY; i++)
		{
			if (i == 0) continue;
			_tiles[i][_tileX - 1].obj = OBJ_NONE;
			_tiles[i][_tileX - 1].objectFrameX = NULL;
			_tiles[i][_tileX - 1].objectFrameY = NULL;
		}
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = _tileX; j < tileX; j++)
			{
				tagTile tile;
				tile.rc = RectMake(j * TILESIZE, i * TILESIZE + MARGIN, TILESIZE, TILESIZE);
				tile.terrain = DIRT1;
				tile.terrainFrameX = 0;
				tile.terrainFrameY = 0;
				if (j == tileX - 1)
				{
					tile.obj = WALL_END;
					tile.objectFrameX = 0;
					tile.objectFrameY = 3;
				}
				else
				{
					tile.obj = OBJ_NONE;
					tile.objectFrameX = NULL;
					tile.objectFrameY = NULL;
				}
				tile.isHaveTorch = false;
				_tiles[i].push_back(tile);
			}
		}
		_tileX = tileX;
	}

	
	if (_tileY > tileY)
	{
		for (int i = _tileY - 1; i >= tileY ; i--)
		{
			_tiles[i].clear();
			_tiles.erase(_tiles.begin() + i);
		}
		_tileY = tileY;
	}
	else
	{
		for (int j = 0; j < _tileX - 1; j++)
		{
			if (j == 0) continue;
			_tiles[_tileY - 1][j].obj = OBJ_NONE;
			_tiles[_tileY - 1][j].objectFrameX = NULL;
			_tiles[_tileY - 1][j].objectFrameY = NULL;
		}
		for (int i = _tileY; i < tileY; i++)
		{
			vector<tagTile> vTile;
			for(int j = 0; j < _tileX; j++)
			{
				tagTile tile;
				tile.rc = RectMake(j * TILESIZE, i * TILESIZE + MARGIN, TILESIZE, TILESIZE);
				tile.terrain = DIRT1;
				tile.terrainFrameX = 0;
				tile.terrainFrameY = 0;
				if (i == tileY - 1)
				{
					tile.obj = WALL_END;
					tile.objectFrameX = 0;
					tile.objectFrameY = 3;
				}
				else
				{
					tile.obj = OBJ_NONE;
					tile.objectFrameX = NULL;
					tile.objectFrameY = NULL;
				}
				tile.isHaveTorch = false;
				vTile.push_back(tile);
			}
			_tiles.push_back(vTile);
		}
		_tileY = tileY;
	}

	for (int i = 0; i < _tileX; i++)
	{
		_tiles[_tileY - 1][i].obj = WALL_END;
		_tiles[_tileY - 1][i].objectFrameX = 0;
		_tiles[_tileY - 1][i].objectFrameY = 3;
		if (_tiles[0][i].obj != WALL_END)
		{
			_tiles[0][i].obj = WALL_END;
			_tiles[0][i].objectFrameX = 0;
			_tiles[0][i].objectFrameY = 3;
		}
	}

	for (int i = 0; i < _tileY; i++)
	{
		_tiles[i][_tileX - 1].obj = WALL_END;
		_tiles[i][_tileX - 1].objectFrameX = 0;
		_tiles[i][_tileX - 1].objectFrameY = 3;
		if (_tiles[i][0].obj != WALL_END)
		{
			_tiles[i][0].obj = WALL_END;
			_tiles[i][0].objectFrameX = 0;
			_tiles[i][0].objectFrameY = 3;
		}
	}
}

void tileMap::saveTile()
{
	//저장이요
	HANDLE file;
	DWORD write;
	_savedX = _tileX;
	_savedY = _tileY;
	tagTile *tile = new tagTile[_savedX * _savedY];
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			tile[i * _savedX + j] = _tiles[i][j];
		}
	}

	file = CreateFile("bossMap.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tile, sizeof(tagTile) * _savedX * _savedY, &write, NULL);

	CloseHandle(file);
	delete[] tile;
}

void tileMap::loadTile()
{
	//로드요
	HANDLE file;
	DWORD read;
	tagTile *tile = new tagTile[_savedX * _savedY];
    file = CreateFile("bossMap.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, tile, sizeof(tagTile) * _savedX * _savedY, &read, NULL);

	_tiles.clear();
	for (int i = 0; i < _savedY; i++)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < _savedX; j++)
		{
			vTile.push_back(tile[i * _savedX + j]);
		}
		_tiles.push_back(vTile);
	}

	_tileX = _savedX;
	_tileY = _savedY;

	CloseHandle(file);
	delete[] tile;
}

void tileMap::drawTerrain(TERRAIN terrain)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				POINT mouse;
				mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
				mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
				if (PtInRect(&_tiles[i][j].rc, mouse))
				{
					_tiles[i][j].terrain = terrain;
					break;
				}
			}
		}
	}
	
}

void tileMap::drawWall(int frameX, int frameY, CATEGORY category)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				POINT mouse;
				mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
				mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
				
				if (PtInRect(&_tiles[i][j].rc, mouse))
				{
					if (_tiles[i][j].terrain != EMPTY)
					{
						_tiles[i][j].objectFrameX = frameX;
						_tiles[i][j].objectFrameY = frameY;

						_tiles[i][j].obj = wallSelect(frameX, frameY, category);
						break;
					}
					break;
				}
			}
		}
	}
	
}

void tileMap::drawObject(OBJECT obj)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				POINT mouse;
				mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
				mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
				if (PtInRect(&_tiles[i][j].rc, mouse))
				{
					if (_tiles[i][j].terrain != EMPTY)
					{
						_tiles[i][j].obj = obj;
						_tiles[i][j].objectFrameX = 0;
						_tiles[i][j].objectFrameY = 0;
						break;
					}
					break;
				}
			}
		}
	}
}

void tileMap::drawTorch()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				POINT mouse;
				mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
				mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
				if (PtInRect(&_tiles[i][j].rc, mouse))
				{
					if (_tiles[i][j].obj == WALL_BASIC || _tiles[i][j].obj == WALL_CRACK || _tiles[i][j].obj == WALL_GOLD || _tiles[i][j].obj == WALL_STONE)
					{
						_tiles[i][j].isHaveTorch = true;
						break;
					}
					break;
				}
			}
		}
	}
}

void tileMap::deleteObject()
{
	if (KEYMANAGER->isStayKeyDown('R') && KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				POINT mouse;
				mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
				mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
				if (PtInRect(&_tiles[i][j].rc, mouse))
				{
					if (_tiles[i][j].terrain != EMPTY)
					{
						_tiles[i][j].terrain = EMPTY;
						_tiles[i][j].terrainFrameX = NULL;
						_tiles[i][j].terrainFrameY = NULL;
						_tiles[i][j].obj = OBJ_NONE;
						_tiles[i][j].objectFrameX = NULL;
						_tiles[i][j].objectFrameY = NULL;
						_tiles[i][j].isHaveTorch = false;
						break;
					}
					break;
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				POINT mouse;
				mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
				mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
				if (PtInRect(&_tiles[i][j].rc, mouse))
				{
					if (_tiles[i][j].obj != OBJ_NONE)
					{
						_tiles[i][j].objectFrameX = NULL;
						_tiles[i][j].objectFrameY = NULL;
						_tiles[i][j].obj = OBJ_NONE;
						_tiles[i][j].isHaveTorch = false;
						break;
					}
					break;
				}
			}
		}
	}
	
	
}

OBJECT tileMap::wallSelect(int frameX, int frameY, CATEGORY category)
{
	switch (category)
	{
	case CATEGORY_WALL1:
		if (frameY >= 0 && frameY <= 4)
		{
			return WALL_BASIC;
		}
		break;
	case CATEGORY_WALL2:
		if (frameY == 0)
		{
			if (frameX <= 1)
			{
				return WALL_GOLD;
			}
			else if (frameX >= 2 && frameX <= 5)
			{
				return WALL_STONE;
			}
		}
		else if ((frameY == 1 && frameX <= 6) || (frameY == 2 && frameX <= 3))
		{
			return WALL_CRACK;
		}
		else if (frameY == 2 && (frameX == 4 || frameX == 5))
		{
			return WALL_DOOR;
		}
		else if (frameY == 3 && frameX <= 5)
		{
			return WALL_END;
		}
		break;
	}
	return OBJ_NONE;
}

