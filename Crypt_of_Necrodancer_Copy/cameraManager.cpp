#include "stdafx.h"
#include "cameraManager.h"

void cameraManager::cameraRange()
{
	if (_cameraBuffer->getX() < 0) _cameraBuffer->setX(0);
	else if (_cameraBuffer->getX() + CAMERAX > BACKGROUNDX)_cameraBuffer->setX(BACKGROUNDX - CAMERAX);
	if (_cameraBuffer->getY() < 0)_cameraBuffer->setY(0);
	else if (_cameraBuffer->getY() + CAMERAY > BACKGROUNDY) _cameraBuffer->setY(BACKGROUNDY - CAMERAY);
}

HRESULT cameraManager::init()
{
	_cameraBuffer = new image;
	_cameraBuffer->init(CAMERAX, CAMERAY);
	for (int i = 0; i < 2; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}
	return S_OK;
}

void cameraManager::release()
{
	SAFE_DELETE(_cameraBuffer);
}

void cameraManager::update()
{
	if (_isFixed)
	{
		_isHaveToMove = true;
	}
}


void cameraManager::render(image* backBuffer, HDC frontDC)
{
	HDC cameraDC = _cameraBuffer->getMemDC();
	HDC backDC = backBuffer->getMemDC();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 2; i++)
		{
			if (x[i] != 0)
			{
				LineMake(backDC, x[i], _cameraBuffer->getY(), x[i], _cameraBuffer->getY() + CAMERAY);
			}
			if (y[i] != 0)
			{
				LineMake(backDC, _cameraBuffer->getX(), y[i], _cameraBuffer->getX() + CAMERAX, y[i]);
			}
		}
	}

	backBuffer->render(cameraDC, 0, 0, _cameraBuffer->getX(), _cameraBuffer->getY(), CAMERAX, CAMERAY);
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(cameraDC);
		char str[128];
		sprintf_s(str, "_isFixed: %d", _isFixed);
		TextOut(cameraDC, 0, 100, str, strlen(str));
		sprintf_s(str, "_isHaveToMove: %d", _isHaveToMove);
		TextOut(cameraDC, 0, 120, str, strlen(str));
	}
	_cameraBuffer->render(frontDC, 0, 0);
}

void cameraManager::updateCamera(float x, float y)
{
	_cameraBuffer->setCenter(x, y);
	cameraRange();
}

void cameraManager::updateCamera(float x1, float y1, float x2, float y2, float ratioX1, float ratioX2)
{
	//x1이 비율 밖으로 나가면 화면 조정
	if (x1 >= _cameraBuffer->getX() + ratioX2 * CAMERAX)
	{
		_cameraBuffer->setX(x1 - ratioX2 * CAMERAX);
	}
	if (x1 <= _cameraBuffer->getX() + ratioX1 * CAMERAX)
	{
		_cameraBuffer->setX(x1 - ratioX1 * CAMERAX);
	}

	//x2의 좌표가 화면 밖으로 나가려고 하면 카메라 조정
	if (getCameraRIGHT() <= x2)
	{
		_cameraBuffer->setX(x2 - WINSIZEX);
	}
	else if (getCameraLEFT() >= x2)
	{
		_cameraBuffer->setX(x2);
	}

	cameraRange();
	x[0] = _cameraBuffer->getX() + ratioX1 * CAMERAX;
	x[1] = _cameraBuffer->getX() + ratioX2 * CAMERAX;
}

void cameraManager::updateCamera(float centerX, float centerY, float ratioX)
{
	if (_isFixed) return;

	if (centerX >= _cameraBuffer->getX() + ratioX * CAMERAX)
	{
		if (_isHaveToMove)
		{
			_cameraBuffer->setX(_cameraBuffer->getX() + 10);
			if (centerX <= _cameraBuffer->getX() + ratioX * CAMERAX)
			{
				_cameraBuffer->setX(centerX - ratioX * CAMERAX);
				_isHaveToMove = false;
			}
		}
		else
		{
			_cameraBuffer->setX(centerX - ratioX * CAMERAX);
		}
	}
	cameraRange();
	x[0] = _cameraBuffer->getX() + ratioX * CAMERAX;
	x[1] = 0;
	
}

