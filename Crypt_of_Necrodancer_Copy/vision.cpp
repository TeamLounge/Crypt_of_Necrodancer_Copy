#include "stdafx.h"
#include "vision.h"

HRESULT vision::init(int tileX, int tileY, int lightNum)
{
	_tileX = tileX;
	_tileY = tileY;
	_startLightNum = lightNum;
	for (int i = 0; i < VISIONY; i++)
	{
		for (int j = 0; j < VISIONX; j++)
		{
			_visionSearch[i][j].lightNum = 0;
			_visionSearch[i][j].tileX = -1;
			_visionSearch[i][j].tileY = -1;
		}
	}
	_visionSearch[VISIONY / 2][VISIONX / 2].tileX = _tileX;
	_visionSearch[VISIONY / 2][VISIONX / 2].tileY = _tileY;
	_visionSearch[VISIONY / 2][VISIONX / 2].lightNum = _startLightNum;

	return S_OK;
}

void vision::release()
{
}

void vision::update(int tileX, int tileY)
{
	_tileX = tileX;
	_tileY = tileY;
	setSearchBoundary();
	searchSurround();
	//findTorch();
	setTileAlpha();
	drawMiniMap();
}

void vision::render()
{
	char str[128];
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < VISIONY; i++)
		{
			for (int j = 0; j < VISIONX; j++)
			{
				if (_visionSearch[i][j].tileX == - 1 || _visionSearch[i][j].tileY == - 1) continue;
				//if (_visionSearch[i][j].lightNum == 0) continue;
				sprintf_s(str, "%d", _visionSearch[i][j].lightNum);
				DrawText(getMemDC(), str, strlen(str), &_map->getRect(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY), DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			}
		}
	}
}

