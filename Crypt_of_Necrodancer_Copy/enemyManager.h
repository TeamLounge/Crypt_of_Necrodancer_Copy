#pragma once

#include "gameNode.h"
#include "slime.h"
#include "skeleton.h"
#include <vector>

#include "slimeGreen.h"
#include "slimeBlue.h"
#include "slimeGold.h"

class player;	//상호 참조 위한 전방 선언


class enemyManager :public gameNode
{
private:
	player* _player;

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

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	vector<slimeGreen*> getVSlimeGreen() { return _vSlimeGreen; }
	vector<slimeGreen*>::iterator getVISlimeGreen() { return _viSlimeGreen; }

	vector<slimeBlue*> getVSlimeBlue() { return _vSlimeBlue; }
	vector<slimeBlue*>::iterator getVISlimeBlue() { return _viSlimeBlue; }

	vector<slimeGold*> getVSlimeGold() { return _vSlimeGold; }
	vector<slimeGold*>::iterator getVISlimeGold() { return _viSlimeGold; }


	void setPlayerMemoryAddressLink(player * player) { _player = player; }
};
