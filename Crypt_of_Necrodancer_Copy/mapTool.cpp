#include "stdafx.h"
#include "mapTool.h"

HRESULT mapTool::init()
{
	//타일맵 이미지
	IMAGEMANAGER->addFrameImage("boss_tile", "image/object/tile/boss.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dirt1_tile", "image/object/tile/dirt1.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dirt2_tile", "image/object/tile/dirt2.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shop_tile", "image/object/tile/shop.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("water_tile", "image/object/tile/water.bmp", 144, 48, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stair_miniboss_tile", "image/object/tile/stair_miniboss.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));

	//벽 이미지
	IMAGEMANAGER->addFrameImage("walls", "image/object/walls/walls.bmp", 384, 864, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("walls1", "image/object/walls/walls1.bmp", 384, 480, 8, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("walls2", "image/object/walls/walls2.bmp", 384, 384, 8, 4, true, RGB(255, 0, 255));
	
	//함정 이미지
	IMAGEMANAGER->addFrameImage("bomb_trap", "imge/object/trapBomb.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("up_trap", "imge/object/trapBounceUp.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down_trap", "imge/object/trapBounceDown.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left_trap", "imge/object/trapBounceLeft.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right_trap", "imge/object/trapBounceRight.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fast_trap", "imge/object/trapSpeedUp.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slow_trap", "imge/object/trapSpeedDown.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("spike_trap", "imge/object/trapSpike.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));

	setup();
	_worldTime = TIMEMANAGER->getWorldTime();
	_isEvenLight = false;

	_tileMap = new tileMap;
	_tileMap->init(5, 5);
	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		switch (_category)
		{
		case CATEGORY_TERRAIN : 
			for (int i = 0; i < _vSampleTile.size(); i++)
			{
				if (PtInRect(&_vSampleTile[i].rc, _ptMouse))
				{
					_ctrSelect = CTRL_TERRAINDRAW;
					_currentCategory = CATEGORY_TERRAIN;
					_currentFloor = _vSampleTile[i].terrain;
					break;
				}
			}
			break;
		case CATEGORY_WALL1:
			for (int i = 0; i < SAMPLEWALLX * SAMPLEWALLY1; i++)
			{
				if (PtInRect(&_sampleWall1[i].rc, _ptMouse))
				{
					_ctrSelect = CTRL_WALLDRAW;
					_currentCategory = CATEGORY_WALL1;
					_currentWall.x = _sampleWall1[i].objectFrameX;
					_currentWall.y = _sampleWall1[i].objectFrameY;
					break;
				}
			}
			break;
		case CATEGORY_WALL2:
			for (int i = 0; i < SAMPLEWALLX * SAMPLEWALLY2; i++)
			{
				if (PtInRect(&_sampleWall2[i].rc, _ptMouse))
				{
					_ctrSelect = CTRL_WALLDRAW;
					_currentCategory = CATEGORY_WALL2;
					_currentWall.x = _sampleWall2[i].objectFrameX;
					_currentWall.y = _sampleWall2[i].objectFrameY;
					break;
				}
			}
			break;
		case CATEGORY_TRAP:
			break;
		}
		
		for (int i = 0; i < 3; i++)
		{
			if (i == 1) continue;
			if (PtInRect(&_categoryRect[i], _ptMouse))
			{
				switch (_category)
				{
				case CATEGORY_TERRAIN:
					if (i == 0) _category = CATEGORY_TRAP;
					else _category = CATEGORY_WALL1;
					break;
				case CATEGORY_WALL1:
					if (i == 0) _category = CATEGORY_TERRAIN;
					else _category = CATEGORY_WALL2;
					break;
				case CATEGORY_WALL2:
					if (i == 0) _category = CATEGORY_WALL1;
					else _category = CATEGORY_TRAP;
					break;
				case CATEGORY_TRAP:
					if (i == 0) _category = CATEGORY_WALL2;
					else _category = CATEGORY_TERRAIN;
					break;
				}
			}
		}
	}

	switch (_ctrSelect)
	{
	case CTRL_TERRAINDRAW:
		_tileMap->drawTerrain(_currentFloor);
		break;
	case CTRL_WALLDRAW:
		_tileMap->drawWall(_currentWall.x, _currentWall.y, _currentCategory);
		break;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
	{
		_tileMap->resizeTile(_tileMap->getTileX() + 1, _tileMap->getTileY() + 1);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
	{
		if (_tileMap->getTileX() > 1 && _tileMap->getTileY() > 1)
		{
			_tileMap->resizeTile(_tileMap->getTileX() - 1, _tileMap->getTileY() - 1);
		}
	}

	_tileMap->update();
}

void mapTool::render()
{

	drawSample();
	drawCategory();
	_tileMap->render();
}

void mapTool::setup()
{
	_category = CATEGORY_TERRAIN;
	_currentCategory = CATEGORY_TERRAIN;
	_currentFloor = DIRT1;
	_ctrSelect = CTRL_TERRAINDRAW;

	//샘플 타일 셋 설정
	for (int i = 0; i < SAMPLETILEMAX; i++)
	{
		tagSampleTile sample;
		sample.terrain = (TERRAIN)i;
		sample.rc = RectMake(WINSIZEX - 600 + 100 * i, 100, 100, 100);
		_vSampleTile.push_back(sample);
	}

	//샘플 벽1 설정
	for (int i = 0; i < SAMPLEWALLY1; i++)
	{
		for (int j = 0; j < SAMPLEWALLX; j++)
		{
			_sampleWall1[i*SAMPLEWALLX + j].objectFrameX = j;
			_sampleWall1[i*SAMPLEWALLX + j].objectFrameY = i;

			_sampleWall1[i*SAMPLEWALLX + j].rc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("walls1")->getWidth() - 150 + j * WALLWIDTH,
				100 + i * WALLHEIGHT, WALLWIDTH, WALLHEIGHT);
		}
	}

	//샘플 벽2 설정
	for (int i = 0; i < SAMPLEWALLY2; i++)
	{
		for (int j = 0; j < SAMPLEWALLX; j++)
		{
			_sampleWall2[i*SAMPLEWALLX + j].objectFrameX = j;
			_sampleWall2[i*SAMPLEWALLX + j].objectFrameY = i;

			_sampleWall2[i*SAMPLEWALLX + j].rc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("walls2")->getWidth() - 150 + j * WALLWIDTH,
				100 + i * WALLHEIGHT, WALLWIDTH, WALLHEIGHT);
		}
	}

	for (int i = 0; i < SAMPLETRAPMAX; i++)
	{
		tagSampleObject sample;
		sample.obj = 
		sample.rc = RectMake(WINSIZEX - 600 + 100 * i, 100, 100, 100);
		_vSampleTile.push_back(sample);
	}

	//카테고리 렉트 설정
	_categoryRect[0] = RectMakeCenter(WINSIZEX - 500, 50, 20, 20);
	_categoryRect[1] = RectMakeCenter(WINSIZEX - 350, 50, 200, 20);
	_categoryRect[2] = RectMakeCenter(WINSIZEX - 200, 50, 20, 20);
}

void mapTool::drawSample()
{
	switch (_category)
	{
	case CATEGORY_TERRAIN:
		//샘플 타일 그리기
		for (int i = 0; i < _vSampleTile.size(); i++)
		{
			Rectangle(getMemDC(), _vSampleTile[i].rc);
			switch (_vSampleTile[i].terrain)
			{
			case DIRT1:
				IMAGEMANAGER->frameRender("dirt1_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - 12,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - 12, 0, 0);
				break;
			case DIRT2:
				IMAGEMANAGER->frameRender("dirt2_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - 12,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - 12, 0, 0);
				break;
			case BOSS:
				IMAGEMANAGER->frameRender("boss_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - 12,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - 12, 0, 0);
				break;
			case WATER:
				IMAGEMANAGER->frameRender("water_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - 12,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - 12, 0, 0);
				break;
			case SHOP:
				IMAGEMANAGER->frameRender("shop_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - 12,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - 12, 0, 0);
				break;
			}
		}
		break;
	case CATEGORY_WALL1:
		//샘플 벽1 그리기
		IMAGEMANAGER->render("walls1", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("walls1")->getWidth() - 150, 100);
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < SAMPLEWALLX * SAMPLEWALLY1; i++)
			{
				Rectangle(getMemDC(), _sampleWall1[i].rc);
			}
		}
		break;
	case CATEGORY_WALL2:
		//샘플 벽2 그리기
		IMAGEMANAGER->render("walls2", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("walls2")->getWidth() - 150, 100);
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < SAMPLEWALLX * SAMPLEWALLY2; i++)
			{
				Rectangle(getMemDC(), _sampleWall2[i].rc);
			}
		}
		break;

	}
}

void mapTool::drawCategory()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 3; i++)
		{
			Rectangle(getMemDC(), _categoryRect[i]);
		}
	}

	char str[128];
	switch (_category)
	{
	case CATEGORY_TERRAIN:
		sprintf_s(str, "Terrain", str, strlen(str));
		break;
	case CATEGORY_WALL1:
		sprintf_s(str, "Wall1", str, strlen(str));
		break;
	case CATEGORY_WALL2:
		sprintf_s(str, "Wall2", str, strlen(str));
		break;
	case CATEGORY_TRAP:
		sprintf_s(str, "Trap", str, strlen(str));
		break;
	}
	DrawText(getMemDC(), str, strlen(str), &_categoryRect[1], DT_CENTER);

	sprintf_s(str, "<", str, strlen(str));
	DrawText(getMemDC(), str, strlen(str), &_categoryRect[0], DT_CENTER);
	sprintf_s(str, ">", str, strlen(str));
	DrawText(getMemDC(), str, strlen(str), &_categoryRect[2], DT_CENTER);

}