void vision::searchSurround()
{
	//좌 탐색
	for (int i = _tileX - 1; i >= _tileX - VISIONX / 2; i--)
	{
		if (i < 0) break;
		if (_visionSearch[VISIONY / 2][i - (VISIONX / 2)].tileX == - 1) continue;
		if (_startLightNum -(_tileX - i) <= 0) continue;

		_visionSearch[VISIONX / 2][i - (_tileX - VISIONX / 2)].lightNum = _startLightNum - (_tileX - i);
		
		//벽이면 탐사 중지
		
		OBJECT obj = _map->getTileObject(_visionSearch[VISIONX / 2][i - (_tileX - VISIONX / 2)].tileX, _visionSearch[VISIONX / 2][i - (_tileX - VISIONX / 2)].tileY);
		if (obj == WALL_BASIC
			|| obj == WALL_CRACK
			|| obj == WALL_DOOR
			|| obj == WALL_END
			|| obj == WALL_GOLD
			|| obj == WALL_STONE)
		{
			break;
		}
		
	}

	//우 탐색
	for (int i = _tileX + 1; i <= _tileX + (VISIONX - 1) / 2; i++)
	{
		if (i >= _map->getXSize()) continue;
		if (_visionSearch[VISIONY / 2][i - (_tileX - VISIONX / 2)].tileX == - 1) continue;
		if (_startLightNum - (i - _tileX) < 0) continue;

		_visionSearch[10][i - (_tileX - 10)].lightNum = _startLightNum - (i - _tileX);
		
		//벽이면 탐사 중지
		
		OBJECT obj = _map->getTileObject(_visionSearch[VISIONY / 2][i - (_tileX - VISIONX / 2)].tileX, _visionSearch[VISIONY / 2][i - (_tileX - VISIONX / 2)].tileY);
		if (obj == WALL_BASIC
			|| obj == WALL_CRACK
			|| obj == WALL_DOOR
			|| obj == WALL_END
			|| obj == WALL_GOLD
			|| obj == WALL_STONE)
		{
			break;
		}
		
	}

	//상 탐색
	for (int i = _tileY - 1; i >= _tileY - VISIONY / 2; i--)
	{
		if (i < 0) continue;
		if (_visionSearch[i - (_tileY - VISIONY/2)][VISIONX / 2].tileY == - 1) continue;
		if (_startLightNum - (_tileY - i) < 0) continue;
	
		_visionSearch[i - (_tileY - VISIONY / 2)][VISIONX / 2].lightNum = _startLightNum - (_tileY - i);
		
		//벽이면 탐사 중지
		OBJECT obj = _map->getTileObject(_visionSearch[i - (_tileY - VISIONY / 2)][VISIONX / 2].tileX, _visionSearch[i - (_tileY - VISIONY / 2)][VISIONX / 2].tileY);
		if (obj == WALL_BASIC
			|| obj == WALL_CRACK
			|| obj == WALL_DOOR
			|| obj == WALL_END
			|| obj == WALL_GOLD
			|| obj == WALL_STONE)
		{
			break;
		}
		
		//_visionSearch[_tileY][i - (_tileX - 10)].lightNum;
	}

	//하 탐색
	for (int i = _tileY + 1; i <= _tileY + VISIONY / 2; i++)
	{
		if (i >= _map->getYSize()) continue;
		if (_visionSearch[i - (_tileY - VISIONY / 2)][VISIONX / 2].tileY == - 1) continue;
		if (_startLightNum - (i - _tileY) < 0) continue;

		_visionSearch[i - (_tileY - VISIONY / 2)][VISIONX / 2].lightNum = _startLightNum - (i - _tileY);
		
		//벽이면 탐사 중지
		OBJECT obj = _map->getTileObject(_visionSearch[i - (_tileY - VISIONY / 2)][VISIONX / 2].tileX, _visionSearch[i - (_tileY - VISIONY / 2)][VISIONX / 2].tileY);
		if (obj == WALL_BASIC
			|| obj == WALL_CRACK
			|| obj == WALL_DOOR
			|| obj == WALL_END
			|| obj == WALL_GOLD
			|| obj == WALL_STONE)
		{
			break;
		}
		
		
	}

	//4방향 탐색한 것으로 주변 채우기
	//플레이어보다 x, y 둘 다 작은 곳
	for (int i = _tileY - 1; i >= _tileY - VISIONY / 2; i--)
	{
		if (i < 0) break;
		for (int j = _tileX - 1; j >= _tileX - VISIONX / 2; j--)
		{
			if (j < 0) continue;
			if (_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].tileX == - 1) continue;
			if ((_visionSearch[i - (_tileY - VISIONY / 2) + 1][j - (_tileX - VISIONX / 2)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - VISIONX / 2) + 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].lightNum =
				(_visionSearch[i - (_tileY - VISIONY / 2) + 1][j - (_tileX - VISIONX / 2)].lightNum +
					_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2) + 1].lightNum) / 2 - 1;
		}
	}
	//플레이어 보다 x가 크고 y가 작은 곳
	for (int i = _tileY - 1; i >= _tileY - VISIONY / 2; i--)
	{
		if (i < 0) break;
		for (int j = _tileX + 1; j <= _tileX + VISIONX / 2; j++)
		{
			if (j >= _map->getXSize()) continue;
			if (_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].tileX == - 1) continue;
			if ((_visionSearch[i - (_tileY - VISIONY / 2) + 1][j - (_tileX - VISIONX / 2)].lightNum + _visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2) + 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].lightNum =
				(_visionSearch[i - (_tileY - VISIONY / 2) + 1][j - (_tileX - VISIONX / 2)].lightNum +
					_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2) - 1].lightNum) / 2 - 1;
		}
	}

	//플레이어보다 x는 작고 y는 큰 곳
	for (int i = _tileY + 1; i <= _tileY + VISIONY / 2; i++)
	{
		if (i >= _map->getYSize()) continue;
		for (int j = _tileX - 1; j >= _tileX - VISIONX / 2; j--)
		{
			if (j < 0) break;
			if (_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].tileX == -1) continue;
			if ((_visionSearch[i - (_tileY - VISIONY / 2) - 1][j - (_tileX - VISIONX / 2)].lightNum + _visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2) + 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].lightNum = (_visionSearch[i - (_tileY - VISIONY / 2) - 1][j - (_tileX - VISIONX / 2)].lightNum + _visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2) + 1].lightNum) / 2 - 1;
		}
	}

	//플레이어보다 x, y 모두 큰 곳
	for (int i = _tileY + 1; i <= _tileY + VISIONY / 2; i++)
	{
		if (i >= _map->getYSize()) continue;
		for (int j = _tileX + 1; j <= _tileX + VISIONX / 2; j++)
		{
			if (j >= _map->getXSize()) continue;
			if (_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].tileX == -1) continue;
			if ((_visionSearch[i - (_tileY - VISIONY / 2) - 1][j - (_tileX - VISIONX / 2)].lightNum + _visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2) - 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].lightNum = (_visionSearch[i - (_tileY - VISIONY / 2) - 1][j - (_tileX - VISIONX / 2)].lightNum + _visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2) - 1].lightNum) / 2 - 1;
		}
	}
}

