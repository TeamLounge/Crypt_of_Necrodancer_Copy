#pragma once
#include "gameNode.h"

class introScene : public gameNode
{
private:
	bool _isSkip;		// 인트로영상 스킵하기위한 불값
	int _count;			// 어느정도 카운트값주고 스킵가능하게

public:
	introScene();
	~introScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();	

};

