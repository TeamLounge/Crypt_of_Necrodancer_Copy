#include "stdafx.h"
#include "vision.h"

HRESULT vision::init(int tileX, int tileY, int lightNum)
{
	_tileX = tileX;
	_tileY = tileY;
	_startLightNum = lightNum;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			_visionSearch[i][j].lightNum = 0;
			_visionSearch[i][j].tileX = NULL;
			_visionSearch[i][j].tileY = NULL;
		}
	}
	_visionSearch[10][10].tileX = _tileX;
	_visionSearch[10][10].tileY = _tileY;
	_visionSearch[10][10].lightNum = _startLightNum;

	return S_OK;
}

void vision::release()
{
}

void vision::update(int tileX, int tileY)
{
	_tileX = tileX;
	_tileY = tileY;
	_visionSearch[10][10].tileX = _tileX;
	_visionSearch[10][10].tileY = _tileY;
	_visionSearch[10][10].lightNum = _startLightNum;
	setSearchBoundary();
	searchSurround();
	setTileAlpha();
}

void vision::render()
{
	char str[128];
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (_visionSearch[i][j].tileX == NULL || _visionSearch[i][j].tileY == NULL) continue;
			//if (_visionSearch[i][j].lightNum == 0) continue;
			sprintf_s(str, "%d", _visionSearch[i][j].lightNum);
			DrawText(getMemDC(), str, strlen(str), &_map->getRect(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY), DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
}

void vision::searchSurround()
{
	//좌 탐색
	for (int i = _tileX - 1; i >= _tileX - 10; i--)
	{
		if (i < 0) break;
		if (_visionSearch[10][i - (_tileX - 10)].tileX == NULL) continue;
		if (_startLightNum -(_tileX - i) < 0) break;

		_visionSearch[10][i - (_tileX - 10)].lightNum = _startLightNum - (_tileX - i);
		
		//벽이면 탐사 중지
		
		OBJECT obj = _map->getTileObject(_visionSearch[10][i - (_tileX - 10)].tileX, _visionSearch[10][i - (_tileX - 10)].tileY);
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
	for (int i = _tileX + 1; i <= _tileX + 10; i++)
	{
		if (i >= _map->getYSize()) break;
		if (_visionSearch[10][i - (_tileX - 10)].tileX == NULL) continue;
		if (_startLightNum - (i - _tileX) < 0) break;

		_visionSearch[10][i - (_tileX - 10)].lightNum = _startLightNum - (i - _tileX);
		
		//벽이면 탐사 중지
		
		OBJECT obj = _map->getTileObject(_visionSearch[10][i - (_tileX - 10)].tileX, _visionSearch[10][i - (_tileX - 10)].tileY);
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
	for (int i = _tileY - 1; i >= _tileY - 10; i--)
	{
		if (i < 0) break;
		if (_visionSearch[i - (_tileY - 10)][10].tileY == NULL) continue;
		if (_startLightNum - (_tileY - i) < 0) break;
	
		_visionSearch[i - (_tileY - 10)][10].lightNum = _startLightNum - (_tileY - i);
		
		//벽이면 탐사 중지
		OBJECT obj = _map->getTileObject(_visionSearch[i - (_tileY - 10)][10].tileX, _visionSearch[i - (_tileY - 10)][10].tileY);
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
	for (int i = _tileY + 1; i <= _tileY + 10; i++)
	{
		if (i >= _map->getYSize()) break;
		if (_visionSearch[i - (_tileY - 10)][10].tileY == NULL) continue;
		if (_startLightNum - (i - _tileY) < 0) break;

		_visionSearch[i - (_tileY - 10)][10].lightNum = _startLightNum - (i - _tileY);
		
		
		
		//벽이면 탐사 중지
		OBJECT obj = _map->getTileObject(_visionSearch[i - (_tileY - 10)][10].tileX, _visionSearch[i - (_tileY - 10)][10].tileY);
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
	for (int i = _tileY - 1; i >= _tileY - 10; i--)
	{
		if (i < 0) break;
		for (int j = _tileX - 1; j >= _tileX - 10; j--)
		{
			if (j < 0) break;
			if (_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].tileX == NULL) continue;
			if ((_visionSearch[i - (_tileY - 10) + 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) + 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].lightNum = (_visionSearch[i - (_tileY - 10) + 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) + 1].lightNum) / 2 - 1;
		}
	}
	//플레이어 보다 x가 크고 y가 작은 곳
	for (int i = _tileY - 1; i >= _tileY - 10; i--)
	{
		if (i < 0) break;
		for (int j = _tileX + 1; j <= _tileX + 10; j++)
		{
			if (j >= _map->getXSize()) break;
			if (_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].tileX == NULL) continue;
			if ((_visionSearch[i - (_tileY - 10) + 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) + 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].lightNum = (_visionSearch[i - (_tileY - 10) + 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) - 1].lightNum) / 2 - 1;
		}
	}

	//플레이어보다 x는 작고 y는 큰 곳
	for (int i = _tileY + 1; i <= _tileY + 10; i++)
	{
		if (i >= _map->getYSize()) break;
		for (int j = _tileX - 1; j >= _tileX - 10; j--)
		{
			if (j < 0) break;
			if (_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].tileX == NULL) continue;
			if ((_visionSearch[i - (_tileY - 10) - 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) + 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].lightNum = (_visionSearch[i - (_tileY - 10) - 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) + 1].lightNum) / 2 - 1;
		}
	}

	//플레이어보다 x, y 모두 큰 곳
	for (int i = _tileY + 1; i <= _tileY + 10; i++)
	{
		if (i >= _map->getYSize()) break;
		for (int j = _tileX + 1; j <= _tileX + 10; j++)
		{
			if (j >= _map->getXSize()) break;
			if (_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].tileX == NULL) continue;
			if ((_visionSearch[i - (_tileY - 10) - 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) - 1].lightNum) / 2 - 1 < 0) continue;
			_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].lightNum = (_visionSearch[i - (_tileY - 10) - 1][j - (_tileX - 10)].lightNum + _visionSearch[i - (_tileY - 10)][j - (_tileX - 10) - 1].lightNum) / 2 - 1;
		}
	}

	//이미 지나왔던 곳인지 확인
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{

		}
	}
}

void vision::setTileAlpha()
{
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY))
			{
				_map->setAlpha(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY, 20);
			}
		}
	}
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (_visionSearch[i][j].tileY == NULL || _visionSearch[i][j].tileX == NULL) continue;
			if (_visionSearch[i][j].lightNum <= 0 && !_map->getIsSeen(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY))
			{
				_map->setAlpha(_visionSearch[i][j].tileX, _visionSearch[i][j].tileY, 0);
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
	for (int i = _tileY - 10; i <= _tileY + 10; i++)
	{
		if (i < 0) continue;
		if (i >= _map->getYSize()) break;

		for (int j = _tileX - 10; j <= _tileX + 10; j++)
		{
			if (j < 0) continue;
			if (j >= _map->getXSize()) break;
			if (j == _tileX && i == _tileY) continue;

			_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].tileX = j;
			_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].tileY = i;
			_visionSearch[i - (_tileY - 10)][j - (_tileX - 10)].lightNum = 0;
		}
	}
}
