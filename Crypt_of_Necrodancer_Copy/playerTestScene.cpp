#include "stdafx.h"
#include "playerTestScene.h"

HRESULT playerTestScene::init()
{
	_map = new mapGenerator;
	_map->init(70,70);
	_map->generate(7);
	_player = new player;
	_player->init(_map->getStartRoomX() + 2, _map->getStartRoomY() + 2);
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->setupPlayerRect();

	//CAMERAMANAGER->setCamera(0, 0);
	/*_UIM = new UIManager;
	_UIM->init();
	_UIM->setHeartBeat(7);*/

	_objectManager = new objectManager;
	_objectManager->setObjectMapMemoryAddressLink(_map);
	_objectManager->setObjectPlayerMemoryAddressLink(_player);
	return S_OK;
}

void playerTestScene::release()
{
}

void playerTestScene::update()
{
	_map->update();
	_player->update();
	//RENDERMANAGER->update();
	//_UIM->updaetHeartBeat(1.7f);

	_objectManager->update();
}

void playerTestScene::render()
{
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
		}
	}


	for (int i = 0; i < _map->getYSize(); ++i)
	{
		for (int j = 0; j < _map->getXSize(); ++j)
		{
			//여기는 타일 오브젝트
			tagTile tile = _map->getTile(j, i);
			switch (tile.obj)
			{
			case OBJ_NONE:
				break;
			case WALL_BASIC:
				IMAGEMANAGER->alphaFrameRender("walls1", getMemDC(), tile.rc.left, tile.rc.top - (TILESIZE * 5) / 8, tile.objectFrameX, tile.objectFrameY, tile.alpha);
				break;
			case WALL_GOLD:
			case WALL_STONE:
			case WALL_CRACK:
			case WALL_DOOR:
			case WALL_END:
				IMAGEMANAGER->alphaFrameRender("walls2", getMemDC(), tile.rc.left,
					tile.rc.top - (TILESIZE * 5) / 8, tile.objectFrameX, tile.objectFrameY, tile.alpha);
				break;
			case TR_BOMB:
				IMAGEMANAGER->frameRender("bomb_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_UP:
				IMAGEMANAGER->frameRender("up_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_DOWN:
				IMAGEMANAGER->frameRender("down_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_LEFT:
				IMAGEMANAGER->frameRender("left_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_RIGHT:
				IMAGEMANAGER->frameRender("right_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_FAST:
				IMAGEMANAGER->frameRender("fast_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_SLOW:
				IMAGEMANAGER->frameRender("slow_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_JUMP:
				IMAGEMANAGER->frameRender("jump_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_DOOR:
				IMAGEMANAGER->frameRender("door_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case TR_SPIKE:
				IMAGEMANAGER->frameRender("spike_trap", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case RED_ITEM_BOX:
				IMAGEMANAGER->frameRender("red_item_box", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case BLACK_ITEM_BOX:
				IMAGEMANAGER->frameRender("black_item_box", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case BOX:
				IMAGEMANAGER->frameRender("box", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("box")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("box")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			case BARREL:
				IMAGEMANAGER->frameRender("barrel", getMemDC(),
					(tile.rc.left + tile.rc.right) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameWidth() / 2,
					(tile.rc.bottom + tile.rc.top) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameHeight() / 2, tile.objectFrameX, tile.objectFrameY);
				break;
			}

			//플레이어 렌더
			if (_player->getRenderX() == j && _player->getRenderY() == i) _player->render();


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

	//_UIM->renderHeartBeat();
}