/*
void cameraManager::updateCamera(float x, float y, float ratioX, float ratioY)
{
	float cX, cY;
	if (ratioX > 0 && ratioY > 0 && ratioX < 1.0f && ratioY < 1.0f)
	{
		if (x == 0.5f)
		{
			cX = x;
		}
		else
		{
			cX = x - ratioX * CAMERAX;
		}

		if (y == 0.5f)
		{
			cY = y;
		}
		else
		{
			cY = y - ratioY * CAMERAY;
		}
		setCamera(cX, cY);
	}
	cameraRange();
}
*/



void cameraManager::updateCamera(RECT& player, float ratioX, float ratioY)
{
	int width = player.right - player.left;
	int height = player.bottom - player.top;

	if (ratioX != 0)
	{
		if (ratioX < 0.5f)
		{
			if (player.left <= _cameraBuffer->getX() + ratioX * CAMERAX)
			{
				_cameraBuffer->setX(player.left - ratioX * CAMERAX);
			}
			if (player.right >= _cameraBuffer->getX() + CAMERAX)
			{
				player.right = _cameraBuffer->getX() + CAMERAX;
				player.left = player.right - width;
			}
		}
		else
		{
			if (player.right >= _cameraBuffer->getX() + ratioX * CAMERAX)
			{
				_cameraBuffer->setX(player.right - ratioX * CAMERAX);
			}
			if (player.left <= _cameraBuffer->getX())
			{
				player.left = _cameraBuffer->getX();
				player.right = player.left + width;
			}
		}
		x[0] = _cameraBuffer->getX() + ratioX * CAMERAX;
		x[1] = 0;
	}

	if (ratioY != 0)
	{
		if (ratioY < 0.5f)
		{
			if (player.top <= _cameraBuffer->getY() + ratioY * CAMERAY)
			{
				_cameraBuffer->setY(player.top - ratioY * CAMERAY);
			}
			if (player.bottom >= _cameraBuffer->getY() + CAMERAY)
			{
				player.bottom = _cameraBuffer->getY() + CAMERAY;
				player.top = player.bottom - height;
			}
		}
		else
		{
			if (player.bottom >= _cameraBuffer->getY() + ratioY * CAMERAY)
			{
				_cameraBuffer->setY(player.bottom - ratioY * CAMERAY);
			}
			if (player.top <= _cameraBuffer->getY())
			{
				player.top = _cameraBuffer->getY();
				player.bottom = player.top + height;
			}
		}
		y[0] = _cameraBuffer->getY() + ratioY * CAMERAY;
		y[1] = 0;
	}

	cameraRange();
}

void cameraManager::updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2)
{
	if (ratioX1 > 0 && ratioX1 < 0.5f)
	{
		if (player.left < _cameraBuffer->getX() + ratioX1 * CAMERAX)
		{
			_cameraBuffer->setX(player.left - ratioX1 * CAMERAX);
		}
	}

	if (ratioX2 > 0.5f && ratioX2 < 1.0f)
	{
		if (player.right > _cameraBuffer->getX() + ratioX2 * CAMERAX)
		{
			_cameraBuffer->setX(player.right - ratioX2 * CAMERAX);
		}
	}

	if (ratioY1 > 0 && ratioY1 < 0.5f)
	{
		if (player.top < _cameraBuffer->getY() + ratioY1 * CAMERAY)
		{
			_cameraBuffer->setY(player.top - ratioY1 * CAMERAY);
		}
	}

	if (ratioY2 > 0.5f && ratioY2 < 1.0f)
	{
		if (player.bottom > _cameraBuffer->getY() + ratioY2 * CAMERAY)
		{
			_cameraBuffer->setY(player.bottom - ratioY2 * CAMERAY);
		}
	}
	cameraRange();

	if (ratioX1 != 0)
	{
		x[0] = _cameraBuffer->getX() + ratioX1 * CAMERAX;
	}
	if (ratioX2 != 0)
	{
		x[1] = _cameraBuffer->getX() + ratioX2 * CAMERAX;
	}
	if (ratioY1 != 0)
	{
		y[0] = _cameraBuffer->getY() + ratioY1 * CAMERAY;
	}
	if (ratioY2 != 0)
	{
		y[1] = _cameraBuffer->getY() + ratioY2 * CAMERAY;
	}
}

float cameraManager::getCameraRIGHT()
{
	return (_cameraBuffer->getX() + CAMERAX);
}

float cameraManager::getCameraBOTTOM()
{
	return (_cameraBuffer->getY() + CAMERAY);
}

