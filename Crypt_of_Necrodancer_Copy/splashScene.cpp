#include "stdafx.h"
#include "splashScene.h"

splashScene::splashScene()
{
}

splashScene::~splashScene()
{
}

HRESULT splashScene::init()
{
	IMAGEMANAGER->addImage("스플래쉬", "image/UI/splash_screen.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("백그라운드", "image/UI/backGround.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_backGround = IMAGEMANAGER->findImage("백그라운드");
	_splash = IMAGEMANAGER->findImage("스플래쉬");

	_alphaIdx = 255;
	_count = 0;
	_isAlphaStart = false;

	return S_OK;
}

void splashScene::release()
{
}

void splashScene::update()
{
	if (!_isAlphaStart)
	{
		_count++;
	}
	
	if (_count >= 150)
	{
		_isAlphaStart = true;
		_count = 0;
	}

	if (_isAlphaStart)
	{
		_alphaCount++;

		if (_alphaCount >= 10)
		{
			_alphaCount = 0;
			_alphaIdx -= 51;
		}

		if (_alphaIdx <= 0)
		{
			SCENEMANAGER->changeScene("intro");
		}
	}
}

void splashScene::render()
{
	_backGround->render(getMemDC());
	_splash->alphaRender(getMemDC(), _alphaIdx);
}
