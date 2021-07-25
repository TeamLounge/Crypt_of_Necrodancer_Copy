#include "stdafx.h"
#include "playGround.h"
#include "aStarTest.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	
	addImage();



	SCENEMANAGER->addScene("player_test", new playerTestScene);
	SCENEMANAGER->changeScene("player_test");
	//SCENEMANAGER->addScene("bossScene", new bossScene);
	//SCENEMANAGER->changeScene("bossScene");


	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();


	
	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, BLACKNESS);
	//================제발 이 사이에 좀 그립시다==========================

	HPEN myPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
	SelectObject(getMemDC(), myPen);

	SCENEMANAGER->render();

	DeleteObject(myPen);

	//==================================================
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}


void playGround::addImage()
{
	//타일맵 이미지
	IMAGEMANAGER->addFrameImage("boss_tile", "image/object/tile/boss.bmp", 216, 144, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dirt1_tile", "image/object/tile/dirt1.bmp", 216, 144, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dirt2_tile", "image/object/tile/dirt2.bmp", 216, 144, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shop_tile", "image/object/tile/shop.bmp", 72, 72, 1, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("water_tile", "image/object/tile/water.bmp", 216, 72, 3, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("stair_miniboss_tile", "image/object/tile/stair_miniboss.bmp", 144, 72, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("stair_locked_tile", "image/object/tile/stair_locked.bmp", 144, 72, 2, 1 ,true, RGB(255, 0, 255), true);

	//벽 이미지 샘플
	IMAGEMANAGER->addFrameImage("sample_walls1", "image/object/walls/sampleWalls1.bmp", 384, 480, 8, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sample_walls2", "image/object/walls/sampleWalls2.bmp", 384, 384, 8, 4, true, RGB(255, 0, 255));

	//벽 이미지
	IMAGEMANAGER->addFrameImage("walls1", "image/object/walls/walls1.bmp", 576, 720, 8, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("walls2", "image/object/walls/walls2.bmp", 576, 576, 8, 4, true, RGB(255, 0, 255));
	//벽 위에 알파값 씌울 검은 이미지
	IMAGEMANAGER->addImage("wall_black", "image/object/walls/wall_black.bmp", 72, 117, true, RGB(255, 0, 255), true);

	//함정 이미지
	IMAGEMANAGER->addFrameImage("bomb_trap", "image/object/trapBomb.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("up_trap", "image/object/trapBounceUp.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("down_trap", "image/object/trapBounceDown.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("left_trap", "image/object/trapBounceLeft.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("right_trap", "image/object/trapBounceRight.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("fast_trap", "image/object/trapSpeedUp.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slow_trap", "image/object/trapSpeedDown.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("jump_trap", "image/object/trapJump.bmp", 72, 84, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("door_trap", "image/object/trapDoor.bmp", 138, 108, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spike_trap", "image/object/trapSpike.bmp", 189, 102, 3, 2, true, RGB(255, 0, 255), true);

	//그 외 오브젝트
	IMAGEMANAGER->addFrameImage("red_item_box", "image/object/boxRed.bmp", 144, 60, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("black_item_box", "image/object/boxBlack.bmp", 144, 60, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("box", "image/object/box.bmp", 102, 72, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("barrel", "image/object/barrel.bmp", 120, 72, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("wall_torch", "image/object/walls/wall_torch.bmp", 144, 78, 4, 1, true, RGB(255, 0, 255), true);
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
	IMAGEMANAGER->addFrameImage("dagger", "image/item/dagger.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("broadSword", "image/item/broadsword.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("rapier", "image/item/rapier.bmp", 78, 162, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("longSword", "image/item/longsword.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spear", "image/item/rapier.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shovelBasic", "image/item/shovel_basic.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shovelTitanium", "image/item/shovel_titanium.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);

	//armor
	IMAGEMANAGER->addFrameImage("chain_armor", "image/item/chainmail.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("leather_armor", "image/item/leather.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);

	//torch
	IMAGEMANAGER->addFrameImage("torch_plus_1", "image/item/torch_1.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("torch_plus_2", "image/item/torch_2.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);

	//item
	IMAGEMANAGER->addFrameImage("bomb", "image/item/bomb.bmp", 342, 144, 5, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("bomb_explosion", "image/item/bombExplosion.bmp", 1728, 216, 8, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("cheese", "image/item/cheese.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("apple", "image/item/apple.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);

	//enemy
	IMAGEMANAGER->addFrameImage("whiteSkeleton", "image/enemy/skeletonBasic.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenSkeleton", "image/enemy/skeletonYellow.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("blackSkeleton", "image/enemy/skeletonBlack.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ghost", "image/enemy/ghost.bmp", 144, 144, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mimic", "image/enemy/mimic.bmp", 375, 75, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minotaur", "image/enemy/minotaur.bmp", 1350, 294, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("monkeyBasic", "image/enemy/monkeyBasic.bmp", 450, 150, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("monkeyWhite" ,"image/enemy/monkeyWhite.bmp", 450, 150, 6, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skeleton_dark", "image/enemy/skeletonBasic_dark.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ghost_dark", "image/enemy/ghost_dark.bmp", 144, 144, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimic_dark", "image/enemy/mimic_dark.bmp", 375, 75, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minotaur_dark", "image/enemy/minotaur_dark.bmp", 1350, 294, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("monkeyBasic_dark", "image/enemy/monkeyBasic_dark.bmp", 450, 150, 6, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("enemyAttackX", "image/enemy/enemyAttack.bmp", 360, 138, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemyAttackY", "image/enemy/enemyAttack2.bmp", 358, 144, 5, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("slimeGreen", "image/enemy/slimeGreen.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeGreen_dark", "image/enemy/slimeGreen_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeBlue", "image/enemy/slimeBlue.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeBlue_dark", "image/enemy/slimeBlue_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeGold", "image/enemy/slimeGold.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeGold_dark", "image/enemy/slimeGold_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("zombie", "image/enemy/zombie.bmp", 600, 300, 8, 4, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("zombie_dark", "image/enemy/zombie_dark.bmp", 600, 300, 8, 4, true, RGB(255, 0, 255), true);

	//player
	IMAGEMANAGER->addFrameImage("player_head", "image/player/playerHead.bmp", 216, 72, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("player_body_basic", "image/player/playerArmor_basic.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255), true);	//alpha 값 꼭 챙겨주자!!!
	IMAGEMANAGER->addFrameImage("player_body_leather", "image/player/playerArmor_leather.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("player_body_chain", "image/player/playerArmor_chain.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("shadow_standard_1", "image/player/shadow_standard1.bmp", 72, 81, true, RGB(255, 0, 255), true);	//검은색 타원
	IMAGEMANAGER->addImage("shadow_standard_2", "image/player/shadow_standard2.bmp", 72, 81, true, RGB(255, 0, 255), true);//검은색 짝대기

	//coin
	IMAGEMANAGER->addFrameImage("coin10", "image/item/coin/coin10.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);

	//shopkeeper
	IMAGEMANAGER->addFrameImage("shopkeeper", "image/object/shopkeeper.bmp", 1128, 114, 8, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shopkeeper_dark", "image/object/shopkeeper_dark.bmp", 1128, 114, 8, 1, true, RGB(255, 0, 255), true);
}
