#include "stdafx.h"
#include "playerTestScene.h"

HRESULT playerTestScene::init()
{
	CAMERAMANAGER->setCamera(0, 0);
	_map = new mapGenerator;
	_map->init(70,70);
	_map->generate(7);
	_player = new player;
	_player->init(_map->getStartRoomX() + 2, _map->getStartRoomY() + 2);
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->setupPlayerRect();
	_em = new enemyManager;
	_em->setMapGeneratorMemoryAddressLink(_map);
	_em->setPlayerMemoryAddressLink(_player);
	_em->init();
	_UIM = new UIManager;
	_UIM->init();
	_UIM->setHeartBeat(7);
	return S_OK;
}

void playerTestScene::release()
{
}

void playerTestScene::update()
{
	//_map->update();
	_player->update();
	//RENDERMANAGER->update();
	_em->update();

	_UIM->updaetHeartBeat(1.7f);
}

void playerTestScene::render()
{
	_map->render();
	_player->render();
	_em->render();
	for (int i = 0; i < _map->getYSize(); ++i)
	{
		for (int j = 0; j < _map->getXSize(); ++j)
		{
			//여긴 타일 렌더
			if (_map->getAlpha(j, i) <= 0) continue;
			tagTile tile = _map->getTile(j, i);
			switch (_map->getTileTerrain(j, i))
			{
			case DIRT1:
				IMAGEMANAGER->alphaFrameRender("dirt1_tile", getMemDC(),
					tile.rc.left, tile.rc.top, tile.terrainFrameX, tile.terrainFrameY, tile.alpha);
				break;
			case DIRT2:
				IMAGEMANAGER->alphaFrameRender("dirt2_tile", getMemDC(),
					tile.rc.left, tile.rc.top, tile.terrainFrameX, tile.terrainFrameY, tile.alpha);
				break;
			case BOSS:
				IMAGEMANAGER->alphaFrameRender("boss_tile", getMemDC(),
					tile.rc.left, tile.rc.top, tile.terrainFrameX, tile.terrainFrameY, tile.alpha);
				break;
			case WATER:
				IMAGEMANAGER->alphaFrameRender("water_tile", getMemDC(),
					tile.rc.left, tile.rc.top, tile.terrainFrameX, tile.terrainFrameY, tile.alpha);
				break;
			case SHOP:
				IMAGEMANAGER->alphaFrameRender("shop_tile", getMemDC(),
					tile.rc.left, tile.rc.top, 0, 0, tile.alpha);
				break;
			case STAIR_BOSS:
				IMAGEMANAGER->alphaFrameRender("stair_miniboss_tile", getMemDC(),
					tile.rc.left, tile.rc.top, tile.terrainFrameX, tile.terrainFrameY, tile.alpha);
				break;
			case STAIR_NONE:
				IMAGEMANAGER->alphaFrameRender("stair_locked_tile", getMemDC(),
					tile.rc.left, tile.rc.top, 1, 0, tile.alpha);
				break;
			case EMPTY:
				break;
			}

			if (_player->getTileX() == j && _player->getTileY() == i) _player->render();

			//여기는 타일 오브젝트
			if (_map->getTileObject(j, i) == OBJ_NONE) continue;
			if (tile.obj == WALL_BASIC)
			{
				IMAGEMANAGER->alphaFrameRender("walls1", getMemDC(), tile.rc.left, tile.rc.top - (TILESIZE * 5) / 8, tile.objectFrameX, tile.objectFrameY, tile.alpha);
			}
			else if (tile.obj == WALL_GOLD || tile.obj == WALL_STONE || tile.obj == WALL_CRACK
				|| tile.obj == WALL_DOOR || tile.obj == WALL_END)
			{
				IMAGEMANAGER->alphaFrameRender("walls2", getMemDC(), tile.rc.left, tile.rc.top - (TILESIZE * 5) / 8, tile.objectFrameX, tile.objectFrameY, tile.alpha);
			}

			if (tile.isHaveTorch)
			{
				IMAGEMANAGER->frameRender("wall_torch", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("wall_torch")->getFrameWidth() / 2 - 5,
					tile.rc.top - (TILESIZE * 5) / 8 - TILESIZE / 3);
				IMAGEMANAGER->alphaFrameRender("wall_torch_black", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("wall_torch_black")->getFrameWidth() / 2 - 5,
					tile.rc.top - (TILESIZE * 5) / 8 - TILESIZE / 3, 255 - tile.alpha);
			}
		}
	}

	_UIM->renderHeartBeat();
}
