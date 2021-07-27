#pragma once
#include "gameNode.h"
#include "slime.h"
#include "mapGenerator.h"
#include "player.h"
#include "weapon.h"
#include <vector>

#include "slimeGreen.h"
#include "slimeBlue.h"
#include "slimeGold.h"

#include "whiteSkeleton.h"
#include "greenSkeleton.h"
#include "blackSkeleton.h"

#include "ghost.h"
#include "mimic.h"

#include "monkeyBasic.h"
#include "monkeyWhite.h"

#include "minotaur.h"

#include "zombie.h"

#include "redDragon.h"

#include "deathMetal.h"



class player;	//상호 참조 위한 전방 선언


class enemyManager :public gameNode
{
private:
	player* _player;
	weapon* _weapon;
	mapGenerator* _map;

	bool _isboss;
	bool _isWhite;
	bool _isgreen;


	//////////////////////////////
	//			슬라임			//
	//////////////////////////////
	typedef vector<slimeGreen*>					vSlimeGreen;
	typedef vector<slimeGreen*>::iterator		viSlimeGreen;

	typedef vector<slimeBlue*>					vSlimeBlue;
	typedef vector<slimeBlue*>::iterator		viSlimeBlue;

	typedef vector<slimeGold*>					vSlimeGold;
	typedef vector<slimeGold*>::iterator		viSlimeGold;

	vSlimeGreen				_vSlimeGreen;
	viSlimeGreen			_viSlimeGreen;

	vSlimeBlue				_vSlimeBlue;
	viSlimeBlue				_viSlimeBlue;

	vSlimeGold				_vSlimeGold;
	viSlimeGold				_viSlimeGold;

	//////////////////////////////
	//			스켈레톤			//
	//////////////////////////////

	typedef vector<whiteSkeleton*>			 vWitheSkeleton;
	typedef vector<whiteSkeleton*>::iterator viWitheSkeleton;

	typedef vector<greenSkeleton*>			 vGreenSkeleton;
	typedef vector<greenSkeleton*>::iterator viGreenSkeleton;

	typedef vector<blackSkeleton*>			 vBlackSkeleton;
	typedef vector<blackSkeleton*>::iterator viBlackSkeleton;

	vWitheSkeleton _vWitheSkeleton;
	viWitheSkeleton _viWitheSkeleton;

	vGreenSkeleton  _vGreenSkeleton;
	viGreenSkeleton _viGreenSkeleton;

	vBlackSkeleton	_vBlackSkeleton;
	viBlackSkeleton _viBlackSkeleton;

	//////////////////////////////
	//	     고스트&미믹 		//
	//////////////////////////////
	typedef vector<ghost*>  vGhost;
	typedef vector<ghost*>::iterator viGhost;

	typedef vector<mimic*>  vMimic;
	typedef vector<mimic*>::iterator viMimic;


	vGhost _vGhost;
	viGhost _viGhost;

	vMimic  _vMimic;
	viMimic _viMimic;

	//////////////////////////////
	//			 망키	 		//
	//////////////////////////////

	typedef vector<monkeyBasic*>  vMonkeyBasic;
	typedef vector<monkeyBasic*>::iterator viMonkeyBasic;

	vMonkeyBasic _vMonkeyBasic;
	viMonkeyBasic _viMonkeyBasic;

	typedef vector<monkeyWhite*>  vMonkeyWhite;
	typedef vector<monkeyWhite*>::iterator viMonkeyWhite;

	vMonkeyWhite _vMonkeyWhite;
	viMonkeyWhite _viMonkeyWhite;

	//////////////////////////////
	//	     미노타우르스 		//
	//////////////////////////////

	typedef vector<minotaur*>  vMinotaur;
	typedef vector<minotaur*>::iterator viMinotaur;

	vMinotaur _vMinotaur;
	viMinotaur _viMinotaur;

	//////////////////////////////
	//			  좀비			//
	//////////////////////////////
	typedef vector<zombie*>					vZombie;
	typedef vector<zombie*>::iterator		viZombie;

	vZombie					_vZombie;
	viZombie				_viZombie;

	//////////////////////////////
	//			레드 드래곤		//
	//////////////////////////////
	typedef vector<redDragon*>					vRedDragon;
	typedef vector<redDragon*>::iterator		viRedDragon;

	vRedDragon				_vRedDragon;
	viRedDragon				_viRedDragon;

