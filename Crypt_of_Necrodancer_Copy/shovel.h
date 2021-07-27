#pragma once
#include "gameNode.h"
#include "shovelType.h"
#include "mapGenerator.h"
#include <vector>

class player;
class objectManager;
class mapGenerator;

struct SHOVELS
{
	image* img;
	string imageName;
	RECT rc;
	float x, y;
};

struct SHOVELCOLLISION
{
	RECT rc;
	float tileX, tileY;
};

class shovel : public gameNode
{
public:
	shovelType* _shovelType;
	SHOVELS _shovel;
	SHOVELCOLLISION _collision;
	vector<SHOVELCOLLISION>				_vCollision;
	vector<SHOVELCOLLISION>::iterator	_viCollision;

	player* _player;
	objectManager* _om;
	mapGenerator* _map;

	int _playerBeforeX;
	int	_playerBeforeY;

	shovel();
	~shovel();

	void InputHandle();
	void InputHandle(shovelType* ShovelType);
	virtual HRESULT init();
	virtual	void release();
	virtual	void update();
	virtual	void render();
	void deleteCollision();

	shovelType* getShovelType() { return _shovelType; }
	string getShovelName() { return _shovel.imageName; }
	image* getShovelImage() { return _shovel.img; }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setOMMemoryAddressLink(objectManager* om) { _om = om; }
	void setMGMemoryAddressLink(mapGenerator* map) { _map = map; }

	vector<SHOVELCOLLISION> getVCollision() { return _vCollision; }
	vector<SHOVELCOLLISION>::iterator getVICollision() { return _viCollision; }
};

