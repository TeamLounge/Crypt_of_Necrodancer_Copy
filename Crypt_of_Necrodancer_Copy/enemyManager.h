#pragma once
#include "gameNode.h"
#include "slime.h"
#include "whiteSkeleton.h"
#include "mapGenerator.h"
#include "player.h"
#include <vector>

#include "slimeGreen.h"
#include "slimeBlue.h"
#include "slimeGold.h"

class player;	//��ȣ ���� ���� ���� ����


class enemyManager :public gameNode
{
private:
	player* _player;
	mapGenerator* _map;

	//////////////////////////////
	//			������			//
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
	//			���̷���			//
	//////////////////////////////

	vector<whiteSkeleton*> _vWitheSkeleton;
	vector<whiteSkeleton*>::iterator _viWitheSkeleton;
public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setWhiteSkeleton();

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

	vector<slimeGreen*> getVSlimeGreen() { return _vSlimeGreen; }
	vector<slimeGreen*>::iterator getVISlimeGreen() { return _viSlimeGreen; }

	vector<slimeBlue*> getVSlimeBlue() { return _vSlimeBlue; }
	vector<slimeBlue*>::iterator getVISlimeBlue() { return _viSlimeBlue; }

	vector<slimeGold*> getVSlimeGold() { return _vSlimeGold; }
	vector<slimeGold*>::iterator getVISlimeGold() { return _viSlimeGold; }


};
