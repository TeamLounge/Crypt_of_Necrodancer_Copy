#include "stdafx.h"
#include "bomb.h"

HRESULT bomb::init()
{
	_worldTime = TIMEMANAGER->getWorldTime();
	_elapsedSec = 0;
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
}

void bomb::render()
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		IMAGEMANAGER->findImage(_viBomb->imageName)->frameRender(getMemDC(), _viBomb->rc.left, _viBomb->rc.top, _viBomb->currentFrameX, _viBomb->currentFrameY);
	}
}

void bomb::fire(int tileX, int tileY, RECT rc)
{
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
	bomb.imageName = "bomb";
	_vBomb.push_back(bomb);
}