void vision::setTileAlpha()
{
	for (int i = 0; i < VISIONY; i++)
	{
		for (int j = 0; j < VISIONX; j++)
		{
			if (_visionSearch[i][j].tileY == -1 || _visionSearch[i][j].tileX == -1) continue;
			if (_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY))
			{
				_map->setAlpha(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY, 100);
			}
		}
	}
	for (int i = 0; i < VISIONY; i++)
	{
		for (int j = 0; j < VISIONX; j++)
		{
			if (_visionSearch[i][j].tileY == -1 || _visionSearch[i][j].tileX == -1) continue;
			
			if (_visionSearch[i][j].lightNum <= 0)
			{
				continue;
			}
			
			if (_visionSearch[i][j].lightNum > 5) _visionSearch[i][j].lightNum = 5;
			_map->setAlpha(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY, 130 + (_visionSearch[i][j].lightNum * 25));
			_map->setIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY, true);
		}
	}
}

void vision::setSearchBoundary()
{
	for (int i = 0; i < VISIONY; i++)
	{
		for (int j = 0; j < VISIONX; j++)
		{
			_visionSearch[i][j].lightNum = 0;
			_visionSearch[i][j].tileX = - 1;
			_visionSearch[i][j].tileY = - 1;
		}
	}

	for (int i = _tileY - (VISIONY / 2); i <= _tileY + VISIONY/2; i++)
	{
		if (i < 0) continue;
		if (i >= _map->getYSize()) break;

		for (int j = _tileX - (VISIONX / 2); j <= _tileX + VISIONX / 2; j++)
		{
			if (j < 0) continue;
			if (j >= _map->getXSize()) break;
			//if (j == _tileX && i == _tileY) continue;

			_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].tileX = j;
			_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].tileY = i;
			_visionSearch[i - (_tileY - VISIONY / 2)][j - (_tileX - VISIONX / 2)].lightNum = 0;
		}
	}

	_visionSearch[VISIONY / 2][VISIONX / 2].tileX = _tileX;
	_visionSearch[VISIONY / 2][VISIONX / 2].tileY = _tileY;
	_visionSearch[VISIONY / 2][VISIONX / 2].lightNum = _startLightNum;
}

