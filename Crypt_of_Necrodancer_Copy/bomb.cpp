#include "stdafx.h"
#include "bomb.h"

HRESULT bomb::init()
{
	_worldTime = TIMEMANAGER->getWorldTime();
	_elapsedSec = 0;

	UIMANAGER->addUI("bomb", "bomb", 0, 0);
	return S_OK;
}

void bomb::release()
{
}

void bomb::update()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime >= 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		if (!_vBomb.empty())
		{
			for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); _viBomb++)
			{
				if (!_viBomb->isExplode)
				{
					if (_viBomb->currentFrameX >= IMAGEMANAGER->findImage(_viBomb->imageName)->getMaxFrameX())
					{
						_viBomb->imageName = "bomb_explosion";
						_viBomb->currentFrameX = 0;
						_viBomb->rc = RectMakeCenter(_viBomb->x, _viBomb->y, TILESIZE * 3, TILESIZE * 3);
						_viBomb->isExplode = true;
					}
					else
					{
						_viBomb->currentFrameX++;
					}
				}
			}
		}
	}

	_elapsedSec += TIMEMANAGER->getElapsedTime();
	if (_elapsedSec >= 0.1f)
	{
		_elapsedSec -= 0.1f;
		for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end();)
		{
			if (_viBomb->isExplode)
			{
				if (_viBomb->currentFrameX >= IMAGEMANAGER->findImage(_viBomb->imageName)->getMaxFrameX())
				{
					_viBomb = _vBomb.erase(_viBomb);
				}
				else
				{
					_viBomb->currentFrameX++;
					_viBomb++;
				}
			}
			else
			{
				_viBomb++;
			}
		}
	}

	explode();
}

void bomb::render()
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		if (_viBomb->isExplode)
		IMAGEMANAGER->findImage(_viBomb->imageName)->frameRender(getMemDC(), _viBomb->rc.left, _viBomb->rc.top, _viBomb->currentFrameX, _viBomb->currentFrameY);
	}
}

void bomb::render(int tileX, int tileY)
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		if (tileX == _viBomb->tileX && tileY == _viBomb->tileY)
		{
			if (!_viBomb->isExplode)
			{
				IMAGEMANAGER->findImage(_viBomb->imageName)->frameRender(getMemDC(), _viBomb->rc.left, _viBomb->rc.top, _viBomb->currentFrameX, 0);
				IMAGEMANAGER->findImage(_viBomb->imageName)->alphaFrameRender(getMemDC(), _viBomb->rc.left, _viBomb->rc.top, _viBomb->currentFrameX, 1, 255 - _map->getAlpha(_viBomb->tileX, _viBomb->tileY));
			}
		}
	}
}

void bomb::fire(int tileX, int tileY, RECT rc)
{
	for (int i = 0; i < _vBomb.size(); i++)
	{
		if (_vBomb[i].tileX == tileX && _vBomb[i].tileY == tileY)
		{
			return;
		}
	}
	tagBomb bomb;
	ZeroMemory(&bomb, sizeof(tagBomb));
	bomb.rc = rc;
	bomb.x = (bomb.rc.left + bomb.rc.right) / 2;
	bomb.y = (bomb.rc.top + bomb.rc.bottom) / 2;
	bomb.currentFrameX = 0;
	bomb.currentFrameY = 0;
	bomb.tileX = tileX;
	bomb.tileY = tileY;
	bomb.isExplode = false;
	bomb.isSoundPlayed = false;
	bomb.imageName = "bomb";
	_vBomb.push_back(bomb);
	SOUNDMANAGER->play("bomb_lit", 0.3f);
}

void bomb::explode()
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		if (_viBomb->isExplode)
		{
			for (int i = _viBomb->tileY - 1; i <= _viBomb->tileY + 1; i++)
			{
				if (i < 0 || i >= _map->getYSize()) continue;
				for (int j = _viBomb->tileX - 1; j <= _viBomb->tileX + 1; j++)
				{
					if (j < 0 || j >= _map->getXSize()) continue;
					if (_map->getTileObject(j, i) == WALL_GOLD)
					{
						_map->setTileObject(j, i, OBJ_NONE);
						_map->setIsHaveTorch(j, i, false);
						_map->setTileItem(j, i, MAP_COIN10);
					}
					else if (_map->getTileObject(j, i) != OBJ_NONE && _map->getTileObject(j, i) != WALL_END 
						&& _map->getTileObject(j, i) != RED_ITEM_BOX && _map->getTileObject(j, i) != BLACK_ITEM_BOX)
					{
						_map->setTileObject(j, i, OBJ_NONE);
						_map->setIsHaveTorch(j, i, false);
					}
				}
			}
			if (!_viBomb->isSoundPlayed)
			{
				SOUNDMANAGER->play("bomb_explode", 0.3f);
				_viBomb->isSoundPlayed = true;
			}
		}
	}
}
