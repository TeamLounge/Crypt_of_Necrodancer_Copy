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

	STREAMMANAGER->addVideo("movie/introMovie.wmv", "��Ʈ��");
	STREAMMANAGER->playVido("��Ʈ��");

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

		if (_isSkip || STREAMMANAGER->getPosition("��Ʈ��") == STREAMMANAGER->getLenthTheEnd("��Ʈ��"))
		{
			STREAMMANAGER->closeVideo("��Ʈ��");
			SCENEMANAGER->changeScene("title");
		}
	}
}

void introScene::render()
{
}
