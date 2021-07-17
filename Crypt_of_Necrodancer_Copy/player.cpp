#include "stdafx.h"
#include "player.h"

HRESULT player::init(int tileX, int tileY)
{
	IMAGEMANAGER->addFrameImage("player_head", "image/player/playerHead.bmp", 204, 72, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body_basic", "image/player/playerArmor_basic.bmp", 204, 90, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body_leather", "image/player/playerArmor_leather.bmp", 204, 90, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_body_chain", "image/player/playerArmor_chain.bmp", 204, 90, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_shadow", "image/player/shadow_standard.bmp", 72, 81, true, RGB(255, 0, 255));
	
	CAMERAMANAGER->setCamera(0, 0);

	_headImageName = "player_head";
	_bodyImageName = "player_body_leather";
	_tileX = tileX;
	_tileY = tileY;
	_elapsedSec = 0;
	_currentFrameX = 0;
	_currentFrameY = 0;
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_elapsedSec += TIMEMANAGER->getElapsedTime();
	if (_elapsedSec >= 0.2f)
	{
		_elapsedSec -= 0.2f;
		if (_currentFrameX >= IMAGEMANAGER->findImage(_headImageName)->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else
		{
			_currentFrameX++;
		}
	}

	_tileRect = _map->getTiles()[_tileY][_tileX].rc;

	_body = RectMake((_tileRect.left + _tileRect.right) / 2 - IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth() / 2,
		_tileRect.top - (IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight() - TILESIZE / 2),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight());
	_head = RectMake(_body.left,
		_body.top - 24,
		IMAGEMANAGER->findImage(_headImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_headImageName)->getFrameHeight());

	CAMERAMANAGER->setCameraCenter((_tileRect.left + _tileRect.right) / 2, (_tileRect.top + _tileRect.bottom) / 2);
}

void player::render()
{
	//Rectangle(getMemDC(), _shadow);
	IMAGEMANAGER->render("player_shadow", getMemDC(), _shadow.left, _shadow.top);
	IMAGEMANAGER->frameRender(_bodyImageName, getMemDC(), _body.left, _body.top, _currentFrameX, _currentFrameY);
	IMAGEMANAGER->frameRender(_headImageName, getMemDC(), _head.left, _head.top, _currentFrameX, _currentFrameY);
}

void player::setupPlayerRect()
{
	_tileRect = _map->getTiles()[_tileY][_tileX].rc;
	//그림자 초기화
	_shadow = RectMake(_tileRect.left, _tileRect.top - 39, 
		IMAGEMANAGER->findImage("player_shadow")->getWidth(), 
		IMAGEMANAGER->findImage("player_shadow")->getHeight());
	//몸통 초기화
	_body = RectMake((_tileRect.left + _tileRect.right) / 2 - IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth() /2,
		_tileRect.top - (IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight() - TILESIZE/2),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameWidth(),
		IMAGEMANAGER->findImage(_bodyImageName)->getFrameHeight());
	//머리 초기화
	_head = RectMake(_body.left,
		_body.top - 24,
		IMAGEMANAGER->findImage(_headImageName)->getFrameWidth(), 
		IMAGEMANAGER->findImage(_headImageName)->getFrameHeight());
	
	//카메라 설정
	CAMERAMANAGER->setCameraCenter((_tileRect.left + _tileRect.right) / 2, (_tileRect.top + _tileRect.bottom) / 2);
}
