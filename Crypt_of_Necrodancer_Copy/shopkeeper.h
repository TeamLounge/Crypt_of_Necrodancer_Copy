#pragma once
#include "gameNode.h"
#include "player.h"
class shopkeeper : public gameNode
{
private:
	player* _player;
	POINT _shopkeeper;
	string _songName;

	float _distance;

	float _elapsedTime;
public:
	virtual HRESULT init(string songName, POINT shopkeeperXY);
	virtual void release();
	virtual void update();
	virtual void render();

	void setShopkeeperPlayerMemoryAddressLink(player* player) { _player = player; }
};

