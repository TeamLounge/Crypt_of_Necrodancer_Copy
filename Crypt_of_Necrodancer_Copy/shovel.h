#pragma once
#include "shovelType.h"
#include "gameNode.h"
#include <vector>

struct SHOVEL
{
	image* img;
	string imageName;
	RECT rc;
	float x, y;
};

struct COLLISION
{
	RECT rc;
	float x, y;
};

class shovel : public gameNode
{
public:
	shovelType* _shovelType;
	SHOVEL _shovel;
	COLLISION _collision;
	vector<COLLISION>			_vCollision;
	vector<COLLISION>::iterator _viCollision;

	shovel();
	~shovel();

	void InputHandle();
	void InputHandle(shovelType* ShovelType);
	virtual HRESULT init();
	virtual	void release();
	virtual	void update();
	virtual	void render();
	void deleteCollision();

	shovelType* getWeaponType() { return _shovelType; }
	string getWeaponName() { return _shovel.imageName; }
	image* getWeaponImage() { return _shovel.img; }
};

