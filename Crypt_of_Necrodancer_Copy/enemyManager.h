#pragma once

#include "gameNode.h"
#include "slime.h"
#include "skeleton.h"
#include <vector>


class enemyManager :public gameNode
{
private:

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
