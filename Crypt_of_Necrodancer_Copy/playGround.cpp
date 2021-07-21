#include "stdafx.h"
#include "playGround.h"
#include "aStarTest.h"
#include "whiteSkeleton.h"
#include "slimeGreen.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	
	addImage();
	addSound();

	_map = new mapGenerator;
	_map->init(70, 70);
	_map->generate(7);
	_player = new player;
	_player->init(_map->getStartRoomX() + 2, _map->getStartRoomY() + 2);
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->setupPlayerRect();



	//������
	_slime = new slimeGreen;
	_slime->setTileMapLink(_map);
	_slime->init();
	 


	//SCENEMANAGER->addScene("player_test", new playerTestScene);
	//SCENEMANAGER->changeScene("player_test");


	////ī�޶� �׽�Ʈ ==================================================================
	//_player.x = BACKGROUNDX / 2;
	//_player.y = BACKGROUNDY / 2 + 200;

	//_player.rc = RectMakeCenter(_player.x, _player.y, 50, 100);
	//CAMERAMANAGER->setCameraCenter(_player.x, _player.y);


	////�浹ó���� ī�޶� ���� ���� �ۼ��ϴ� testPlayer======================
	//_test.x = BACKGROUNDX / 2 + 100;
	//_test.y = BACKGROUNDY / 2 + 200;

	//_test.rc = RectMakeCenter(_test.x, _test.y, 100, 100);
	////==============================================================================

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();



	_map->update();
	_player->update();
	/*CAMERAMANAGER->setCameraCenterX((_player->+ _skeleton->getRect().left)/2);
	CAMERAMANAGER->setCameraCenterY((_player->getRect().bottom + _skeleton->getRect().top) / 2);

	
	SCENEMANAGER->update();
	//_mapTool->update();
	//_randomMap->update();

	/*
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraLEFT() - TILESIZE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraLEFT() + TILESIZE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraTOP() - TILESIZE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraTOP() + TILESIZE);
	}
	*/

	////ī�޶� �׽�Ʈ��================================================================================================================
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	_player.x -= 5;
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	_player.x += 5;
	//}

	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	_player.y -= 5;
	//}

	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	_player.y += 5;
	//}
	//_player.rc = RectMakeCenter(_player.x, _player.y, 50, 100);
	//_test.rc = RectMakeCenter(_test.x, _test.y, 100, 100);

	//if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	//{
	//	if (!CAMERAMANAGER->getSeeLine())
	//	{
	//		CAMERAMANAGER->setSeeLine(true);
	//	}
	//	else
	//	{
	//		CAMERAMANAGER->setSeeLine(false);
	//	}
	//}

	////���� �������� �̿��ϰ�
	//CAMERAMANAGER->updateCamera(_player.x, _player.y); //�÷��̾��� ������ �߽����� �����̴� ī�޶�
	////CAMERAMANAGER->updateCamera(_player.rc, 0.7, 0.3); //�÷��̾ ���� �߽��̻� ������ ������
	////CAMERAMANAGER->updateCamera(_player.rc, 0.3, 0.7, 0.3, 0.7); //�÷��̾ �簢�� ���� ������ ������ ������

	////�浹�ϸ� ī�޶� ����
	//RECT temp;
	//if (IntersectRect(&temp, &_player.rc, &_test.rc))
	//{
	//	CAMERAMANAGER->vibrateScreen(_player.x, _player.y, 5.0f);	// 5.0f => ���� ���� 
	//}
	////============================================================================================================================
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, BLACKNESS);
	//================���� �� ���̿� �� �׸��ô�==========================

	HPEN myPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
	SelectObject(getMemDC(), myPen);
	_map->render();
	_player->render();
	_slime->render();
	//SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//SCENEMANAGER->render();
	DeleteObject(myPen);

	//ī�޶� �׽�Ʈ��
	//Rectangle(getMemDC(), _player.rc);
	//Rectangle(getMemDC(), _test.rc);
	//==================================================
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}


