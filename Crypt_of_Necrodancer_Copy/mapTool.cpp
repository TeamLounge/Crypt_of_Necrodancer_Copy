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
	IMAGEMANAGER->addFrameImage("bomb_trap", "image/object/trapBomb.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("up_trap", "image/object/trapBounceUp.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down_trap", "image/object/trapBounceDown.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left_trap", "image/object/trapBounceLeft.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right_trap", "image/object/trapBounceRight.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fast_trap", "image/object/trapSpeedUp.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slow_trap", "image/object/trapSpeedDown.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door_trap", "image/object/trapDoor.bmp", 92, 72, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("spike_trap", "image/object/trapSpike.bmp", 126, 68, 3, 2, true, RGB(255, 0, 255));

	//그 외 오브젝트
	IMAGEMANAGER->addFrameImage("red_item_box", "image/object/boxRed.bmp", 96, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("black_item_box", "image/object/boxBlack.bmp", 96, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("box", "image/object/box.bmp", 68, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("barrel", "image/object/barrel.bmp", 80, 48, 2, 1, true, RGB(255, 0, 255));

	_tileMap = new tileMap;
	_tileMap->init();

	setup();

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
		case CATEGORY_OBJECT:
			for (int i = 0; i < _vSampleTrap.size(); i++)
			{
				if (PtInRect(&_vSampleTrap[i].rc, _ptMouse))
				{
					_ctrSelect = CTRL_OBJECTDRAW;
					_currentCategory = CATEGORY_OBJECT;
					_currentTrap = _vSampleTrap[i].obj;
					break;
				}
			}
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
					if (i == 0) _category = CATEGORY_OBJECT;
					else _category = CATEGORY_WALL1;
					break;
				case CATEGORY_WALL1:
					if (i == 0) _category = CATEGORY_TERRAIN;
					else _category = CATEGORY_WALL2;
					break;
				case CATEGORY_WALL2:
					if (i == 0) _category = CATEGORY_WALL1;
					else _category = CATEGORY_OBJECT;
					break;
				case CATEGORY_OBJECT:
					if (i == 0) _category = CATEGORY_WALL2;
					else _category = CATEGORY_TERRAIN;
					break;
				}
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (PtInRect(&_tileSizeInput[i].rc, _ptMouse))
			{
				if (!_tileSizeInput[i].isSelect)
				{
					if (i == 0)
					{
						_tileSizeInput[1].isSelect = false;
					}
					else
					{
						_tileSizeInput[0].isSelect = false;
					}
					_tileSizeInput[i].isSelect = true;
				}
				else
				{
					_tileSizeInput[i].isSelect = false;
				}
			}
		}

		if (PtInRect(&_resizeButton, _ptMouse))
		{
			if (!_tileSizeInput[0].str.empty() && !_tileSizeInput[1].str.empty())
			{
				_tileMap->resizeTile(stoi(_tileSizeInput[0].str), stoi(_tileSizeInput[1].str));
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
	case CTRL_OBJECTDRAW:
		_tileMap->drawObject(_currentTrap);
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

	for (int i = 0; i < 2; i++)
	{
		if (_tileSizeInput[i].isSelect)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_BACK))
			{
				if (!_tileSizeInput[i].str.empty())
				{
					_tileSizeInput[i].str.erase(_tileSizeInput[i].str.size() - 1);
				}
			}

			for (int j = 0; j < 10; j++)
			{
				if (KEYMANAGER->isOnceKeyDown(char(j+48)))
				{
					_tileSizeInput[i].str.append(to_string(j));
				}
			}
		}
	}

}