void vision::findTorch()
{
	//좌 탐색
	for (int i = 9; i >= 0; i--)
	{
		if (_visionSearch[VISIONY/2][i].tileX == -1) continue;
		

		//벽이면 탐사 중지
		OBJECT obj = _map->getTileObject(_visionSearch[VISIONY / 2][i - (_tileX - VISIONX/2)].tileX, _visionSearch[VISIONY / 2][i - (_tileX - VISIONX / 2)].tileY);
		if (obj == WALL_BASIC
			|| obj == WALL_CRACK
			|| obj == WALL_DOOR
			|| obj == WALL_END
			|| obj == WALL_GOLD
			|| obj == WALL_STONE)
		{
			break;
		}

	}
}
/*
void vision::addTorchLight(int x, int y)
{
	int lightNum = 3;
	_visionSearch[y][x].lightNum = 3;

	//좌 탐색
	for (int i = x - 1; i >= x - 5; i--)
	{
		if (i < 0) break;
		if (_visionSearch[y][i].tileX == - 1) continue;
		if (lightNum - (x - i) < 0) break;
		if (!_map->getIsSeen(_visionSearch[y][i].tileX, _visionSearch[y][i].tileY)) break;
		_visionSearch[y][i].lightNum = (_visionSearch[y][i].lightNum + lightNum - (x - i)) /2 + 1;
	}
	//우 탐색
	for (int i = x + 1; i <= x + 5; i++)
	{
		if (i >= _map->getXSize()) break;
		if (_visionSearch[y][i].tileX == - 1) continue;
		if (lightNum - (i - x) < 0) break;
		if (!_map->getIsSeen(_visionSearch[y][i].tileX, _visionSearch[y][i].tileY)) break;

		_visionSearch[y][i].lightNum = (_visionSearch[y][i].lightNum + (lightNum - (i - x))) /2 + 1;
	}
	//상 탐색
	for (int i = y - 1; i >= y - 5; i--)
	{
		if (i < 0) break;
		if (_visionSearch[i][x].tileY == - 1) continue;
		if (lightNum - (y - i) < 0) break;
		if (!_map->getIsSeen(_visionSearch[i][x].tileX, _visionSearch[i][x].tileY)) break;

		_visionSearch[i][x].lightNum = (_visionSearch[i][x].lightNum + (lightNum - (y - i))) / 2 + 1;
	}
	//하 탐색
	for (int i = y + 1; i <= y + 5; i++)
	{
		if (i >= _map->getYSize()) break;
		if (_visionSearch[i][x].tileY == - 1) continue;
		if (lightNum - (i - y) < 0) break;
		if (!_map->getIsSeen(_visionSearch[i][x].tileX, _visionSearch[i][x].tileY)) break;
		
		_visionSearch[i][x].lightNum = (_visionSearch[i][x].lightNum  + lightNum - (i - y)) /2;
	}

	for (int i = y - 1; i >= y - 5; i--)
	{
		if (i >= _map->getYSize()) break;
		for (int j = x - 1; j >= x - 3; j--)
		{
			if (j < 0) break;
			if (_visionSearch[i][j].tileY == - 1 ) continue;
			if ((_visionSearch[i + 1][j].lightNum + _visionSearch[i][j + 1].lightNum) / 2 - 1 < 0) continue;
			if (!_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY)) break;

			_visionSearch[i][j].lightNum += (_visionSearch[i + 1][j].lightNum + _visionSearch[i][j + 1].lightNum) / 2 - 1;
		}

		for (int j = x + 1; j <= x + 5; j++)
		{
			if (j < 0) break;
			if (_visionSearch[i][j].tileY == - 1) continue;
			if ((_visionSearch[i + 1][j].lightNum + _visionSearch[i][j - 1].lightNum) / 2 - 1 < 0) continue;
			if (!_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY)) break;

			_visionSearch[i][j].lightNum += (_visionSearch[i + 1][j].lightNum + _visionSearch[i][j - 1].lightNum) / 2 - 1;
		}
	}

	for (int i = y + 1; i <= y + 5; i++)
	{
		if (i >= _map->getYSize()) break;
		for (int j = x - 1; j >= x - 3; j--)
		{
			if (j < 0) break;
			if (_visionSearch[i][j].tileY == - 1) continue;
			if ((_visionSearch[i - 1][j].lightNum + _visionSearch[i][j + 1].lightNum) / 2 - 1 < 0) continue;
			if (!_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY)) break;

			_visionSearch[i][j].lightNum += (_visionSearch[i - 1][j].lightNum + _visionSearch[i][j + 1].lightNum) / 2 - 1;
		}

		for (int j = x + 1; j <= x + 5; j++)
		{
			if (j < 0) break;
			if (_visionSearch[i][j].tileY == - 1) continue;
			if ((_visionSearch[i - 1][j].lightNum + _visionSearch[i][j - 1].lightNum) / 2 - 1 < 0) continue;
			if (!_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY)) break;

			_visionSearch[i][j].lightNum += (_visionSearch[i - 1][j].lightNum + _visionSearch[i][j - 1].lightNum) / 2 - 1;
		}
	}
}
*/
void vision::drawMiniMap()
{
	for (int i = 0; i < VISIONY; i++)
	{
		for (int j = 0; j < VISIONX; j++)
		{
			if (_visionSearch[i][j].tileY == -1 || _visionSearch[i][j].tileX == -1) continue;
			if (_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY))
			{
				MINIMAP->drawMiniMap(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY, 
					_map->getTileTerrain(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY), 
					_map->getTileObject(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY),
					_map->getTileItem(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY), _map->getIsEnemy(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY));
			}
		}
	}
	MINIMAP->drawPlayer(_tileX, _tileY);
}
