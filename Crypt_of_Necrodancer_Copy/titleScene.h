#pragma once
#include "gameNode.h"


class titleScene : public gameNode
{
private:
	image* _title;
	image* _anyKey;

	float _y;			// 아무키나 누르세요 y값
	int _count;			// 아무키나 누르세요 y값 슬라이드 올리려고~
	int _alphaIdx;		// 아무키나 누르세요 알파값 적용하려고

public:
	titleScene();
	~titleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

