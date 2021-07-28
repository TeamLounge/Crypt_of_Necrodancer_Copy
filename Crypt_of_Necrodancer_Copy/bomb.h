#pragma once
#include "gameNode.h"
#include "mapGenerator.h"

struct tagBomb
{
	RECT rc;
	float x, y;
	int currentFrameX;
	int currentFrameY;
	int tileX, tileY;
	bool isExplode;
	const char* imageName;
	bool isSoundPlayed;
};
class bomb : public gameNode
{
private:
	vector<tagBomb> _vBomb;
	vector<tagBomb>::iterator _viBomb;

	mapGenerator* _map;

	float _worldTime;
	float _elapsedSec;
public :

	HRESULT init();
	void release();
	void update();
	void render();
	void render(int tileX, int tileY);
	void fire(int tileX, int tileY, RECT rc); //ÆøÅºÀ§Ä¡ Å¸ÀÏ·ºÆ®·Î ¹Þ¾Æ¿È

	void setBombMapMemoryAddressLink(mapGenerator* map) { _map = map; }

	void explode();
};