void playGround::addImage()
{
	//Ÿ�ϸ� �̹���
	IMAGEMANAGER->addFrameImage("boss_tile", "image/object/tile/boss.bmp", 216, 144, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dirt1_tile", "image/object/tile/dirt1.bmp", 216, 144, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dirt2_tile", "image/object/tile/dirt2.bmp", 216, 144, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shop_tile", "image/object/tile/shop.bmp", 72, 72, 1, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("water_tile", "image/object/tile/water.bmp", 216, 72, 3, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("stair_miniboss_tile", "image/object/tile/stair_miniboss.bmp", 144, 72, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("stair_locked_tile", "image/object/tile/stair_locked.bmp", 144, 72, 2, 1 ,true, RGB(255, 0, 255), true);

	//�� �̹��� ����
	IMAGEMANAGER->addFrameImage("sample_walls1", "image/object/walls/sampleWalls1.bmp", 384, 480, 8, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sample_walls2", "image/object/walls/sampleWalls2.bmp", 384, 384, 8, 4, true, RGB(255, 0, 255));

	//�� �̹���
	IMAGEMANAGER->addFrameImage("walls1", "image/object/walls/walls1.bmp", 576, 720, 8, 5, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("walls2", "image/object/walls/walls2.bmp", 576, 576, 8, 4, true, RGB(255, 0, 255), true);

	//���� �̹���
	IMAGEMANAGER->addFrameImage("bomb_trap", "image/object/trapBomb.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("up_trap", "image/object/trapBounceUp.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down_trap", "image/object/trapBounceDown.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left_trap", "image/object/trapBounceLeft.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right_trap", "image/object/trapBounceRight.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fast_trap", "image/object/trapSpeedUp.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slow_trap", "image/object/trapSpeedDown.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jump_trap", "image/object/trapJump.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door_trap", "image/object/trapDoor.bmp", 138, 108, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("spike_trap", "image/object/trapSpike.bmp", 189, 102, 3, 2, true, RGB(255, 0, 255));

	//�� �� ������Ʈ
	IMAGEMANAGER->addFrameImage("red_item_box", "image/object/boxRed.bmp", 144, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("black_item_box", "image/object/boxBlack.bmp", 144, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("box", "image/object/box.bmp", 102, 72, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("barrel", "image/object/barrel.bmp", 120, 72, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wall_torch", "image/object/walls/wall_torch.bmp", 144, 78, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wall_torch_black", "image/object/walls/wall_torch_black.bmp", 144, 78, 4, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->findImage("wall_torch")->setFrameX(0);
	IMAGEMANAGER->findImage("wall_torch")->setFrameY(0);

	//play HUD
	IMAGEMANAGER->addFrameImage("heart", "image/UI/heart.bmp", 100, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heartBeat", "image/UI/beat_marker.bmp", 24, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beatHeart", "image/UI/beat_heart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("money", "image/UI/money.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("diamond", "image/UI/diamond.bmp", 50, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("X", "image/UI/X.bmp", 14, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("number", "image/UI/number.bmp", 140, 18, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("itemHUD", "image/UI/itemHUD.bmp", 1890, 126, 21, 1, true, RGB(255, 0, 255));

	//item HUD
	IMAGEMANAGER->addFrameImage("dagger", "image/item/dagger.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("broadSword", "image/item/broadsword.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rapier", "image/item/rapier.bmp", 78, 162, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("longSword", "image/item/longsword.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("spear", "image/item/rapier.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255));
}

void playGround::addSound()
{
	SOUNDMANAGER->addSound("zone1-2", "music/zone1_2.mp3", true, false);
	SOUNDMANAGER->addSound("zone1-2_shopkeeper", "music/zone1_2_shopkeeper.ogg", true, false);
	SOUNDMANAGER->addSound("zone1-3", "music/zone1_3.mp3", true, false);
	SOUNDMANAGER->addSound("zone1-3_shopkeeper", "music/zone1_3_shopkeeper.ogg", true, false);
	SOUNDMANAGER->addSound("boss", "music/boss_2.ogg", true, false);
}