	//////////////////////////////
	//		   데스메탈			//
	//////////////////////////////

	deathMetal* _deathMetal;

	//무기정보
	string _weaponName;
	bool attackoff;
	vector<COLLISION>			_vCollision;
	vector<COLLISION>::iterator _viCollision;

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual HRESULT bossRoomInit();
	virtual void bossRoomRelease();
	virtual void bossRoomUpdate();
	virtual void bossRoomRender();


	void setMapGeneratorMemoryAddressLink(mapGenerator* map) { _map = map; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setWeaponMemoryAddressLink(weapon* weapon) { _weapon = weapon; }
	void bosspatten();


	//ㄹㅇ 수만은 셋터들
	void setSlimeGreen();
	void updateSlimeGreen();
	void renderSlimeGreen();

	void setSlimeGold();
	void updateSlimeGold();
	void renderSlimeGold();

	void setSlimeBlue();
	void updateSlimeBlue();
	void renderSlimeBlue();


	void setWhiteSkeleton();
	void updateWhiteSkeleton();
	void renderWhiteSkeleton();

	void setGreenSkeleton();
	void updateGreenSkeleton();
	void renderGreenSkeleton();

	void setBlackSkeleton();
	void updateBlackSkeleton();
	void renderBlackSkeleton();

	void setGhost();
	void updateGhost();
	void renderGhost();

	void setMimic();
	void updateMimic();
	void renderMimic();

	void setMonkeyBasic();
	void updateMonkeyBasic();
	void renderMonkeyBasic();

	void setMonkeyWhite();
	void updateMonkeyWhite();
	void renderMonkeyWhite();

	void setMinotaur();
	void updateMinotaur();
	void renderMinotaur();

	void setZombie();
	void updateZombie();
	void renderZombie();

	void setRedDragon();
	void updateRedDragon();
	void renderRedDragon();

	//보스방용
	void setDeathMetal();
	void updateDeathMetal();
	void renderDeathMetal();

	void setGhostBossRoom();
	void setWhiteSkeletonBossRoom();
	void setGreenSkeletonBossRoom();

	//에너미 삭제 할 때
	//_em->delete(_tileX, _tileY); 이런 


	//ㄹㅇ 수만은 겟터들

	vSlimeGreen getVSlimeGreen() { return _vSlimeGreen; }
	viSlimeGreen getVISlimeGreen() { return _viSlimeGreen; }		//typedef 쓰면 이렇게 써 임마

	vSlimeBlue getVSlimeBlue() { return _vSlimeBlue; }
	viSlimeBlue getVISlimeBlue() { return _viSlimeBlue; }

	vSlimeGold getVSlimeGold() { return _vSlimeGold; }
	viSlimeGold getVISlimeGold() { return _viSlimeGold; }

	vWitheSkeleton getVWitheSkeleton() { return _vWitheSkeleton; }
	viWitheSkeleton getVIWitheSkeleton() { return _viWitheSkeleton; }

	vGreenSkeleton getVGreenSkeleton() { return _vGreenSkeleton; }
	viGreenSkeleton getVIGreenSkeleton() { return _viGreenSkeleton; }

	vBlackSkeleton getVBlackSkeleton() { return _vBlackSkeleton; }
	viBlackSkeleton getVIBlackSkeleton() { return _viBlackSkeleton; }

	vGhost getVGhost() { return _vGhost; }
	viGhost getVIGhost() { return _viGhost; }

	vMimic getVMimic() { return _vMimic; }
	viMimic getVIMimic() { return _viMimic; }

	vMonkeyBasic getVMonkeyBasic() { return _vMonkeyBasic; }
	viMonkeyBasic getVIMonkeyBasic() { return _viMonkeyBasic; }

	vMonkeyWhite getVMonkeyWhite() { return _vMonkeyWhite; }
	viMonkeyWhite getVIMonkeyWhite() { return _viMonkeyWhite; }

	vMinotaur getVMinotaur() { return _vMinotaur; }
	viMinotaur getVIMinotaur() { return _viMinotaur; }

	vZombie getVZombie() { return _vZombie; }
	viZombie getVIZombie() { return _viZombie; }

	vRedDragon getVRedDragon() { return _vRedDragon; }
	viRedDragon getVIRedDragon() { return _viRedDragon; }



	/////////////////////////////////
	//속도 값 통일해서 변수로 만들어두기
	/////////////////////////////////
};