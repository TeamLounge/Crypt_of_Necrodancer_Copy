#pragma once
#include "gameNode.h"

class splashScene : public gameNode
{
private:
	image* _backGround;		 // 검정 백그라운드 이미지
	image* _splash;			 // 스플래쉬 이미지를 담을 변수
	int _alphaIdx;			 // 알파값을 줄 변수
	int _count;				 // 알파값 죽이기위한 카운트
	int _alphaCount;		 // 알파값 죽이기위한 카운트2
	bool _isAlphaStart;		 // 알파값 죽이기위한 시작

public:
	splashScene();
	~splashScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