void mapTool::render()
{

	drawSample();
	drawCategory();
	_tileMap->render();
	
	char str[128];
	sprintf_s(str, "x :");
	TextOut(getMemDC(), _tileSizeInput[0].rc.left - 25, _tileSizeInput[0].rc.top + 5, str, strlen(str));
	sprintf_s(str, "y :");
	TextOut(getMemDC(), _tileSizeInput[1].rc.left - 25, _tileSizeInput[1].rc.top + 5, str, strlen(str));

	for (int i = 0; i < 2; i++)
	{
		if (_tileSizeInput[i].isSelect)
		{
			HPEN myPen = (HPEN)CreatePen(1, 3, RGB(0, 0, 0));
			SelectObject(getMemDC(), myPen);
			Rectangle(getMemDC(), _tileSizeInput[i].rc);
			DeleteObject(myPen);
		}
		else
		{
			HPEN myPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
			SelectObject(getMemDC(), myPen);
			Rectangle(getMemDC(), _tileSizeInput[i].rc);
			DeleteObject(myPen);
		}
	}
	DrawText(getMemDC(), _tileSizeInput[0].str.c_str(), strlen(_tileSizeInput[0].str.c_str()), &_tileSizeInput[0].rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(getMemDC(), _tileSizeInput[1].str.c_str(), strlen(_tileSizeInput[1].str.c_str()), &_tileSizeInput[1].rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	HPEN myPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
	SelectObject(getMemDC(), myPen);
	Rectangle(getMemDC(), _resizeButton);
	DeleteObject(myPen);
	sprintf_s(str, "RESIZE");
	DrawText(getMemDC(), str, strlen(str), &_resizeButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
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
		sample.rc = RectMake(WINSIZEX - 600 + 100 * (i % 5), 100 + (i / 5) * 100, 100, 100);
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

	//함정 샘플 설정
	for (int i = 0; i < SAMPLETRAPMAX; i++)
	{
		tagSampleObject sample;
		sample.obj = (OBJECT)(i + 7);
		sample.rc = RectMake(WINSIZEX - 600 + 100 * (i % 5), 100 + (i / 5) * 100, 100, 100);
		sample.objectFrameX = 0;
		sample.objectFrameY = 0;
		_vSampleTrap.push_back(sample);
	}

	//카테고리 렉트 설정
	_categoryRect[0] = RectMakeCenter(WINSIZEX - 500, 50, 20, 20);
	_categoryRect[1] = RectMakeCenter(WINSIZEX - 350, 50, 200, 20);
	_categoryRect[2] = RectMakeCenter(WINSIZEX - 200, 50, 20, 20);

	//타일 사이즈 관련 구조체 설정
	for (int i = 0; i < 2; i++)
	{
		_tileSizeInput[i].rc = RectMakeCenter(WINSIZEX - 500 + i * 150, WINSIZEY - 200, 100, 30);
		_tileSizeInput[i].isSelect = false;
	}
	_tileSizeInput[0].str = to_string(_tileMap->getTileX());
	_tileSizeInput[1].str = to_string(_tileMap->getTileY());

	_resizeButton = RectMakeCenter(WINSIZEX - 200, WINSIZEY - 200, 100, 30);
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
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - TILESIZE/2,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - TILESIZE / 2, 0, 0);
				break;
			case DIRT2:
				IMAGEMANAGER->frameRender("dirt2_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - TILESIZE / 2,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - TILESIZE / 2, 0, 0);
				break;
			case BOSS:
				IMAGEMANAGER->frameRender("boss_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - TILESIZE / 2,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - TILESIZE / 2, 0, 0);
				break;
			case WATER:
				IMAGEMANAGER->frameRender("water_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - TILESIZE / 2,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - TILESIZE / 2, 0, 0);
				break;
			case SHOP:
				IMAGEMANAGER->frameRender("shop_tile", getMemDC(),
					(_vSampleTile[i].rc.left + _vSampleTile[i].rc.right) / 2 - TILESIZE / 2,
					(_vSampleTile[i].rc.bottom + _vSampleTile[i].rc.top) / 2 - TILESIZE / 2, 0, 0);
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
	case CATEGORY_OBJECT:
		//샘플 함정 그리기
		for (int i = 0; i < _vSampleTrap.size(); i++)
		{
			Rectangle(getMemDC(), _vSampleTrap[i].rc);
			switch (_vSampleTrap[i].obj)
			{
			case TR_BOMB:
				IMAGEMANAGER->frameRender("bomb_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_UP:
				IMAGEMANAGER->frameRender("up_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_DOWN:
				IMAGEMANAGER->frameRender("down_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_LEFT:
				IMAGEMANAGER->frameRender("left_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_RIGHT:
				IMAGEMANAGER->frameRender("right_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_FAST:
				IMAGEMANAGER->frameRender("fast_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_SLOW:
				IMAGEMANAGER->frameRender("slow_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_DOOR:
				IMAGEMANAGER->frameRender("door_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case TR_SPIKE:
				IMAGEMANAGER->frameRender("spike_trap", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case RED_ITEM_BOX:
				IMAGEMANAGER->frameRender("red_item_box", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case BLACK_ITEM_BOX:
				IMAGEMANAGER->frameRender("black_item_box", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case BOX:
				IMAGEMANAGER->frameRender("box", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, 0, 0);
				break;
			case BARREL:
				IMAGEMANAGER->frameRender("barrel", getMemDC(),
					(_vSampleTrap[i].rc.left + _vSampleTrap[i].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(_vSampleTrap[i].rc.bottom + _vSampleTrap[i].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, 0, 0);
				break;
			}
		}
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
	case CATEGORY_OBJECT:
		sprintf_s(str, "Object", str, strlen(str));
		break;
	}
	DrawText(getMemDC(), str, strlen(str), &_categoryRect[1], DT_CENTER);

	sprintf_s(str, "<", str, strlen(str));
	DrawText(getMemDC(), str, strlen(str), &_categoryRect[0], DT_CENTER);
	sprintf_s(str, ">", str, strlen(str));
	DrawText(getMemDC(), str, strlen(str), &_categoryRect[2], DT_CENTER);

}

