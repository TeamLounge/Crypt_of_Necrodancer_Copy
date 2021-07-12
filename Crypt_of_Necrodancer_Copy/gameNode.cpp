#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		CAMERAMANAGER->init();
		
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
	}
	

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	
}

void gameNode::render()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hdc; //�� �� �߿��մ�...


	switch (iMessage)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			this->render();

			EndPaint(hWnd, &ps);
		break;
		case WM_TIMER:
			this->update();
		break;
		//���콺 �����̸� ���⼭ �޼��� �߻�
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;

		case WM_COMMAND:
		break;

		case WM_KEYDOWN:

			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;


			//������ â �ν���(?) 
		case WM_DESTROY:
		//������ �����Լ�
			PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	
}