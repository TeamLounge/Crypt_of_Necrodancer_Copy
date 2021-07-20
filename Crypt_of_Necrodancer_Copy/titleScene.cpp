#include "stdafx.h"
#include "titleScene.h"

titleScene::titleScene()
{
}

titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	IMAGEMANAGER->addImage("title", "image/UI/title.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("anyKey", "image/UI/¾Æ¹«Å°.bmp", WINSIZEX / 3, WINSIZEY / 15, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("titleMusic", "music/titleMusic.mp3", true, true);
	SOUNDMANAGER->play("titleMusic", 0.8f);
	_title = IMAGEMANAGER->findImage("title");
	_anyKey = IMAGEMANAGER->findImage("anyKey");

	_y = WINSIZEY;
	_alphaIdx = 0;
	_count = 0;

	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	SOUNDMANAGER->update();

	if (_y > WINSIZEY - 100)
	{
		_y -= 1.5f;
	}
	
	if (_alphaIdx < 255)
	{
		_count++;
	}

	if (_count % 10 == 0)
	{
		_count = 0;
		_alphaIdx += 35;
	}
	
	if (_alphaIdx >= 255)
	{
		_alphaIdx = 255;
	}

	if (KEYMANAGER->isOnceKeyDown())
	{
		SOUNDMANAGER->stop("titleMusic");
		SCENEMANAGER->changeScene("lobby");
	}
}

void titleScene::render()
{
	_title->render(getMemDC());
	_anyKey->alphaRender(getMemDC(), WINSIZEX / 2 - (_anyKey->getWidth() / 2), _y, _alphaIdx);
}
