#include "stdafx.h"
#include "miniMap.h"

HRESULT miniMap::init()
{
	IMAGEMANAGER->addImage("minimap_door", "image/minimap/minimap_door.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_enemy", "image/minimap/minimap_enemy.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_item", "image/minimap/minimap_item.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_obj_none", "image/minimap/minimap_obj_none.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_player", "image/minimap/minimap_player.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_shopkeeper", "image/minimap/minimap_shopkeeper.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_stair", "image/minimap/minimap_stair.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_trap", "image/minimap/minimap_trap.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_basic", "image/minimap/minimap_wall_basic.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_end", "image/minimap/minimap_wall_end.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_gold", "image/minimap/minimap_wall_gold.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_stone", "image/minimap/minimap_wall_stone.bmp", 6, 6, true, RGB(255, 0, 255));
	_miniMapBuffer = new image;
	_miniMapBuffer->init(0, 0);
	return S_OK;
}

void miniMap::release()
{

}

void miniMap::render(HDC hdc)
{
	_miniMapBuffer->render(hdc, WINSIZEX - _miniMapBuffer->getWidth() - 100, WINSIZEY - _miniMapBuffer->getHeight() - 100);
}

void miniMap::setupMiniMap(int sizeX, int sizeY)
{
	_mapSizeX = sizeX;
	_mapSizeY = sizeY;
	_miniMapBuffer->release();
	_miniMapBuffer->init(MINIMAP_TILE_SIZE * _mapSizeX, MINIMAP_TILE_SIZE * _mapSizeY, true, RGB(0, 0, 0));
	PatBlt(_miniMapBuffer->getMemDC(), 0, 0, _miniMapBuffer->getWidth(), _miniMapBuffer->getHeight(), BLACKNESS);
}

void miniMap::drawPlayer(int tileX, int tileY)
{
	IMAGEMANAGER->findImage("minimap_player")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
	return;
}

void miniMap::drawMiniMap(int tileX, int tileY, TERRAIN terrain, OBJECT obj, MAP_ITEM item, bool isEnemy)
{
	if (terrain == EMPTY) return;
	if (isEnemy)
	{
		IMAGEMANAGER->findImage("minimap_enemy")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		return;
	}
	switch (obj)
	{
	case OBJ_NONE:
		IMAGEMANAGER->findImage("minimap_obj_none")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case WALL_BASIC:
		IMAGEMANAGER->findImage("minimap_wall_basic")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case WALL_GOLD:
		IMAGEMANAGER->findImage("minimap_wall_gold")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case WALL_STONE:
	case WALL_CRACK:
		IMAGEMANAGER->findImage("minimap_wall_stone")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case WALL_DOOR:
		IMAGEMANAGER->findImage("minimap_door")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case WALL_END:
		IMAGEMANAGER->findImage("minimap_wall_end")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case TR_BOMB:
	case TR_UP:
	case TR_DOWN:
	case TR_LEFT:
	case TR_RIGHT:
	case TR_FAST:
	case TR_SLOW:
	case TR_JUMP:
	case TR_DOOR:
	case TR_SPIKE:
		IMAGEMANAGER->findImage("minimap_trap")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case RED_ITEM_BOX:
	case BLACK_ITEM_BOX:
		IMAGEMANAGER->findImage("minimap_item")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case BOX:
	case BARREL:
		IMAGEMANAGER->findImage("minimap_enemy")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
		break;
	case SHOPKEEPER:
		IMAGEMANAGER->findImage("minimap_shopkeeper")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
	default:
		break;
	}
	if (item != MAP_ITEM_NONE)
	{
		IMAGEMANAGER->findImage("minimap_item")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
	}
}


