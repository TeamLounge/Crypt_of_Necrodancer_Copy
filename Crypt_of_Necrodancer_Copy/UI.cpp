#include "stdafx.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

HRESULT UI::init()
{
	return S_OK;
}

HRESULT UI::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_elapsedSec = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getFrameWidth(), _imageName->getFrameHeight());

	_centerX = (_rc.left + _rc.right) / 2;
	_centerY = (_rc.top + _rc.bottom) / 2;
	_rectX = (WINSIZEX - _centerX) + CAMERAMANAGER->getCameraLEFT();

	_cameraCenterX = (abs)(CAMERAMANAGER->getCameraCenterX() - (_rc.left + _rc.right) / 2); // 처음 태어났을때 카메라중심좌표로부터 나의 거리 측정

	_positionX = position.x;
	_positionY = position.y;

	_cameraCenterX = 0;
	_cameraLeftX = 0;
	_cameraRectX = 0;
	_numMax = 0;
	_range = 0;
	_alpha = 0;
	_moveSpeed = 0;

	return S_OK;
}

void UI::release()
{
	SAFE_RELEASE(_imageName);
	SAFE_DELETE(_imageName);
}

void UI::update(float frameSpeed)
{
	_elapsedSec += TIMEMANAGER->getElapsedTime();

	if (_elapsedSec >= frameSpeed)
	{
		_elapsedSec -= frameSpeed;

		if (_currentFrameX == _imageName->getMaxFrameX())
		{
			_currentFrameX = 0;
		}

		else _currentFrameX++;
	}
}

void UI::render()
{
	draw();
}

void UI::frameMove()
{

}

void UI::move(float speed)
{
	//float moveSpeed = TIMEMANAGER->getElapsedTime() * speed;

	//_centerX += moveSpeed;

	//_cameraCenterX = (abs)(WINSIZEX / 2 - _centerX);
}

void UI::moveY(float speed)
{
	//float moveSpeed = TIMEMANAGER->getElapsedTime() * speed;

	//_centerY += moveSpeed;
}

void UI::draw()
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void UI::imgDraw()
{
	_imageName->render(getMemDC(), _rc.left, _rc.top);
}

void UI::alphaRender()
{
}
