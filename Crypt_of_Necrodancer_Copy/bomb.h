#pragma once
#include "gameNode.h"

struct tagBomb
{
	RECT rc;
	float x, y;
	int currentFrameX;
	int currentFrameY;
	int tileX, tileY;
	bool isExplode;
	const char* imageName;
};
class bomb : public gameNode
{
private:
	vector<tagBomb> _vBomb;
	vector<tagBomb>::iterator _viBomb;

	float _worldTime;
	float _elapsedSec;
public :

	HRESULT init();
	void release();
	void update();
	void render();
	void fire(int tileX, int tileY, RECT rc); //ÆøÅºÀ§Ä¡ Å¸ÀÏ·ºÆ®·Î ¹Þ¾Æ¿È
};

