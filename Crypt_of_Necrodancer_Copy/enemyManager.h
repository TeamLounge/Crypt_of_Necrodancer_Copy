#pragma once
#include "gameNode.h"
#include "slime.h"
#include "mapGenerator.h"
#include "player.h"
#include <vector>

#include "slimeGreen.h"
#include "slimeBlue.h"
#include "slimeGold.h"

#include "whiteSkeleton.h"
#include "greenSkeleton.h"
#include "blackSkeleton.h"

#include "ghost.h"
#include "mimic.h"

#include "monkey.h"

#include "minotaur.h"



class player;	//상호 참조 위한 전방 선언


class enemyManager :public gameNode
{
private:
	player* _player;
	mapGenerator* _map;

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
	//typedef vector<ghost*>  vGhost;
	//typedef vector<ghost*>::iterator viGhost;
	//
	//typedef vector<mimic*>  vMimic;
	//typedef vector<mimic*>::iterator viMimic;
	//
	//
	//vGhost _vGhost;
	//viGhost _viGhost;
	//
	//vMimic  _vMimic;
	//viMimic _viMimic;
	//
	////////////////////////////////
	////			 망키	 		//
	////////////////////////////////
	//
	//typedef vector<monkey*>  vMonkey;
	//typedef vector<monkey*>::iterator viMonkey;
	//
	//vMonkey _vMonkey;
	//viMonkey _viMonkey;
	//
	//
	////////////////////////////////
	////	     미노타우르스 		//
	////////////////////////////////
	//
	//typedef vector<minotaur*>  vMinotaur;
	//typedef vector<minotaur*>::iterator viMinotaur;
	//
	//
	//vMinotaur _vMinotaur;
	//viMinotaur _viMinotaur;
	//


public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();


	void setSlimeGreen();
	void updateSlimeGreen();
	void renderSlimeGreen();

	void setSlimeGold();
	void updateSlimeGold();
	void renderSlimeGold();

	void setSlimeBlue();
	void updateSlimeBlue();
	void renderSlimeBlue();

	void setMapGeneratorMemoryAddressLink(mapGenerator* map) {_map = map;}
	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	
	//ㄹㅇ 수만은 셋터들
	void setWhiteSkeleton();
	void setGreenSkeleton();
	void setBlackSkeleton();
	//void setGhost();
	//void setMimic();
	//void setMonkey();
	//void setMinotaur();

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

	//vGhost getVGhost() { return _vGhost; }
	//viGhost getVIGhost() { return _viGhost; }
	//
	//vMimic getVMimic() { return _vMimic; }
	//viMimic getVIMimic() { return _viMimic; }
	//
	//vMonkey getVMonkey() { return _vMonkey; }
	//viMonkey getVIMonkey() { return _viMonkey; }
	//
	//vMinotaur getVMinotaur() { return _vMinotaur; }
	//viMinotaur getVIMinotaur() { return _viMinotaur; }
};
