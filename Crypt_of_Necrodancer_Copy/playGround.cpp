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
	addSoundEffect();

	SCENEMANAGER->addScene("splash", new splashScene);
	SCENEMANAGER->addScene("intro", new introScene);
	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("player_test", new playerTestScene);
	SCENEMANAGER->addScene("bossScene", new bossScene);
	SCENEMANAGER->changeScene("splash");


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
	if (!STREAMMANAGER->getIsPlay())
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
	IMAGEMANAGER->addFrameImage("bombX3", "image/object/bomb_3.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->findImage("wall_torch")->setFrameX(0);
	IMAGEMANAGER->findImage("wall_torch")->setFrameY(0);

	//play HUD
	IMAGEMANAGER->addFrameImage("heart", "image/UI/heart.bmp", 100, 150, 2, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_heart", "image/UI/heart.bmp", 67, 100, 2, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heartBeat", "image/UI/beat_marker.bmp", 24, 64, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beatHeart", "image/UI/beat_heart.bmp", 246, 156, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("money", "image/UI/money.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("diamond", "image/UI/diamond.bmp", 50, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("X", "image/UI/X.bmp", 14, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("number", "image/UI/number.bmp", 140, 18, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("itemHUD", "image/UI/itemHUD.bmp", 1890, 126, 21, 1, true, RGB(255, 0, 255));

	//item HUD
	IMAGEMANAGER->addFrameImage("dagger", "image/item/dagger.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("broadSword", "image/item/broadsword.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("rapier", "image/item/rapier.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("longSword", "image/item/longsword.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spear", "image/item/spear.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shovelBasic", "image/item/shovel_basic.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shovelTitanium", "image/item/shovel_titanium.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shovelBasicEffect", "image/item/shovel_basic_effect.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shovelTitaniumEffect", "image/item/shovel_titanium_effect.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	

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
	IMAGEMANAGER->addFrameImage("minotaur_dark", "image/enemy/minotaur_dark.bmp", 1350, 294, 9, 2, true, RGB(255, 0, 255));
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

	IMAGEMANAGER->addFrameImage("dragonRed", "image/enemy/dragonRed.bmp", 1281, 306, 7, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dragonRed_dark", "image/enemy/dragonRed_dark.bmp", 1281, 306, 7, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dragonRedFire", "image/enemy/dragonRedFire.bmp", 504, 72, 7, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dragonRedFireStarting", "image/enemy/dragonRedFireStarting.bmp", 504, 144, 7, 2, true, RGB(255, 0, 255), true);


	IMAGEMANAGER->addFrameImage("deathMetal", "image/enemy/deathMetal.bmp", 2100, 318, 10, 2, true, RGB(255, 0, 255), true);

	//player
	IMAGEMANAGER->addFrameImage("player_head", "image/player/playerHead.bmp", 216, 72, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("player_body_basic", "image/player/playerArmor_basic.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255), true);	//alpha 값 꼭 챙겨주자!!!
	IMAGEMANAGER->addFrameImage("player_body_leather", "image/player/playerArmor_leather.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("player_body_chain", "image/player/playerArmor_chain.bmp", 216, 90, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("shadow_standard_1", "image/player/shadow_standard1.bmp", 72, 81, true, RGB(255, 0, 255), true);	//검은색 타원
	IMAGEMANAGER->addImage("shadow_standard_2", "image/player/shadow_standard2.bmp", 72, 81, true, RGB(255, 0, 255), true);//검은색 짝대기

	//coin
	IMAGEMANAGER->addFrameImage("coin1", "image/item/coin/coin1.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin2", "image/item/coin/coin2.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin3", "image/item/coin/coin3.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin4", "image/item/coin/coin4.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin5", "image/item/coin/coin5.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin6", "image/item/coin/coin6.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin7", "image/item/coin/coin7.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin8", "image/item/coin/coin8.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin9", "image/item/coin/coin9.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coin10", "image/item/coin/coin10.bmp", 72, 144, 1, 2, true, RGB(255, 0, 255), true);

	//shopkeeper
	IMAGEMANAGER->addFrameImage("shopkeeper", "image/object/shopkeeper.bmp", 1128, 114, 8, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("shopkeeper_dark", "image/object/shopkeeper_dark.bmp", 1128, 114, 8, 1, true, RGB(255, 0, 255), true);

	//멘트등록
	IMAGEMANAGER->addImage("벗어남", "image/UI/TEMP_missed.bmp", 72, 26, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("죽음멘트1", "image/UI/game_death1.bmp", 236, 24, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("죽음멘트2", "image/UI/game_death2.bmp", 166, 24, true, RGB(255, 0, 255), true);

	//이펙트 등록
	IMAGEMANAGER->addFrameImage("broadSword_LR", "image/item/broadSword_W.bmp", 162, 378, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("broadSword_TB", "image/item/broadSword2_W.bmp", 567, 108, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dagger_LR", "image/item/dagger_W.bmp", 171, 66, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dagger_TB", "image/item/dagger2_W.bmp", 99, 114, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("longSword_LR", "image/item/longSword_W.bmp", 552, 96, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("longSword_TB", "image/item/longSword2_W.bmp", 192, 276, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("rapier_LR", "image/item/rapier_W.bmp", 528, 42, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("rapier_TB", "image/item//rapier2_W.bmp", 84, 264, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("throwDagger_LR", "image/item/throwDagger_LR.bmp", 76, 48, 3, 2, true, RGB(255, 0, 255), true);
}

void playGround::addSoundEffect()
{
	SOUNDMANAGER->addSound("dig_dirt", "sound_effect/mov_dig_dirt.ogg", false, false);
	SOUNDMANAGER->addSound("dig_fail", "sound_effect/mov_dig_fail.ogg", false, false);
	SOUNDMANAGER->addSound("dig_stone", "sound_effect/mov_dig_stone.ogg", false, false);
	SOUNDMANAGER->addSound("door_open", "sound_effect/obj_door_open.ogg", false, false);
	SOUNDMANAGER->addSound("monkey_grab", "sound_effect/en_monkey_grab.ogg", false, false);
	SOUNDMANAGER->addSound("monkey_hit1", "sound_effect/en_monkey_hit_01.ogg", false, false);
	SOUNDMANAGER->addSound("monkey_hit2", "sound_effect/en_monkey_hit_02.ogg", false, false);
	SOUNDMANAGER->addSound("monkey_hit3", "sound_effect/en_monkey_hit_03.ogg", false, false);
	SOUNDMANAGER->addSound("bomb_lit", "sound_effect/sfx_bomb_lit.ogg", false, false);
	SOUNDMANAGER->addSound("bomb_explode", "sound_effect/sfx_bomb_explode.ogg", false, false);
	SOUNDMANAGER->addSound("trap_bounce", "sound_effect/obj_trap_bounce.ogg", false, false);
	SOUNDMANAGER->addSound("pickup_weapon", "sound_effect/sfx_pickup_weapon.ogg", false, false);
	SOUNDMANAGER->addSound("pickup_gold", "sound_effect/sfx_pickup_gold_01.ogg", false, false);
	SOUNDMANAGER->addSound("pickup_general", "sound_effect/sfx_pickup_general_ST.ogg", false, false);
	SOUNDMANAGER->addSound("pickup_armor", "sound_effect/sfx_pickup_armor.ogg", false, false);
	SOUNDMANAGER->addSound("deathMetal_fire", "sound_effect/en_deathmetal_fireball.ogg", false, false);
	SOUNDMANAGER->addSound("deathMetal_skel", "sound_effect/en_deathmetal_skels.ogg", false, false);
	SOUNDMANAGER->addSound("attackVoice", "sound_effect/vo_cad_melee_1_01.ogg", false, false);
	SOUNDMANAGER->addSound("attackVoice2", "sound_effect/vo_cad_melee_2_01.ogg", false, false);
	SOUNDMANAGER->addSound("attackVoice3", "sound_effect/vo_cad_melee_3_01.ogg", false, false);
	SOUNDMANAGER->addSound("attackVoice4", "sound_effect/vo_cad_melee_4_01.ogg", false, false);
	SOUNDMANAGER->addSound("player_death", "sound_effect/vo_cad_death_03.ogg", false, false);
	SOUNDMANAGER->addSound("player_hurt", "sound_effect/vo_cad_hurt_05.ogg", false, false);
	SOUNDMANAGER->addSound("miss_beat", "sound_effect/sfx_missedbeat.ogg", false, false);
	SOUNDMANAGER->addSound("throw", "sound_effect/wep_throwable_thrown.ogg", false, false);
}
