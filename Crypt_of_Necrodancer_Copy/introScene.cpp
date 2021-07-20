#include "stdafx.h"
#include "introScene.h"

introScene::introScene()
{
}

introScene::~introScene()
{
}

HRESULT introScene::init()
{
	_isSkip = false;
	_count = 0;

	STREAMMANAGER->addVideo("movie/introMovie.wmv", "인트로");
	STREAMMANAGER->playVido("인트로");

	return S_OK;
}

void introScene::release()
{
}

void introScene::update()
{
	_count++;
	if (_count >= 20)
	{
		if (KEYMANAGER->isOnceKeyDown())
		{
			_isSkip = true;
		}

		if (_isSkip || STREAMMANAGER->getPosition("인트로") == STREAMMANAGER->getLenthTheEnd("인트로"))
		{
			STREAMMANAGER->closeVideo("인트로");
			SCENEMANAGER->changeScene("title");
		}
	}
}

void introScene::render()
{
}
