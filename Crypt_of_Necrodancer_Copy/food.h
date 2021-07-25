#pragma once
#include "gameNode.h"
#include "foodType.h"

class player;

struct FOOD
{
	string imageName;
	image* img;
	RECT rc;
	float x, y;
};

class food : public gameNode
{
private:

public:
	FOOD _food;
	foodType* _foodType;
	player* _player;

	int _playerBeforeX;
	int _playerBeforeY;
	
	food();
	~food();

	void InputHandle();
	virtual HRESULT init();
	virtual	void release();
	virtual	void update();
	virtual	void render();

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
};

