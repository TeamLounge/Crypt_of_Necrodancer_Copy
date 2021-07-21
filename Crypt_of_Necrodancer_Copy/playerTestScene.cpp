#include "stdafx.h"
#include "playerTestScene.h"


HRESULT playerTestScene::init()
{
	SOUNDMANAGER->addSound("zone1-1", "music/zone1_1.ogg", true, false);
	SOUNDMANAGER->addSound("zone1-1_shopkeeper", "music/zone1_1_shopkeeper.ogg", true, false);
	
	//맵
	_map = new mapGenerator;
	_map->init(70,70);
	_map->generate(7);

	//플레이어
	_player = new player;
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->init(_map->getStartRoomX() + 2, _map->getStartRoomY() + 2);

	_player->setupPlayerRect();

	//에너미
	_em = new enemyManager;
	_em->setMapGeneratorMemoryAddressLink(_map);
	_em->setPlayerMemoryAddressLink(_player);
	_em->init();

	//UI
	_UIM = new UIManager;
	_UIM->init();
	CAMERAMANAGER->setCamera(0, 0);
	_UIM->setHeartBeat(7);
	_UIM->setItemHUD();

	//오브젝트
	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setObjectMapMemoryAddressLink(_map);
	_objectManager->setObjectPlayerMemoryAddressLink(_player);

	//사운드 플레이
	SOUNDMANAGER->play("zone1-1", 0.2f);
	SOUNDMANAGER->play("zone1-1_shopkeeper", 0.2f);
	SOUNDMANAGER->setGroup("zone1-1");
	SOUNDMANAGER->setGroup("zone1-1_shopkeeper");

	_weapon = new weapon;
	_weapon->init();

	_weapon->setPlayerMemoryAddressLink(_player);
	_player->setWeaponMemoryAddressLink(_weapon);
	_weapon->setUIMMemortAddressLink(_UIM);
	_UIM->setWeaponMemoryAddressLink(_weapon);
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
	_em->update();
	_UIM->updaetHeartBeat(1.7f);
	_objectManager->update();
	_weapon->update();
	_UIM->updateItemHUD();
}

void playerTestScene::render()
{
	_map->render();
	_player->render();
	/*
	for (int i = 0; i < _map->getYSize(); ++i)
	{
		for (int j = 0; j < _map->getXSize(); ++j)
		{
			//여기는 타일 오브젝트
			tagTile* tile = _map->getTile(j, i);
			if (tile->alpha = 0) continue;
			switch (_map->getTileObject(j, i))
			{
			case OBJ_NONE:
				break;
			case WALL_BASIC:
				IMAGEMANAGER->alphaFrameRender("walls1", getMemDC(), tile->rc.left, tile->rc.top - (TILESIZE * 5) / 8, tile->objectFrameX, tile->objectFrameY, tile->alpha);
				break;
			case WALL_GOLD:
			case WALL_STONE:
			case WALL_CRACK:
			case WALL_DOOR:
			case WALL_END:
				IMAGEMANAGER->alphaFrameRender("walls2", getMemDC(), tile->rc.left,
					tile->rc.top - (TILESIZE * 5) / 8, tile->objectFrameX, tile->objectFrameY, _map->getAlpha(j, i));
				break;
			case TR_BOMB:
				IMAGEMANAGER->frameRender("bomb_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_UP:
				IMAGEMANAGER->frameRender("up_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_DOWN:
				IMAGEMANAGER->frameRender("down_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_LEFT:
				IMAGEMANAGER->frameRender("left_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_RIGHT:
				IMAGEMANAGER->frameRender("right_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_FAST:
				IMAGEMANAGER->frameRender("fast_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_SLOW:
				IMAGEMANAGER->frameRender("slow_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_JUMP:
				IMAGEMANAGER->frameRender("jump_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("jump_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_DOOR:
				IMAGEMANAGER->frameRender("door_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case TR_SPIKE:
				IMAGEMANAGER->frameRender("spike_trap", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case RED_ITEM_BOX:
				IMAGEMANAGER->frameRender("red_item_box", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case BLACK_ITEM_BOX:
				IMAGEMANAGER->frameRender("black_item_box", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case BOX:
				IMAGEMANAGER->frameRender("box", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("box")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("box")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			case BARREL:
				IMAGEMANAGER->frameRender("barrel", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameWidth() / 2,
					(tile->rc.bottom + tile->rc.top) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameHeight() / 2, tile->objectFrameX, tile->objectFrameY);
				break;
			}

			//플레이어 렌더
			if (_player->getRenderX() == j && _player->getRenderY() == i) _player->render();


			if (tile->isHaveTorch)
			{
				IMAGEMANAGER->frameRender("wall_torch", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("wall_torch")->getFrameWidth() / 2 - 5,
					tile->rc.top - (TILESIZE * 5) / 8 - TILESIZE / 3);
				IMAGEMANAGER->alphaFrameRender("wall_torch_black", getMemDC(),
					(tile->rc.left + tile->rc.right) / 2 - IMAGEMANAGER->findImage("wall_torch_black")->getFrameWidth() / 2 - 5,
					tile->rc.top - (TILESIZE * 5) / 8 - TILESIZE / 3, 255 - tile->alpha);
			}

		}
	}
	*/
	_em->render();
	_UIM->renderHeartBeat();
	_weapon->render();
	_UIM->renderItemHUD();
}
